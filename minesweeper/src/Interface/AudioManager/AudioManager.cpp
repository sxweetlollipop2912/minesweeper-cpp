#include <iostream>

#include "AudioManager.h"


AudioManager::AudioManager() {
	queue.clear();
	cfgs.clear();
	current_song_idx = -1;
	current_cfg_idx = 0;
	current_status = MusicStatus::Stopped;
    current_volume = des_volume = 100;
	start_moment = sf::microseconds(0);
    start_stopping_moment = start_changing_volume_moment = sf::microseconds(0);
}


AudioVisualCfg AudioManager::parseFromCfgFile(const std::string& file_path) {
	AudioVisualCfg cfg_v;
	std::ifstream in_cfg(file_path);

	if (in_cfg.is_open()) {
		std::string s;
		int line_cnt = 0;

        auto normalize = [](std::string &s) {
            if(!s.empty() && *s.rbegin() == '\r') {
                s.erase( s.size() - 1, 1);
            }
        };
        auto readNextCfg = [&]() {
            for (; line_cnt < MAX_LINE && std::getline(in_cfg, s); line_cnt++) {
                normalize(s);
                if (!s.empty() && *s.begin() == '[' && *s.rbegin() == ']' && s.size() <= MAX_CHAR_PER_LINE)
                    break;
            }
        };

        readNextCfg();

		while (line_cnt <= MAX_LINE) {
            normalize(s);
            if (!(!s.empty() && *s.begin() == '[' && *s.rbegin() == ']' && s.size() <= MAX_CHAR_PER_LINE))
                break;

			try {
				auto start_time = std::stoi(s.substr(1, s.size() - 2));

				cfg_v.v.push_back(AudioVisualCfg::Cfg());
				auto& cfg = cfg_v.v.back();
				cfg.time = sf::seconds(start_time);

				for (; line_cnt < MAX_LINE && std::getline(in_cfg, s); line_cnt++) {
                    normalize(s);
                    if (s.empty() || s.size() > MAX_CHAR_PER_LINE)
                        continue;
                    if (*s.begin() == '[' && *s.rbegin() == ']')
                        break;
					if (s.find(OPTION_VALUE_SEPARATOR) == std::string::npos) 
						continue;

					auto separator = s.find(OPTION_VALUE_SEPARATOR);
					auto option = s.substr(0, separator);
					auto value_str = s.substr(separator + 1);

					if (option == PRIMARY_COLOR_OPTION) {
						std::stringstream ss(value_str);
						std::vector <int> color(3);
						color[0] = cfg.primary_color.r, color[1] = cfg.primary_color.g, color[2] = cfg.primary_color.b;
						for (int i = 0; i < 3 && ss >> color[i]; i++);

						cfg.primary_color = sf::Color(color[0], color[1], color[2]);
					}

					if (option == SECONDARY_COLOR_OPTION) {
						std::stringstream ss(value_str);
						std::vector <int> color(3);
						color[0] = cfg.secondary_color.r, color[1] = cfg.secondary_color.g, color[2] = cfg.secondary_color.b;
						for (int i = 0; i < 3 && ss >> color[i]; i++);

						cfg.secondary_color = sf::Color(color[0], color[1], color[2]);
					}

					if (option == TRANSITION_DURATION_OPTION) {
						std::stringstream ss(value_str);
						int duration = cfg.transition_duration.asSeconds();
						for (int i = 0; i < 1 && ss >> duration; i++);

						cfg.transition_duration = sf::seconds(duration);
					}

					if (option == BUBBLE_SPEED_OPTION) {
						std::stringstream ss(value_str);
						int speed = cfg.bubble_speed;
						for (int i = 0; i < 1 && ss >> speed; i++);

						cfg.bubble_speed = speed;
					}
				}
			}
			catch (const std::exception& e) {
				std::cout << "Error while parsing " << file_path  << ": " << e.what();

				readNextCfg();
			}
		}
	}

	cfg_v.sort();

	return cfg_v;
}


void AudioManager::setRandomMusicList(const int max_songs) {
	music.stop();
	current_status = MusicStatus::Stopped;

	std::set <fs::path> set;

	for (const auto& entry : fs::directory_iterator(MUSIC_PATH)) {
		if (AUDIO_EXTENSIONS.find(entry.path().extension().string()) != AUDIO_EXTENSIONS.end()) {
			set.insert(entry.path().filename());
		}

		if (entry.path().extension().string() == CFG_EXTENSION) {
			cfgs[entry.path().stem()] = parseFromCfgFile(entry.path().string());
		}
	}

	queue.clear();

	for (int cnt = 0; !set.empty() && cnt < max_songs; cnt++) {
		int ran = rand() % (int)(set.size());
		for (const auto& e : set) {
			if (ran == 0) {
				queue.push_back(e);
				break;
			}
			--ran;
		}
		set.erase(queue.back());

		if (cfgs.find(queue.back().stem()) == cfgs.end()) {
			cfgs[queue.back().stem()].v.push_back(DEFAULT_VISUAL_CONFIG);
		}
	}

	current_song_idx = -1;
}


Result AudioManager::startPlayingEntry(const int song_idx) {
	if (!queue.empty() && music.openFromFile(MUSIC_PATH + queue[song_idx].string())) {
		music.play();
        music.setVolume(current_volume);
		start_moment = (*ResourceManager::getInstance())->getElapsedTime();
		current_cfg_idx = 0;

		return Result::success;
	}
	else {
		return Result::failure;
	}
}


void AudioManager::onNextMusicEvent() {
    start_stopping_moment = (*ResourceManager::getInstance())->getElapsedTime();
	current_status = MusicStatus::Stopping;
}


void AudioManager::startMusic() {
	current_status = MusicStatus::Playing;
}


void AudioManager::turnVolume(const float volume) {
	if (current_status != MusicStatus::Stopping && std::abs(des_volume - volume) > EPS) {
		this->des_volume = volume;
        start_changing_volume_moment = (*ResourceManager::getInstance())->getElapsedTime();
	}
}


AudioVisualCfg::Cfg AudioManager::update() {
	if (current_status != MusicStatus::Stopping && std::abs(des_volume - current_volume) > EPS) {
        auto time_elapsed = (*ResourceManager::getInstance())->getElapsedTime() - start_changing_volume_moment;
        if (time_elapsed < VOLUME_CHANGING_TIME) {
            auto dec_volume_percent = time_elapsed.asMilliseconds() / (float)VOLUME_CHANGING_TIME.asMilliseconds();
            current_volume += (des_volume - current_volume) * dec_volume_percent;
        }
        else {
            current_volume = des_volume;
        }
        music.setVolume(current_volume);
	}

	AudioVisualCfg::Cfg cfg;

	if (current_status != MusicStatus::Stopped) {
		if (!queue.empty() && music.getStatus() == sf::Music::SoundSource::Status::Stopped) {
			int cnt = 0;
			do {
				current_song_idx = (current_song_idx + 1) % (int)queue.size();
				++cnt;
			} while (startPlayingEntry(current_song_idx) == Result::failure && cnt < queue.size());
		}

		if (current_status == MusicStatus::Stopping) {
			auto time_elapsed = (*ResourceManager::getInstance())->getElapsedTime() - start_stopping_moment;
			auto volume_down = time_elapsed.asMilliseconds() / (float)VOLUME_DOWN_TIME.asMilliseconds();

			if (volume_down > 1) {
				music.stop();
				current_status = MusicStatus::Playing;
			}
			else {
				music.setVolume(current_volume - (volume_down * (float)100));
			}
		}

		if (music.getStatus() == sf::Music::SoundSource::Status::Playing &&
			cfgs.find(queue[current_song_idx].stem()) != cfgs.end()) {

			auto v = cfgs.at(queue[current_song_idx].stem()).v;

			if (current_cfg_idx < v.size()) {
				const auto& current_cfg = v[current_cfg_idx];
				auto now = (*ResourceManager::getInstance())->getElapsedTime() - start_moment;
				if (now >= current_cfg.time) {
					cfg = current_cfg;
					++current_cfg_idx;
				}
			}
		}
	}

	return cfg;
}

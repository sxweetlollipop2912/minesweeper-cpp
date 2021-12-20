#include "AudioManager.h"


AudioManager::AudioManager() {
	queue.clear();
	current_song_idx = -1;
	current_status = sf::Music::SoundSource::Status::Stopped;
}


void AudioManager::setRandomMusiclist(const int max_songs) {
	music.stop();
	current_status = sf::Music::SoundSource::Status::Stopped;

	std::set <std::string> set;

	for (const auto& entry : fs::directory_iterator(MUSIC_PATH)) {
		if (EXTENSIONS.find(entry.path().extension().string()) != EXTENSIONS.end()) {
			set.insert(entry.path().filename().string());
		}
	}

	queue.clear();

	for (int cnt = 0; !set.empty() && cnt < max_songs; cnt++) {
		int ran = rand() % (int)(set.size());
		for (auto e : set) {
			if (ran == 0) {
				queue.push_back(e);
				break;
			}
			--ran;
		}
		set.erase(queue.back());
	}

	current_song_idx = -1;
}


Result AudioManager::startPlayingEntry(const int song_idx) {
	if (!queue.empty() && music.openFromFile(MUSIC_PATH + queue[song_idx])) {
		music.play();

		return Result::success;
	}
	else {
		return Result::failure;
	}
}


void AudioManager::onNextMusicEvent() {
	music.stop();
	current_status = sf::Music::SoundSource::Status::Playing;
}


void AudioManager::startMusic() {
	current_status = sf::Music::SoundSource::Status::Playing;
}


Result AudioManager::update() {
	if (current_status != sf::Music::SoundSource::Status::Stopped) {
		if (!queue.empty() && music.getStatus() == sf::Music::SoundSource::Status::Stopped) {
			current_song_idx = (current_song_idx + 1) % (int)queue.size();

			if (startPlayingEntry(current_song_idx) == Result::failure) {
				return Result::failure;
			}
		}
	}

	return Result::success;
}

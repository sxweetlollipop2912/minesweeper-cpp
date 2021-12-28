#include <filesystem>
#include <fstream>
#include <set>
#include <string>
#include <sstream>

#include <SFML/Audio.hpp>

#include "../ResourceManager/ResourceManager.h"
#include "../../Enums.h"
#include "../../Constants.h"
#include "../../Structs.h"

namespace fs = std::filesystem;


enum class MusicStatus {
	Playing,
	Stopped,
	Stopping,
};


class AudioManager {
private:
	sf::Music music;
	std::vector <fs::path> queue;
	std::map <fs::path, AudioVisualCfg> cfgs;

	int current_song_idx;
	int current_cfg_idx;
	int volume;
	MusicStatus current_status;

	sf::Time start_moment;
	sf::Time start_down_volume_moment;


	AudioVisualCfg parseFromCfgFile(const std::string& file_path);

	Result startPlayingEntry(const int song_idx);

public:
	AudioManager();

	// Initializes a music list of random songs from music directory.
	// With `max_songs` as number of max songs on the list.
	// If music is currently played, this will stop the music.
	// NOTE: manually call `startMusic` to start music after calling this.
	void setRandomMusiclist(const int max_songs);

	void onNextMusicEvent();
	void startMusic();
	void turnVolume(const int volume);

	// This should be called on every frame.
	AudioVisualCfg::Cfg update();
};
#include <filesystem>
#include <set>
#include <string>

#include <SFML/Audio.hpp>

#include "../../Enums.h"
#include "../../Constants.h"
#include "../../Structs.h"

namespace fs = std::filesystem;

const std::set <std::string> EXTENSIONS = { ".ogg",".wav",".flac" };


class AudioManager {
private:
	sf::Music music;
	std::vector <std::string> queue;
	int current_song_idx;
	sf::Music::SoundSource::Status current_status;

	sf::Clock clock;


	Result startPlayingEntry(const int song_idx);

public:
	AudioManager();

	// Initializes a music list of random songs from music directory.
	// With `max_songs` as number of max songs on the list.
	// If music is currently played, this will stop the music.
	// NOTE: manually call `playMusic` to start music after calling this.
	void setRandomMusiclist(const int max_songs);

	void onNextMusicEvent();
	void startMusic();

	// This should be called on every frame.
	Result update();
};
#pragma once

#include <SFML/Graphics.hpp>

class Timer {
private:
    sf::Time last_resumed;
    sf::Time run_time;
    bool is_paused;

public:
    Timer();

    void reset();
    void resume();
    void pause();
    sf::Time getElapsedTime() const;
};
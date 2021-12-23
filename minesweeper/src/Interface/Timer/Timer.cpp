#include "Timer.h"
#include "../Window/Window.h"


Timer::Timer() {
    reset();
}

void Timer::reset() {
    is_paused = false;
    run_time = sf::microseconds(0);
    last_resumed = (*ResourceManager::getInstance())->getElapsedTime();
}

void Timer::resume() {
    if (is_paused) {
        last_resumed = (*ResourceManager::getInstance())->getElapsedTime();
    }
    is_paused = false;
}

void Timer::pause() {
    if (!is_paused) {
        run_time += (*ResourceManager::getInstance())->getElapsedTime() - last_resumed;
    }
    is_paused = true;
}

sf::Time Timer::getElapsedTime() const {
    if (!is_paused) {
        return run_time + (*ResourceManager::getInstance())->getElapsedTime() - last_resumed;
    }
    return run_time;
}
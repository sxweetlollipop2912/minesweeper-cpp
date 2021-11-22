#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Window.h"
#include "../Board/Board.h"


sf::Vector2i Window::getMousePosition() const {
	return pos_mouse;
}

SceneType Window::getCurrentSceneType() const {
	return current_scene_type;
}

GameEvent Window::getLastGameEvent() const {
	return last_game_event;
}


std::shared_ptr<Scene> Window::getCurrentScene() {
	if (map_scene.find(current_scene_type) != map_scene.end()) {
		return map_scene[current_scene_type];
	}

	return nullptr;
}


void Window::initializeMenuScene(sf::Vector2u window_size) {
	auto menu_scene = std::static_pointer_cast<MenuScene>(map_scene[SceneType::Menu]);
	menu_scene->initialize(window_size);
}


void Window::initializePlayingScene(sf::Vector2u window_size, int board_rows, int board_cols) {
	auto playing_scene = std::static_pointer_cast<PlayingScene>(map_scene[SceneType::Playing]);
	playing_scene->initialize(window_size, board_rows, board_cols);
}


bool Window::changeMousePosition(const sf::Vector2i& mouse_position) {
	pos_mouse = mouse_position;

	switch (current_scene_type) {
	case SceneType::Playing:
	{
		auto playing_scene = std::static_pointer_cast<PlayingScene>(map_scene[SceneType::Playing]);
		if (playing_scene->PlayingScene::changeMousePosition(mouse_position))
			drawCurrentScene();

		break;
	}

	case SceneType::Menu:
		//break;
	case SceneType::Won:
		//break;
	case SceneType::Lost:
		//break;
	case SceneType::Leaderboard:
		//break;
	case SceneType::Closing:
		//break;
	case SceneType::Unkown:
		//break;

	default:
		auto scene = getCurrentScene();
		if (scene->changeMousePosition(pos_mouse))
			drawCurrentScene();

		break;
	}
}


void Window::setCurrentSceneType(const SceneType& type) {
	current_scene_type = type;
}


void Window::createWindow() {
	render_window.create(sf::VideoMode(width, height), title);
}


void Window::closeWindow() {
	render_window.close();
}


void Window::onResize(const int width, const int height) {
	this->width = width;
	this->height = height;
}


Result Window::handleMouseButtonPress(const sf::Mouse::Button& button, const sf::Vector2i& position) {
	return Result();
}


void Window::drawCurrentScene() {
	switch (current_scene_type) {
	case SceneType::Menu:
	{
		auto menu_scene = std::static_pointer_cast<MenuScene>(map_scene[SceneType::Menu]);
		draw(*menu_scene);
		break;
	}
	case SceneType::Playing:
	{
		auto playing_scene = std::static_pointer_cast<PlayingScene>(map_scene[SceneType::Playing]);
		draw(*playing_scene);
		break;
	}
	case SceneType::Won:
		break;
	case SceneType::Lost:
		break;
	case SceneType::Leaderboard:
		break;
	case SceneType::Closing:
		break;
	case SceneType::Unkown:
		break;
	default:
		break;
	}
}


void Window::draw(const sf::Sprite& sprite) {
	render_window.draw(sprite);
}


void Window::draw(const sf::Text& text) {
	render_window.draw(text);
}


void Window::draw(Text& text) {
	draw(text.getSfText());
}


void Window::draw(Button& button, const bool isHovered) {
	if (isHovered == false)
		draw(button.getDefaultSprite());
	else
		draw(button.getHoveredSprite());

	draw(button.label);
}


void Window::draw(MenuScene& scene) {
	draw((Scene&)scene);
}


void Window::draw(PlayingScene& scene) {
	draw((Scene&)scene);

	Board& board = scene.board;

	for (int i = 0; i < board.number_of_rows; i++) {
		for (int j = 0; j < board.number_of_cols; j++) {

			if (Position(i, j) != board.hovered_cell) {
				draw(board.board[i][j]);
			}
			else {
				draw(board.board[i][j], true);
			}
		}
	}
}


void Window::draw(Scene& scene) {
	for (auto i = scene.map_button.begin(); i != scene.map_button.end(); i++) {
		if (i->first != scene.hovered_button)
			draw(i->second);
		else
			draw(i->second, true);
	}

	for (auto i = scene.map_text.begin(); i != scene.map_text.end(); i++)
		draw(i->second);
}

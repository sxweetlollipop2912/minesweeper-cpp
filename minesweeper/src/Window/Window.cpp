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
	bool change = false;

	switch (current_scene_type) {
	case SceneType::Playing:
	{
		auto playing_scene = std::static_pointer_cast<PlayingScene>(map_scene[SceneType::Playing]);
		if (playing_scene->PlayingScene::changeMousePosition(pos_mouse))
			change = true;

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
			change = true;

		break;
	}

	return change;
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


bool Window::handleGameEvents(const GameEvent game_event) {
	if (game_event == GameEvent::Unknown)
		return false;


	switch (game_event) {
		case GameEvent::QuitGame:
		{
			// Send quit game event to back end.
			// End game.

			break;
		}
		case GameEvent::QuitToMenu:
		{
			if (current_scene_type == SceneType::Playing) {
				// Send quit game event to back end.
			}
			current_scene_type = SceneType::Menu;

			break;
		}
		case GameEvent::NewGame:
		{
			current_scene_type = SceneType::Playing;
			// Send new game event to back end.
			// Update board.

			break;
		}
		case GameEvent::LoadGame:
		{
			current_scene_type = SceneType::Playing;
			// Send load game event to back end.
			// Update board.

			break;
		}
		case GameEvent::ShowLeaderboard:
		{
			current_scene_type = SceneType::Leaderboard;
			// Send load leaderboard to back end.
			// Update leaderboard.

			break;
		}
		case GameEvent::OpenCell:
		{
			// Send open action with coordinate on board to back end.
			// Update board, check if won/lost.
			bool won = false, lost = false;
			if (won) {
				handleGameEvents(GameEvent::Won);
			}
			else if (lost) {
				handleGameEvents(GameEvent::Lost);
			}
			// Else, keep current scene (Playing).
			break;
		}
		case GameEvent::FlagCell:
		{
			// Send flag action with coordinate on board to back end.
			// Update board, check if won/lost.
			bool won = false, lost = false;
			if (won) {
				handleGameEvents(GameEvent::Won);
			}
			else if (lost) {
				handleGameEvents(GameEvent::Lost);
			}
			// Else, keep current scene (Playing).
			break;
		}
		case GameEvent::AutoOpenCell:
		{
			// Send auto open action with coordinate on board to back end.
			// Update board, check if won/lost.
			bool won = false, lost = false;
			if (won) {
				handleGameEvents(GameEvent::Won);
			}
			else if (lost) {
				handleGameEvents(GameEvent::Lost);
			}
			// Else, keep current scene (Playing).
			break;
		}
		case GameEvent::Won:
		{
			// Load whole board, splash screen etc.
			current_scene_type = SceneType::Won;
			break;
		}
		case GameEvent::Lost: 
		{
			// Load whole board, splash screen etc.
			current_scene_type = SceneType::Lost;
			break;
		}
		default:
		{
			return false;
		}
	}

	last_game_event = game_event;

	return true;
}


bool Window::handleMouseButtonPress(const sf::Mouse::Button& button, const sf::Vector2i& position) {
	if (lock_mouse_button != MouseActionType::Unknown) {
		return false;
	}

	// Determines mouse action type.
	switch (button) {
	case sf::Mouse::Left:
		lock_mouse_button = MouseActionType::LMB;
		break;

	case sf::Mouse::Right:
		lock_mouse_button = MouseActionType::RMB;
		break;
	}

	return false;
}


bool Window::handleMouseButtonRelease(const sf::Mouse::Button& button, const sf::Vector2i& position) {
	bool match = false;

	if (lock_mouse_button == MouseActionType::DoubleLMB && button == sf::Mouse::Left)
		match = true;
	if (lock_mouse_button == MouseActionType::LMB && button == sf::Mouse::Left)
		match = true;
	if (lock_mouse_button == MouseActionType::RMB && button == sf::Mouse::Right)
		match = true;

	if (!match) return false;


	MouseActionType type = lock_mouse_button;
	lock_mouse_button = MouseActionType::Unknown;


	// Detects double left click.
	// If a double left click is detected, sets `lock_mouse_button` to `MouseActionType::DoubleLMB` and returns.
	{
		sf::Clock elapse;
		sf::Event event;

		if (type == MouseActionType::LMB) {
			while (elapse.getElapsedTime().asMilliseconds() < 100) {
				while (render_window.pollEvent(event)) {
					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
						lock_mouse_button = MouseActionType::DoubleLMB;

						return false;
					}
				}
			}
		}
	}


	// Runs scene-specific mouse action handling methods.
	// Gets the next game event, if exists
	GameEvent nxt_event = GameEvent::Unknown;
	{
		switch (current_scene_type) {
		case SceneType::Menu:
		{
			auto menu_scene = std::static_pointer_cast<MenuScene>(map_scene[SceneType::Menu]);
			nxt_event = menu_scene->MenuScene::handleMouseButtonEvent(type);
			break;
		}
		case SceneType::Playing:
		{
			auto playing_scene = std::static_pointer_cast<PlayingScene>(map_scene[SceneType::Playing]);
			nxt_event = playing_scene->PlayingScene::handleMouseButtonEvent(type);
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

	return handleGameEvents(nxt_event);
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

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Window.h"
#include "../Board/Board.h"
#include "../Scenes/leaderboard_scene.h"


Window* Window::instance = nullptr;


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


void Window::initializeMenuScene() {
	auto menu_scene = std::shared_ptr<MenuScene>(new MenuScene(window_size));
	map_scene[SceneType::Menu] = std::static_pointer_cast<Scene>(menu_scene);
}


void Window::initializeLeaderboardScene() {
	auto leaderboard_scene = std::shared_ptr<LeaderboardScene>(new LeaderboardScene(window_size));
	map_scene[SceneType::Leaderboard] = std::static_pointer_cast<Scene>(leaderboard_scene);
}


void Window::initializePlayingScene(const int board_rows = -1, const int board_cols = -1) {
	auto current_playing_scene = std::static_pointer_cast<PlayingScene>(map_scene[SceneType::Playing]);
	int rows = board_rows < 0 ? current_playing_scene->getBoardRows() : board_rows;
	int cols = board_cols < 0 ? current_playing_scene->getBoardCols() : board_cols;

	auto playing_scene = std::shared_ptr<PlayingScene>(new PlayingScene(window_size, rows, cols));
	map_scene[SceneType::Playing] = std::static_pointer_cast<Scene>(playing_scene);
}


bool Window::changeMousePosition(const sf::Vector2i& mouse_position) {
	pos_mouse = mouse_position;

	bool change = getCurrentScene()->changeMousePosition(pos_mouse);

	return change;
}


void Window::setCurrentSceneType(const SceneType& type) {
	current_scene_type = type;
}


std::shared_ptr<Window*> Window::getInstance() {
	if (!instance) {
		instance = new Window();
	}
	return std::make_shared<Window*>(instance);
}


void Window::createWindow() {
	render_window.create(window_size, title, window_style);
}


void Window::closeWindow() {
	render_window.close();
}


Result Window::updateGameInfo(const Comms::GameInfo info) {
	return Result::failure;
}


bool Window::handleSfEvent(const sf::Event& event) {
	bool change = false;

	switch (event.type) {
	case sf::Event::Closed:
		change |= handleGameEvents(GameEvent::QuitGame);
		break;
	case sf::Event::MouseMoved:
		change |= changeMousePosition(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
		break;
	case sf::Event::MouseButtonPressed:
		change |= handleMouseButtonPress(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		break;
	case sf::Event::MouseButtonReleased:
		change |= handleMouseButtonRelease(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		break;
	default:
		break;
	}

	return change;
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
			break;
		}
		case GameEvent::Lost: 
		{
			// Load whole board, splash screen etc.
			break;
		}
		case GameEvent::ClosePopUp:
		case GameEvent::OpenPopUp:
		{
			return true;
		}
		default:
		{
			return false;
		}
	}

	last_game_event = game_event;
	getCurrentScene()->changeMousePosition(pos_mouse);

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
			while (elapse.getElapsedTime().asMilliseconds() < 50) {
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
		nxt_event = map_scene[current_scene_type]->handleMouseButtonEvent(type);
	}

	return handleGameEvents(nxt_event);
}


void Window::drawCurrentScene() {
	draw(*getCurrentScene());
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


void Window::draw(Scene& scene) {
	Scene::DrawableList list = scene.getDrawableList();

	for (int rank = 0, sprite_idx = 0, text_idx = 0; sprite_idx < list.sprites.size() || text_idx < list.texts.size(); rank++) {
		for (; sprite_idx < list.sprites.size() && list.sprites[sprite_idx].rank == rank; sprite_idx++) {
			draw(*list.sprites[sprite_idx].sprite);
		}
		for (; text_idx < list.texts.size() && list.texts[text_idx].rank == rank; text_idx++) {
			draw(*list.texts[text_idx].text);
		}
	}
}

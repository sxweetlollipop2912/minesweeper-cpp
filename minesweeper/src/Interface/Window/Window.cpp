#include <iostream>

#include "Window.h"


Window* Window::instance = nullptr;


Window::Window(const sf::VideoMode& window_size, const std::string& title, const int window_style) {
	this->window_size = window_size;
	this->title = title;
	this->window_style = window_style;

	background = Background(window_size);

	audio_manager.setRandomMusiclist(MAX_SONGS);
	audio_manager.startMusic();

	auto menu_scene = std::shared_ptr<MenuScene>(new MenuScene(window_size));
	auto playing_scene = std::shared_ptr<PlayingScene>(new PlayingScene(window_size, 0, 0));

	scenes[SceneType::Menu] = std::static_pointer_cast<Scene>(menu_scene);
	scenes[SceneType::Playing] = std::static_pointer_cast<Scene>(playing_scene);

	setCurrentSceneType(SceneType::Menu);
	last_game_event = GameEvent::Unknown;
	lock_mouse_button = MouseActionType::Unknown;
	pos_mouse = sf::Vector2i(-1, -1);
}


std::shared_ptr<Window*> Window::getInstance() {
	if (!instance) {
		instance = new Window();
	}
	return std::make_shared<Window*>(instance);
}


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
	if (scenes.find(getCurrentSceneType()) != scenes.end()) {
		return scenes.at(getCurrentSceneType());
	}

	return nullptr;
}


void Window::initializeMenuScene() {
	auto menu_scene = std::shared_ptr<MenuScene>(new MenuScene(window_size));
	scenes[SceneType::Menu] = std::static_pointer_cast<Scene>(menu_scene);
}


void Window::initializeLeaderboardScene() {
	auto leaderboard_scene = std::shared_ptr<LeaderboardScene>(new LeaderboardScene(window_size));
	scenes[SceneType::Leaderboard] = std::static_pointer_cast<Scene>(leaderboard_scene);
}


void Window::initializeDifficultiesScene() {
	auto difficulties_scene = std::shared_ptr<DifficultiesScene>(new DifficultiesScene(window_size));
	scenes[SceneType::Difficulties] = std::static_pointer_cast<Scene>(difficulties_scene);
}


void Window::initializePlayingScene(const int board_rows, const int board_cols) {
	int rows = std::max(board_rows, 0);
	int cols = std::max(board_cols, 0);

	if ((board_rows < 0 || board_cols < 0) && scenes.find(SceneType::Playing) != scenes.end()) {
		auto current_playing_scene = std::dynamic_pointer_cast<PlayingScene>(scenes.at(SceneType::Playing));
		rows = current_playing_scene->getBoardRows();
		cols = current_playing_scene->getBoardCols();
	}

	auto playing_scene = std::shared_ptr<PlayingScene>(new PlayingScene(window_size, rows, cols));
	scenes[SceneType::Playing] = std::static_pointer_cast<Scene>(playing_scene);
}


bool Window::changeMousePosition(const sf::Vector2i& mouse_position) {
	pos_mouse = mouse_position;

	bool change = getCurrentScene()->changeMousePosition(pos_mouse);

	return change;
}


void Window::setCurrentSceneType(const SceneType& type) {
	current_scene_type = type;
}


void Window::createWindow() {
	render_window.create(window_size, title, window_style);
}


void Window::closeWindow() {
	render_window.close();
}


void Window::updateGameInfo(const Comms::GameInfo info) {
	current_game_info = info;

	switch (current_interface_info.game_event) {
		case GameEvent::QuitToMenu:
		{
			initializeMenuScene();

			break;
		}
		case GameEvent::NewGame:
		case GameEvent::LoadGame:
		{
			initializePlayingScene(current_game_info.board_row, current_game_info.board_col);

			auto scene = std::dynamic_pointer_cast<PlayingScene>(getCurrentScene());
			scene->updateBoard(current_game_info.cell_board, current_game_info.mine_board, 
				current_game_info.game_Feature.flags);

			break;
		}
		case GameEvent::ShowLeaderboard:
		{
			initializeLeaderboardScene();

			auto scene = std::dynamic_pointer_cast<LeaderboardScene>(getCurrentScene());
			scene->updateRecords(current_game_info.records);

			break;
		}
		case GameEvent::OpenCell:
		case GameEvent::FlagCell:
		case GameEvent::AutoOpenCell:
		{
			auto scene = std::dynamic_pointer_cast<PlayingScene>(getCurrentScene());
			scene->updateBoard(current_game_info.cell_board, current_game_info.mine_board,
				current_game_info.game_Feature.flags);

			break;
		}
		case GameEvent::Unknown: 
		{
			// From updatePerFrame() method.
			if (constantly_changing_scenes.find(getCurrentSceneType()) != constantly_changing_scenes.end()) {
				switch (getCurrentSceneType()) {
				case SceneType::Playing:
				{
					auto scene = std::dynamic_pointer_cast<PlayingScene>(getCurrentScene());
					scene->updateTimer(current_game_info.current_timer);

					break;
				}
				}
			}

			break;
		}
		default:
			break;
	}
}


bool Window::handleSfEvents(const sf::Event& event) {
	bool change = false;

	switch (event.type) {
	case sf::Event::Closed:
		change |= handleGameEvents(GameEvent::QuitGame);
		break;
	case sf::Event::MouseMoved:
		change |= changeMousePosition(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
		break;
	case sf::Event::MouseButtonPressed:
		change |= onMouseButtonPressed(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		break;
	case sf::Event::MouseButtonReleased:
		change |= onMouseButtonReleased(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		break;
	default:
		break;
	}

	return change;
}


bool Window::handleGameEvents(const GameEvent game_event) {
	bool send_interface_info = false;

	switch (game_event) {
		case GameEvent::QuitGame:
		{
			if (getCurrentSceneType() == SceneType::Playing) {
				send_interface_info = true;
			}

			break;
		}
		case GameEvent::QuitToMenu:
		{
			if (getCurrentSceneType() == SceneType::Playing) {
				send_interface_info = true;
			}

			break;
		}
		case GameEvent::NewGame:
		{
			send_interface_info = true;

			auto scene = std::dynamic_pointer_cast<DifficultiesScene>(getCurrentScene());

			current_interface_info.new_row = std::min(scene->getCurrentRow(), scene->getCurrentCol());
			current_interface_info.new_col = std::max(scene->getCurrentRow(), scene->getCurrentCol());

			std::cout << "ROW " << current_interface_info.new_row << '\n';
			std::cout << "COL " << current_interface_info.new_col << '\n';

			break;
		}
		case GameEvent::LoadGame:
		{
			send_interface_info = true;

			break;
		}
		case GameEvent::ShowLeaderboard:
		{
			send_interface_info = true;

			break;
		}
		case GameEvent::OpenCell:
		case GameEvent::FlagCell:
		case GameEvent::AutoOpenCell:
		{
			send_interface_info = true;

			auto scene = std::dynamic_pointer_cast<PlayingScene>(getCurrentScene());

			current_interface_info.cell_pos = scene->getLastPressedCell();

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
		case GameEvent::NextSong:
		{
			audio_manager.onNextMusicEvent();

			break;
		}
	}

	if (game_event != GameEvent::Unknown && game_event != GameEvent::NextSong) {
		auto scene = getCurrentScene();

		if (game_event == GameEvent::ChangesInScene) {
			scene->changeMousePosition(pos_mouse);
		}

		else {
			auto nxt_scene_type = getCurrentSceneType();
			if (scene->getNextScene(game_event) != SceneType::Unknown) {
				nxt_scene_type = scene->getNextScene(game_event);
			}

			if (send_interface_info) {
				// Postpones changing current scene type to the next scene
				// Postpones changing last_game_event
				// to wait for response from GAME.
				current_interface_info.game_event = game_event;
				current_interface_info.current_scene = nxt_scene_type;

				// Sends to GAME.
				Comms::interfaceInfoSending(current_interface_info);
			}

			last_game_event = game_event;
			setCurrentSceneType(nxt_scene_type);

			getCurrentScene()->changeMousePosition(pos_mouse);
		}
	}

	return game_event != GameEvent::Unknown;
}


bool Window::onMouseButtonPressed(const sf::Mouse::Button& button, const sf::Vector2i& position) {
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

	// Runs scene-specific mouse released event handling methods.
	// Gets the next game event, if exists
	GameEvent nxt_event = GameEvent::Unknown;
	{
		nxt_event = scenes.at(getCurrentSceneType())->onMouseButtonPressed(lock_mouse_button);
	}

	return handleGameEvents(nxt_event);
}


bool Window::onMouseButtonReleased(const sf::Mouse::Button& button, const sf::Vector2i& position) {
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


	// Runs scene-specific mouse released event handling methods.
	// Gets the next game event, if exists
	GameEvent nxt_event = GameEvent::Unknown;
	{
		nxt_event = scenes.at(getCurrentSceneType())->onMouseButtonReleased(type);
	}

	return handleGameEvents(nxt_event);
}


bool Window::updatePerFrame() {
	auto audio_cfg = audio_manager.update();
	background.setNextConfig(audio_cfg);
	background.update();

	if (constantly_changing_scenes.find(getCurrentSceneType()) != constantly_changing_scenes.end()) {
		current_interface_info.game_event = GameEvent::Unknown;
		current_interface_info.current_scene = getCurrentSceneType();

		Comms::interfaceInfoSending(current_interface_info);

		return true;
	}

	return true;
}


void Window::drawCurrentScene() {
	draw(background.getDrawableList());
	draw(getCurrentScene()->getDrawableList());
}


void Window::draw(const sf::Sprite& sprite) {
	render_window.draw(sprite);
}


void Window::draw(const sf::Text& text) {
	render_window.draw(text);
}


void Window::draw(const sf::RectangleShape& rect) {
	render_window.draw(rect);
}


void Window::draw(const sf::CircleShape& circle) {
	render_window.draw(circle);
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


void Window::draw(const DrawableList& list) {
	for (int rank = 0, sprite_idx = 0, text_idx = 0, rect_idx = 0, circle_idx = 0; 
		sprite_idx < list.sprites.size() || 
		text_idx < list.texts.size() || 
		rect_idx < list.rects.size() || 
		circle_idx < list.circles.size(); rank++) {

		for (; rect_idx < list.rects.size() && list.rects[rect_idx].rank == rank; rect_idx++) {
			draw(*list.rects[rect_idx].rect);
		}
		for (; circle_idx < list.circles.size() && list.circles[circle_idx].rank == rank; circle_idx++) {
			draw(*list.circles[circle_idx].circle);
		}
		for (; sprite_idx < list.sprites.size() && list.sprites[sprite_idx].rank == rank; sprite_idx++) {
			draw(*list.sprites[sprite_idx].sprite);
		}
		for (; text_idx < list.texts.size() && list.texts[text_idx].rank == rank; text_idx++) {
			draw(*list.texts[text_idx].text);
		}
	}
}

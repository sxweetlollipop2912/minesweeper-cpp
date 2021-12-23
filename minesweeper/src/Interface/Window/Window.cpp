#include <iostream>

#include "Window.h"


Window* Window::instance = nullptr;


Window::Window(const sf::VideoMode& window_size, const std::string& title, const int window_style) {
	render_window = std::make_shared<sf::RenderWindow>();

	this->window_size = window_size;
	this->title = title;
	this->window_style = window_style;

	background = std::make_shared<Background>(Background(window_size));

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
	int rows = std::min(MAX_ROW, std::max(board_rows, MIN_ROW));
	int cols = std::min(MAX_COLUMN, std::max(board_cols, MIN_COLUMN));

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

	bool change = false;
	change |= getCurrentScene()->changeMousePosition(pos_mouse);
	change |= background->changeMousePosition(pos_mouse);

	return change;
}


void Window::setCurrentSceneType(const SceneType& type) {
	if (type != current_scene_type) {
		pressed_actions.clear();
		released_actions.clear();
		lock_mouse_button = MouseActionType::Unknown;

		current_scene_type = type;
	}
}


void Window::createWindow() {
	render_window->create(window_size, title, window_style);
}


void Window::closeWindow() {
	render_window->close();
}


void Window::updateGameInfo(const Comms::GameInfo& info) {
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
			if (current_game_info.game_Feature.MAX_ROW < 0 || current_game_info.game_Feature.MAX_COLUMN < 0) {
				current_interface_info.current_scene = SceneType::Difficulties;
			}
			else {
				initializePlayingScene(current_game_info.game_Feature.MAX_ROW, current_game_info.game_Feature.MAX_COLUMN);

				auto scene = std::dynamic_pointer_cast<PlayingScene>(scenes.at(current_interface_info.current_scene));
				scene->updateBoard(current_game_info.cell_board, current_game_info.mine_board,
					current_game_info.game_Feature.flags);

				if (current_game_info.game_state == GameState::Won) std::cout << "WON!\n";
				else if (current_game_info.game_state == GameState::Ongoing) std::cout << "ongoing!\n";
				else if (current_game_info.game_state == GameState::Lost) std::cout << "LOST!\n";
			}

			break;
		}
		case GameEvent::ShowLeaderboard:
		{
			initializeLeaderboardScene();

			auto scene = std::dynamic_pointer_cast<LeaderboardScene>(scenes.at(current_interface_info.current_scene));
			scene->updateRecords(current_game_info.records);

			break;
		}
		case GameEvent::OpenCell:
		case GameEvent::FlagCell:
		case GameEvent::AutoOpenCell:
		{
			auto scene = std::dynamic_pointer_cast<PlayingScene>(scenes.at(current_interface_info.current_scene));
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
					auto scene = std::dynamic_pointer_cast<PlayingScene>(scenes.at(current_interface_info.current_scene));
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
		onMouseButtonPressed(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		break;
	case sf::Event::MouseButtonReleased:
		onMouseButtonReleased(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
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

			if (current_interface_info.new_row == BEGINNER_ROW && current_interface_info.new_col == BEGINNER_COL) {
				current_interface_info.difficulty = Difficulty::Beginner;
			}
			else if (current_interface_info.new_row == INTERMEDIATE_ROW && current_interface_info.new_col == INTERMEDIATE_COL) {
				current_interface_info.difficulty = Difficulty::Intermediate;
			}
			else if (current_interface_info.new_row == EXPERT_ROW && current_interface_info.new_col == EXPERT_COL) {
				current_interface_info.difficulty = Difficulty::Expert;
			}
			else {
				current_interface_info.difficulty = Difficulty::Custom;
			}

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

				setCurrentSceneType(current_interface_info.current_scene);
				last_game_event = current_interface_info.game_event;
			}
			else {
				setCurrentSceneType(nxt_scene_type);
				last_game_event = game_event;
			}

			getCurrentScene()->changeMousePosition(pos_mouse);
		}
	}

	return game_event != GameEvent::Unknown;
}


void Window::onMouseButtonPressed(const sf::Mouse::Button& button, const sf::Vector2i& position) {
	if (lock_mouse_button != MouseActionType::Unknown) {
		return;
	}

	// Determines mouse action type.
	switch (button) {
	case sf::Mouse::Left:
	{
		if (!released_actions.empty() && released_actions.front().type == MouseActionType::LMB &&
			(game_clock.getElapsedTime() - released_actions.front().pressed_moment) <= DOUBLE_CLICK_TIME_LIMIT) {

			lock_mouse_button = MouseActionType::DoubleLMB;

			released_actions.pop_front();
			pressed_actions.pop_front();
		}
		else {
			lock_mouse_button = MouseActionType::LMB;
		}
		break;
	}

	case sf::Mouse::Right: 
	{
		lock_mouse_button = MouseActionType::RMB;
		break;
	}
	}

	pressed_actions.push_front(MouseAction(lock_mouse_button, game_clock.getElapsedTime()));
	released_actions.push_front(MouseAction(MouseActionType::Unknown, pressed_actions.front().pressed_moment));

	if (pressed_actions.front().type == MouseActionType::LMB || pressed_actions.front().type == MouseActionType::DoubleLMB) {
		// Runs scene-specific mouse released event handling methods.
		// Gets the next game event, if exists
		GameEvent nxt_event = GameEvent::Unknown;
		{
			auto mouse_type = pressed_actions.front().type == MouseActionType::LMB ? MouseActionType::FirstLMB : MouseActionType::SecondLMB;

			auto bg_event = background->onMouseButtonPressed(mouse_type);
			nxt_event = scenes.at(getCurrentSceneType())->onMouseButtonPressed(mouse_type);
			if (nxt_event == GameEvent::Unknown)
				nxt_event = bg_event;
		}

		handleGameEvents(nxt_event);
	}
}


void Window::onMouseButtonReleased(const sf::Mouse::Button& button, const sf::Vector2i& position) {
	bool match = false;

	if (lock_mouse_button == MouseActionType::DoubleLMB && button == sf::Mouse::Left)
		match = true;
	if (lock_mouse_button == MouseActionType::LMB && button == sf::Mouse::Left)
		match = true;
	if (lock_mouse_button == MouseActionType::RMB && button == sf::Mouse::Right)
		match = true;

	if (match) {
		released_actions.front().type = lock_mouse_button;
		lock_mouse_button = MouseActionType::Unknown;

		if (released_actions.front().type == MouseActionType::LMB || released_actions.front().type == MouseActionType::DoubleLMB) {
			// Runs scene-specific mouse released event handling methods.
			// Gets the next game event, if exists
			GameEvent nxt_event = GameEvent::Unknown;
			{
				auto mouse_type = released_actions.front().type == MouseActionType::LMB ? MouseActionType::FirstLMB : MouseActionType::SecondLMB;

				auto bg_event = background->onMouseButtonReleased(mouse_type);
				nxt_event = scenes.at(getCurrentSceneType())->onMouseButtonReleased(mouse_type);
				if (nxt_event == GameEvent::Unknown)
					nxt_event = bg_event;
			}

			handleGameEvents(nxt_event);
		}
	}
}


void Window::updatePerFrame() {
	// Mouse action handling
	{
		if (!pressed_actions.empty()) {
			auto last_mouse_action = pressed_actions.back().type;

			if (last_mouse_action != MouseActionType::LMB ||
				(game_clock.getElapsedTime() - pressed_actions.back().pressed_moment) > DOUBLE_CLICK_TIME_LIMIT) {

				pressed_actions.pop_back();

				// Runs scene-specific mouse released event handling methods.
				// Gets the next game event, if exists
				GameEvent nxt_event = GameEvent::Unknown;
				{
					auto bg_event = background->onMouseButtonPressed(last_mouse_action);
					nxt_event = scenes.at(getCurrentSceneType())->onMouseButtonPressed(last_mouse_action);
					if (nxt_event == GameEvent::Unknown)
						nxt_event = bg_event;
				}

				handleGameEvents(nxt_event);
			}
		}

		if (!released_actions.empty() && released_actions.back().type != MouseActionType::Unknown) {
			auto last_mouse_action = released_actions.back().type;

			if (last_mouse_action != MouseActionType::LMB ||
				(game_clock.getElapsedTime() - released_actions.back().pressed_moment) > DOUBLE_CLICK_TIME_LIMIT) {

				released_actions.pop_back();

				// Runs scene-specific mouse released event handling methods.
				// Gets the next game event, if exists
				GameEvent nxt_event = GameEvent::Unknown;
				{
					auto bg_event = background->onMouseButtonReleased(last_mouse_action);
					nxt_event = scenes.at(getCurrentSceneType())->onMouseButtonReleased(last_mouse_action);
					if (nxt_event == GameEvent::Unknown)
						nxt_event = bg_event;
				}

				handleGameEvents(nxt_event);
			}
		}
	}

	audio_manager.turnVolume(background->volume->getSliderValue());
	auto audio_cfg = audio_manager.update();
	background->setNextConfig(audio_cfg);
	background->update();

	if (constantly_changing_scenes.find(getCurrentSceneType()) != constantly_changing_scenes.end()) {
		current_interface_info.game_event = GameEvent::Unknown;
		current_interface_info.current_scene = getCurrentSceneType();

		Comms::interfaceInfoSending(current_interface_info);
	}
}


void Window::drawCurrentScene() {
	render_window->clear();

	background->draw(std::static_pointer_cast<sf::RenderTarget>(render_window));
	getCurrentScene()->draw(std::static_pointer_cast<sf::RenderTarget>(render_window));

	render_window->display();
}

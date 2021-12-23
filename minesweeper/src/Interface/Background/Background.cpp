#include <iostream>

#include "Background.h"


float calDist(const sf::Vector2f p1, const sf::Vector2f p2 = sf::Vector2f(0, 0)) {
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	return sqrt(x * x + y * y);
}


Background::Background(const sf::VideoMode window_size, const sf::Color primary_color, const sf::Color secondary_color, const float circle_speed, const int number_of_circles, const float circle_radius) : Scene(window_size, SceneType::Background) {
	cur_prim_color = des_prim_color = primary_color;
	cur_second_color = des_second_color = secondary_color;
	cur_second_color.a = des_second_color.a = TRANSPARENT_ALPHA;
	this->circle_speed = circle_speed;
	transition_duration = sf::microseconds(0);

	last_color_update = (*ResourceManager::getInstance())->getElapsedTime();
	last_pos_update = (*ResourceManager::getInstance())->getElapsedTime();

	background.setSize(sf::Vector2f(window_size.width, window_size.height ));
	background.setFillColor(cur_prim_color);

	circles.resize(number_of_circles);
	{
		for (int i = 0; i < circles.size(); i++) {
			auto& circle = circles[i];

			circle.radius = circle_radius;

			sf::Color color = secondary_color;

			auto& pos = circle.pos;
			pos.x = 1.2 * circle_radius + (rand() % (window_size.width - (int)(circle_radius * 2.2)));
			pos.y = 1.2 * circle_radius + (rand() % (window_size.height - (int)(circle_radius * 2.2)));
		}
	}

	{
		float angle = ((90 / (float)(number_of_circles + 1)) / 180) * PI;
		for(int i = 0; i < circles.size(); i++) {
			auto& veloc = circles[i].veloc;

			veloc.x = cos(angle * (float)(i + 1));
			veloc.y = sqrt(1 - veloc.x * veloc.x);

			veloc.x *= ((rand() % 2 == 0) ? -1 : 1);
			veloc.y *= ((rand() % 2 == 0) ? -1 : 1);
		}
	}

	// Interactive objects
	{
		buttons_event[STR_NEXT_SONG] = GameEvent::NextSong;

		Button& next_song_button = buttons[STR_NEXT_SONG];
		next_song_button.setImage(TextureType::NextSong);
		next_song_button.setSize(NEXT_SONG_SIZE);

		sf::Vector2f TL_next_song;
		TL_next_song.x = RIGHT_DOWN_COEF_NEXT_SONG.x * window_size.width - next_song_button.getSize().x;
		TL_next_song.y = RIGHT_DOWN_COEF_NEXT_SONG.y * window_size.height - next_song_button.getSize().y;
		next_song_button.setTopLeftPos(TL_next_song);

		sf::Vector2f volume_pos;
		volume_pos.x = (RIGHT_DOWN_COEF_VOLUME.x - VOLUME_WIDTH) * window_size.width;
		volume_pos.y = (RIGHT_DOWN_COEF_VOLUME.y - VOLUME_HEIGHT) * window_size.height;
		volume = std::make_shared<Slider>(Slider(0, 100, 100, volume_pos, VOLUME_WIDTH * window_size.width, VOLUME_HEIGHT * window_size.width, false));
	}
}


GameEvent Background::onMouseButtonReleased(const MouseActionType mouse_type) {
	auto game_event = this->Scene::onMouseButtonReleased(mouse_type);

	volume->onMouseButtonReleased(mouse_type);

	return game_event;
}


GameEvent Background::onMouseButtonPressed(const MouseActionType mouse_type) {
	auto game_event = Scene::onMouseButtonPressed(mouse_type);
	
	if (game_event == GameEvent::Unknown) {
		bool change = false;
		change |= volume->onMouseButtonPressed(mouse_type);

		game_event = change ? GameEvent::ChangesInScene : GameEvent::Unknown;
	}

	return game_event;
}


bool Background::changeMousePosition(const sf::Vector2i& pos) {
	bool change = false;

	change |= this->Scene::changeMousePosition(pos);
	change |= volume->changeMousePosition(pos);

	return change;
}


void Background::calCurrentColor() {
	if (transition_duration.asMilliseconds() < 0)
		return;

	auto time_elapsed = (*ResourceManager::getInstance())->getElapsedTime() - last_color_update;
	transition_duration -= time_elapsed;
	float rate = (1 / (float)transition_duration.asMilliseconds()) * (float)time_elapsed.asMilliseconds();

	{
		Color color = cur_prim_color;
		color.r = (des_prim_color.r - color.r) * rate + color.r;
		color.g = (des_prim_color.g - color.g) * rate + color.g;
		color.b = (des_prim_color.b - color.b) * rate + color.b;

		if ((des_prim_color.r - color.r) * (des_prim_color.r - cur_prim_color.r) > 0 &&
			(des_prim_color.g - color.g) * (des_prim_color.g - cur_prim_color.g) > 0 &&
			(des_prim_color.b - color.b) * (des_prim_color.b - cur_prim_color.b) > 0) {

			cur_prim_color = color;
		}
	}
	background.setFillColor(cur_prim_color);

	{
		Color color = cur_second_color;
		color.r = (des_second_color.r - color.r) * rate + color.r;
		color.g = (des_second_color.g - color.g) * rate + color.g;
		color.b = (des_second_color.b - color.b) * rate + color.b;

		if ((des_second_color.r - color.r) * (des_second_color.r - cur_second_color.r) > 0 &&
			(des_second_color.g - color.g) * (des_second_color.g - cur_second_color.g) > 0 &&
			(des_second_color.b - color.b) * (des_second_color.b - cur_second_color.b) > 0) {

			cur_second_color = color;
		}
	}

	last_color_update = (*ResourceManager::getInstance())->getElapsedTime();
}


void Background::calCurrentCirclesPos() {
	for (auto& circle : circles) {
		auto pos = circle.pos;
		auto radius = circle.radius;

		auto& veloc = circle.veloc;
		
		if (((pos.x - radius) < EPS && veloc.x < 0) || ((float)(window_size.width - radius - pos.x) < EPS && veloc.x > 0)) {
			veloc.x = -veloc.x;
		}
		if (((pos.y - radius) < EPS && veloc.y < 0) || ((float)(window_size.height - radius - pos.y) < EPS && veloc.y > 0)) {
			veloc.y = -veloc.y;
		}
	}

	auto time_elapsed = ((*ResourceManager::getInstance())->getElapsedTime() - last_pos_update).asMilliseconds();
	float distance = circle_speed * (time_elapsed / (float)sf::seconds(1).asMilliseconds());

	for (auto& circle : circles) {
		auto veloc = circle.veloc;

		auto& pos = circle.pos;
		pos.x += veloc.x * distance;
		pos.y += veloc.y * distance;
	}

	last_pos_update = (*ResourceManager::getInstance())->getElapsedTime();
}


sf::Color Background::getCurrentPrimaryColor() const {
	return cur_prim_color;
}


sf::Color Background::getCurrentSecondaryColor() const {
	return cur_second_color;
}


int Background::getNumberOfCircles() const {
	return circles.size();
}


void Background::update() {
	calCurrentColor();
	calCurrentCirclesPos();
}


void Background::setNextColor(const Color next_prim_color, const Color next_second_color, const sf::Time transition_duration) {
	if (next_prim_color.isValid())
		this->des_prim_color = next_prim_color;
	
	if (next_second_color.isValid()) {
		this->des_second_color = next_second_color;
		this->des_second_color.a = TRANSPARENT_ALPHA;
	}

	if (transition_duration.asSeconds() > 0) {
		this->transition_duration = transition_duration;
		last_color_update = (*ResourceManager::getInstance())->getElapsedTime();
	}
}


void Background::setCircleSpeed(const float speed) {
	if (speed > 0) {
		this->circle_speed = speed;
	}
}


void Background::setNextConfig(const AudioVisualCfg::Cfg& cfg) {
	setNextColor(cfg.primary_color, cfg.secondary_color, cfg.transition_duration);
	setCircleSpeed(cfg.bubble_speed);
}


void Background::draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing) {
	renderer->draw(background);

	for (auto& circle : circles) {
		circle_shape.setRadius(circle.radius);
		circle_shape.setOrigin(circle.radius, circle.radius);
		circle_shape.setFillColor(cur_second_color);
		circle_shape.setPosition(circle.pos);
		
		renderer->draw(circle_shape);
	}

	Scene::draw(renderer, is_focusing);
	volume->draw(renderer, is_focusing);
}

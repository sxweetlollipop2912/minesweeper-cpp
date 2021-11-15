#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Window.h"


void Window::changeMousePosition(const sf::Vector2i& mouse_position) {
	pos_mouse = mouse_position;

	Scene& scene = map_scene[current_scene];
	ButtonType last_hovered = scene.hoveredButton;

	scene.changeMousePosition(pos_mouse);

	if (scene.hoveredButton == last_hovered) return;

	draw(scene);
}


void Window::registerScene(const SceneType& type, const Scene& scene) {
	map_scene[type] = scene;
}


void Window::setCurrentSceneType(const SceneType& type) {
	current_scene = type;
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
	draw(map_scene[current_scene]);
}


void Window::draw(const sf::Sprite& sprite) {
	render_window.draw(sprite);
}


void Window::draw(const sf::Text& text) {
	render_window.draw(text);
}


void Window::draw(Text& text) {
	text.isDrawing = true;

	draw(text.getSfText());
}


void Window::draw(Button& button, const bool isHovered) {
	button.isDrawing = true;

	if (isHovered == false)
		draw(button.getDefaultSprite());
	else
		draw(button.getHoveredSprite());

	draw(button.label);
}


void Window::draw(Scene& scene) {
	scene.isDrawing = true;

	for (auto i = scene.map_button.begin(); i != scene.map_button.end(); i++) {
		if (i->first != scene.hoveredButton)
			draw(i->second);
		else
			draw(i->second, true);
	}

	for (auto i = scene.map_text.begin(); i != scene.map_text.end(); i++)
		draw(i->second);
}

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Window.h"


void Window::setMousePosition(const sf::Vector2i& pos) {
	pos_mouse = pos;
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


void Window::draw(const Text& text) {
	draw(text.getSfText());
}


void Window::draw(const Button& button, const bool isHovered) {
	if (isHovered == false)
		draw(button.getDefaultSprite());
	else
		draw(button.getHoveredSprite());

	draw(button.label);
}


void Window::draw(const Scene& scene) {
	for (auto i = scene.map_button.begin(); i != scene.map_button.end(); i++)
		draw(i->second);
	for (auto i = scene.map_text.begin(); i != scene.map_text.end(); i++)
		draw(i->second);
}

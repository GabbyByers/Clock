#include "SFML/Graphics.hpp"
#include <vector>
using std::vector;

int main() {
	int screen_width = 450;
	int screen_height = 450;
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Clock", sf::Style::Close);
	sf::Event event;

	float bx = static_cast<float>(screen_width) / 2;
	float by = static_cast<float>(screen_height) / 2;
	float large_radius = bx - 20;
	float small_radius = bx - 80;
	float pi = 3.1415926536;
	vector<sf::Vertex> outer_circle;
	vector<sf::Vertex> inner_circle;

	for (int i = 0; i < 101; i++) {
		float rad = i * (2 * (pi / 100));
		float x = cos(rad);
		float y = sin(rad);
		outer_circle.push_back(sf::Vertex(sf::Vector2f(x * large_radius + bx, y * large_radius + by), sf::Color(0, 0, 0)));
		inner_circle.push_back(sf::Vertex(sf::Vector2f(x * small_radius + bx, y * small_radius + by), sf::Color(0, 0, 0)));
	}

	vector<sf::Vertex> line_segments;
	int division = 6;
	for (int i = 0; i < 12 * division; i++) {
		sf::Color color = sf::Color(0, 0, 0);
		if (i % division != 0) { color = sf::Color(200, 200, 200); }
		float rad = i * ((2 * pi) / (12 * division));
		float x0 = cos(rad) * small_radius;
		float y0 = sin(rad) * small_radius;
		float x1 = cos(rad) * large_radius;
		float y1 = sin(rad) * large_radius;
		line_segments.push_back(sf::Vertex(sf::Vector2f(x0 + bx, y0 + by), color));
		line_segments.push_back(sf::Vertex(sf::Vector2f(x1 + bx, y1 + by), color));
	}

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color(255, 255, 255));
		window.draw(&outer_circle[0], outer_circle.size(), sf::LineStrip);
		window.draw(&inner_circle[0], inner_circle.size(), sf::LineStrip);
		window.draw(&line_segments[0], line_segments.size(), sf::Lines);
		window.display();
	} return 0;
}

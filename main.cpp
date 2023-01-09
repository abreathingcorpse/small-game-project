#include <SFML/Graphics.hpp>
#include <iostream>
#include "support.h"

// Declaring the namespaces
using namespace sf;
using namespace std;

// Game Loop parameters
float framerate = 1.f/60; // .f forces it to be a float, so that it's not 0
Time dt = sf::seconds(framerate);
sf::Clock game_clock;
float v0 = 160.0; // in px / s
Vector2f velocity; // velocity vector
float rotation_angle = 0; // in degrees

int main() {

	// Declare the window
	RenderWindow window;
	settings.antialiasingLevel = 8;

	// TODO: toggle_fullscreen currently (re)creates the RenderWindow, clears and display
	// 	 It actually should only toggle the fullscreen_flag
	toggle_fullscreen(window, fullscreen_flag);

	// Make the character's ConvexShape a Point Count of 4 and define those points.
	// NOTE: this needs to be inside the main(), since main() runs before any calls outside
	// of its scope
	character.setPointCount(4);
	character.setPoint(0, Vector2f(TRIANGLE_BASE / 2, TRIANGLE_HEIGHT - TAILCUT_HEIGHT ));
	character.setPoint(1, Vector2f(0.0, TRIANGLE_HEIGHT));
	character.setPoint(2, Vector2f(TRIANGLE_BASE / 2, 0));
	character.setPoint(3, Vector2f(TRIANGLE_BASE, TRIANGLE_HEIGHT));
	// The rotations look clunkly, so I'll try to change the origin of the character
	character.setOrigin(TRIANGLE_BASE / 2, TRIANGLE_HEIGHT / 2);
	// The update to the origin cuts the initial print of the character on the RenderWindow
	character.setPosition(TRIANGLE_BASE / 2, TRIANGLE_HEIGHT / 2);

	// run the program as long as the window is open
	while (window.isOpen()) {

		window.clear(Color::Black);
		window.draw(character);
		window.display();

		// check all the window's events that were triggered since the last iteration of
		// the game loop
		Event event;

		// TODO: Implement the A and W keys as well 
		sf::Time elapsed = game_clock.restart();
		while (elapsed.asMicroseconds() > 0) {
			Time deltaTime = min(dt, elapsed);
		
			velocity = Vector2f(0,0); // set the vector to default before processing

			// TODO: This happens even if the window is out of focus. It shouldn't
			// TODO: Diagonal movement is quicker than movement along a single axis,
			//	I'll need to normalize it
			if (Keyboard::isKeyPressed(Keyboard::D) &&
			!Keyboard::isKeyPressed(Keyboard::A)) {
				cout << "x: " << character.getPosition().x << endl;

				velocity += Vector2f(v0,0);
				cout << "vx: " << velocity.x << endl;

				character.move(Vector2f(velocity.x * deltaTime.asSeconds(),
				velocity.y * deltaTime.asSeconds()));

				// If the player was pressing A and suddenly presses D
				// this woulnd't really be true however, the frames go so fast
				// that it becomes true very quickly
				angle = ( angle + 90.f ) / 2;
				character.setRotation(angle);
			}
			if (Keyboard::isKeyPressed(Keyboard::S) &&
			!Keyboard::isKeyPressed(Keyboard::W)) {
				cout << "y: " << character.getPosition().y << endl;

				velocity += Vector2f(0,v0);

				character.move(Vector2f(velocity.x * deltaTime.asSeconds(),
				velocity.y * deltaTime.asSeconds()));

				// If the player was pressing W and suddenly presses S
				// this woulnd't really be true however, the frames go so fast
				// that it becomes true very quickly
				angle = ( angle + 180.f ) / 2;
				character.setRotation(angle);
			}
			if (Keyboard::isKeyPressed(Keyboard::A) &&
			!Keyboard::isKeyPressed(Keyboard::D)) {
				cout << "x: " << character.getPosition().x << endl;

				velocity += Vector2f(-v0,0);
				cout << "vx: " << velocity.x << endl;

				character.move(Vector2f(velocity.x * deltaTime.asSeconds(),
				velocity.y * deltaTime.asSeconds()));

				// If the player was pressing D and suddenly presses A
				// this woulnd't really be true however, the frames go so fast
				// that it becomes true very quickly
				angle = ( angle + 270.f ) / 2;
				character.setRotation(angle);
			}
			if (Keyboard::isKeyPressed(Keyboard::W) &&
			!Keyboard::isKeyPressed(Keyboard::S)) {
				cout << "y: " << character.getPosition().y << endl;

				velocity += Vector2f(0,-v0);

				character.move(Vector2f(velocity.x * deltaTime.asSeconds(),
				velocity.y * deltaTime.asSeconds()));

				if (Keyboard::isKeyPressed(Keyboard::A) &&
				!Keyboard::isKeyPressed(Keyboard::D)) {
					angle = 315.f;
				} else if (Keyboard::isKeyPressed(Keyboard::D) &&
				!Keyboard::isKeyPressed(Keyboard::A)) {
					angle = 45.f;
				} else { angle = 0.f; }

				character.setRotation(angle);
			}
			elapsed -= deltaTime;
		}

		// TODO: Bounding boxes
		// You'll have to implement Collision Detection sometime

		while (window.pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == Event::Closed) {
				window.close();	
			}
			// The window toggles between the default and fullscreen mode
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::F) {
				fullscreen_flag = !fullscreen_flag;
				toggle_fullscreen(window, fullscreen_flag);
			}
			// TODO:
			// call:
			// static const std::vector<VideoMode>& VideoMode::getFullscreenModes	()
			// returns: Array containing all the supported fullscreen modes
			// When? whenever the key 'V'
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
				character.rotate(angle);
			}
		}
	}

	return 0;
}

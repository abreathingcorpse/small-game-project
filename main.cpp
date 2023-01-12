#include <SFML/Graphics.hpp>
#include <iostream> // for debugging
#include "support.h"
#include <cmath> // for normalizing the velocity vector

// Declaring the namespaces
using namespace sf;
using namespace std;

// Game Loop parameters
float framerate = 1.f/60; // .f forces it to be a float, so that it's not 0
Time dt = sf::seconds(framerate);
sf::Clock game_clock;
float v0 = 160.0; // in px / s
Vector2f direction; // vector that's modified by pressing WASD
Vector2f unitary_velocity; // normalized velocity vector
Vector2f velocity; // velocity vector
float rotation_angle = 0; // in degrees

void keyboard_movement(sf::Time elapsed) {

	while (elapsed.asMicroseconds() > 0) {
		Time deltaTime = min(dt, elapsed);
	
		direction = Vector2f(0,0); // set the vector to default before processing

		// TODO: This happens even if the window is out of focus. It shouldn't
		if (Keyboard::isKeyPressed(Keyboard::D) &&
		!Keyboard::isKeyPressed(Keyboard::A)) {
	//		cout << "x: " << character.getPosition().x << endl;
	//		cout << "y: " << character.getPosition().y << endl;

			// Pressing D modifies the direction vector,
			// which is then normalized and multiplied by v0
			direction += Vector2f(1,0);
			float direction_magnitude = sqrt ( pow(direction.x,2) + 
			pow(direction.y,2)  );
			unitary_velocity = direction / direction_magnitude;
	//		cout << "ux: " << unitary_velocity.x << endl;
	//		cout << "uy: " << unitary_velocity.y << endl;
			velocity = v0 * unitary_velocity;
	//		cout << "vx: " << velocity.x << endl;
	//		cout << "vy: " << velocity.y << endl;

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
	//		cout << "x: " << character.getPosition().x << endl;
	//		cout << "y: " << character.getPosition().y << endl;

			// Pressing S modifies the direction vector,
			// which is then normalized and multiplied by v0
			direction += Vector2f(0,1);
			float direction_magnitude = sqrt ( pow(direction.x,2) + 
			pow(direction.y,2)  );
			unitary_velocity = direction / direction_magnitude;
	//		cout << "ux: " << unitary_velocity.x << endl;
	//		cout << "uy: " << unitary_velocity.y << endl;
			velocity = v0 * unitary_velocity;
	//		cout << "vx: " << velocity.x << endl;
	//		cout << "vy: " << velocity.y << endl;

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

			// Pressing A modifies the direction vector,
			// which is then normalized and multiplied by v0
			direction += Vector2f(-1,0);
			float direction_magnitude = sqrt ( pow(direction.x,2) + 
			pow(direction.y,2)  );
			unitary_velocity = direction / direction_magnitude;
			velocity = v0 * unitary_velocity;

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

			// Pressing W modifies the direction vector,
			// which is then normalized and multiplied by v0
			direction += Vector2f(0,-1);
			float direction_magnitude = sqrt ( pow(direction.x,2) + 
			pow(direction.y,2)  );
			unitary_velocity = direction / direction_magnitude;
			velocity = v0 * unitary_velocity;

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

	} // while elapsed > 0
}

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
	// TODO: Implement a View, because whenever the window is resized, the Character has a
	// different Texture width & height than that of the screen. Since, initially, they had a
	// 1:1 relationship
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

		// get the elapsed time between current and last frame
		sf::Time elapsed = game_clock.restart();
			
		// handle the character movement with the keyboard
		keyboard_movement(elapsed);

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

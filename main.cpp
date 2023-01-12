#include <SFML/Graphics.hpp>
#include <iostream> // for debugging
#include "support.h"
#include "movement.h"

// Declaring the namespaces
using namespace sf;
using namespace std;

sf::Clock game_clock;

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
			
			/* Making the Character rotate by pressing R was more of a test,
			is this truly needed?

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
				character.rotate(angle); // angle was set to 45 at movement.h
			}
			*/

		} // pollEvent
	} // window is open

	return 0;
} // main()

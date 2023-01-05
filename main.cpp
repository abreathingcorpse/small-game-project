
#include <SFML/Graphics.hpp>
#include <iostream>

// Declaring the SFML namespace
using namespace sf;
using namespace std;

// --- Character ---
// Define the constant parameters
float TRIANGLE_BASE = 18.0f;
float TRIANGLE_HEIGHT = 20.0f;
float TAILCUT_HEIGHT = 4.0f; // Must: TAILCUT_HEIGHT < TRIANGLE_HEIGHT

// Declare a ConvexShape for the character
ConvexShape character;
// NOTE: The area before the main() is to declare stuff only,
// any attempts to run anything outside of it will result in an out of scope issue
ContextSettings settings;
// Define the rotation angle
float angle = 45;
// --- # ---

// --- RenderWindow ---
// This is toggled between true/false whenever the player presses F
bool fullscreen_flag = true;
// --- # ---

// Receives the referece of window, as well as the fullscreen_flag
// Toggles between default and Fullscreen mode
void toggle_fullscreen(RenderWindow& window, bool fullscreen_flag) {
	if (fullscreen_flag) {
		VideoMode DesktopVideoMode = VideoMode::getDesktopMode();
		window.create(DesktopVideoMode, "Small Game", Style::Fullscreen, settings);
		window.clear(Color::Black);
		// window.draw(...)
		window.display();
	} else {
		window.create(VideoMode(800,600), "Small Game", Style::Default, settings);
	}
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

		// TODO: Use the sf::Keyboard instead of the Event::KeyPressed
		// https://www.sfml-dev.org/tutorials/2.5/window-inputs.php
		// Keep in mind the character.setRotation(angle), it'll have to be sum of
		// vectors or something. This will require a Game Loop set up
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			character.move(Vector2f(1.0,0));
			character.setRotation(90.f);
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

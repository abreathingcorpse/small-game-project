#include <SFML/Graphics.hpp>
#include <iostream> // for debugging
#include "support.h"
#include "movement.h"

// Declaring the namespaces
using namespace sf;
using namespace std;

sf::Clock game_clock;

// Declare the tile and its size 
CircleShape hexagon;
CircleShape offseted_hexagon;
float hex_size = 20;
// Declare the hexgrid
RenderTexture hexgrid;
// I had to add +2 on the y size because for some reason otherwise it wasn't enough
IntRect hexmap_size(0, 0, 4 * (4 * hex_size), 4 * (4 * (sqrt(3)/2) * hex_size));

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

	// Define the hexagon
	// TODO: Print the offseted hexagon
	hexagon.setRadius(hex_size);
	hexagon.setPointCount(6);
	hexagon.setFillColor(Color::Transparent);
	hexagon.setOutlineThickness(1.f);
	hexagon.setOrigin(sqrt(3)/2.f * hex_size, hex_size);
	hexagon.setRotation(30.f);
	hexagon.setOrigin(hex_size, sqrt(3)/2.f * hex_size);
	hexagon.setPosition(hex_size, sqrt(3)/2.f * hex_size);

	offseted_hexagon.setRadius(hex_size);
	offseted_hexagon.setPointCount(6);
	offseted_hexagon.setFillColor(Color::Transparent);
	offseted_hexagon.setOutlineThickness(1.f);
	offseted_hexagon.setOrigin(sqrt(3)/2.f * hex_size, hex_size);
	offseted_hexagon.setRotation(30.f);
	offseted_hexagon.setOrigin(hex_size, sqrt(3)/2.f * hex_size);
	offseted_hexagon.setPosition( (1+3/2.f) * hex_size, sqrt(3) * hex_size);
	// Define the hexgrid
	if (!hexgrid.create((7/2.f) * hex_size, (3/2.f)*sqrt(3) * hex_size)) { return -1; }
	hexgrid.setRepeated(true);

	// run the program as long as the window is open
	while (window.isOpen()) {


		hexgrid.clear(Color::Black);
		hexgrid.draw(hexagon);
		hexgrid.draw(offseted_hexagon);
		hexgrid.display();

		window.clear(Color::Black);
		
		// Draw the hexgrid RenderTexture
		Sprite hexmap(hexgrid.getTexture(), hexmap_size);
		window.draw(hexmap);

		// Draw the character ConvexShape
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

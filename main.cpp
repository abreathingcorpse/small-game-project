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
//CircleShape offseted_hexagon;
const unsigned int g_hex_size = 20;

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

	// calculate the size of the hexgrid
	Vector2u window_size = window.getSize();

	cout << "window_size_x: " << window_size.x << endl;
	cout << "window_size_y: " << window_size.y << endl;
	
	int delta_x = window_size.x % ( 2*g_hex_size );
	cout << "delta_x: " << delta_x << endl;
	int delta_y = window_size.y % static_cast<int>(( sqrt(3)*g_hex_size ));
	cout << "delta_y: " << delta_y << endl;
	
	/*double delta_y = ceil(sqrt(3)*g_hex_size);
	cout << "double delta_y: " << delta_y << endl;
	int casted_delta_y = static_cast<int>(sqrt(3)*g_hex_size);
	cout << "int delta_y: " << casted_delta_y << endl;*/
	int max_x_hexagons = ceil((window_size.x - delta_x)/(2*g_hex_size));
	int max_y_hexagons = (window_size.y - delta_y)/(sqrt(3)*g_hex_size);

	cout << "n: " << max_x_hexagons << endl;
	cout << "m: " << max_y_hexagons << endl;

	Vector2f hexgrid[max_x_hexagons][max_y_hexagons];
	hexgrid[0][0] = Vector2f(g_hex_size, sqrt(3)/2.f * g_hex_size);
	hexgrid[0][1] = Vector2f(5*g_hex_size/2, sqrt(3) * g_hex_size);
	hexgrid[1][0] = Vector2f(g_hex_size, 3*sqrt(3) * g_hex_size/2);
	hexgrid[1][1] = Vector2f(5*g_hex_size/2, 2*sqrt(3) * g_hex_size);

	// Define the hexagon
	// TODO: Print the offseted hexagon
	hexagon.setRadius(g_hex_size);
	hexagon.setPointCount(6);
	hexagon.setFillColor(Color::Transparent);
	hexagon.setOutlineThickness(1.f);
	hexagon.setOrigin(sqrt(3)/2.f * g_hex_size, g_hex_size);
	hexagon.setRotation(30.f);
	hexagon.setOrigin(g_hex_size, sqrt(3)/2.f * g_hex_size);
	hexagon.setPosition(g_hex_size, sqrt(3)/2.f * g_hex_size);

	// run the program as long as the window is open
	while (window.isOpen()) {

		window.clear(Color::Black);
		

		// Draw the o_0,0 hexagon
//		hexagon.setPosition(g_hex_size, sqrt(3)/2.f * g_hex_size);
		hexagon.setPosition(hexgrid[0][0]);
		window.draw(hexagon);
		// Draw the o_0,1 hexagon
//		hexagon.setPosition(5*g_hex_size/2, sqrt(3) * g_hex_size);
		hexagon.setPosition(hexgrid[0][1]);
		window.draw(hexagon);
		// Draw the o_1,0 hexagon
//		hexagon.setPosition(g_hex_size, 3*sqrt(3) * g_hex_size/2);
		hexagon.setPosition(hexgrid[1][0]);
		window.draw(hexagon);
		// Draw the o_1,1 hexagon
//		hexagon.setPosition( 5*g_hex_size/2, 2*g_hex_size*sqrt(3) );
		hexagon.setPosition(hexgrid[1][1]);
		window.draw(hexagon);

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

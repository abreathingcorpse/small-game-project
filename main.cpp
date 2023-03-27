#include <SFML/Graphics.hpp>
#include <iostream> // for debugging
#include "support.h"
#include "movement.h"
#include "hexgrid.h"

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

	// calculate the size of the hexgrid
	Vector2u max_hexagons = calculate_hexgrid_size(window);

	// Added a +2 for the padding
	Vector2f hexgrid[max_hexagons.y + 2][max_hexagons.x + 2];

	// fill out the positions for the main hexgrid
	// as well as the right and bottom paddings and most of the left padding
	/*for(int i=1;i<max_hexagons.y+2;i++){
		int j=1;
		float a = 0;
		if(i==1 && j==1) {
			hexgrid[1][1] = Vector2f(1, sqrt(3)/2.f) * g_hex_size;
		} else {
			hexgrid[i][1] = hexgrid[i-1][1] + Vector2f(0,sqrt(3)) * g_hex_size;
		}

		// fill out the left padding
		a = - sqrt(3)/2; // set the value for the left padding
		hexgrid[i][0] = hexgrid[i][1] - Vector2f(3/2.f, a) * g_hex_size;

		for(j=2;j<max_hexagons.x+2;j++) {
			if(j%2) { // checks if odd
				a = - sqrt(3)/2;
			} else {
				a = sqrt(3)/2;
			}
			hexgrid[i][j] = hexgrid[i][j-1] + Vector2f(3/2.f, a) * g_hex_size;
		}
	}


	fill_hexgrid(&hexgrid[0][0], max_hexagons);
	
	// loop around the top padding of the hexgrid
	hexgrid[0][1] = hexgrid[1][1] - Vector2f(0,sqrt(3)) * g_hex_size;
	hexgrid[0][0] = hexgrid[0][1] - Vector2f(3/2.f, - sqrt(3)/2) * g_hex_size;
	for(int j=2;j<max_hexagons.x+2;j++) {
		float a = 0;
		if(j%2) { // checks if odd
			a = - sqrt(3)/2;
		} else {
			a = sqrt(3)/2;
		}
		hexgrid[0][j] = hexgrid[0][j-1] + Vector2f(3/2.f, a) * g_hex_size;	
	}*/

	fill_hexgrid(&hexgrid[0][0], max_hexagons);

	// Define the hexagon
	hexagon.setRadius(g_hex_size);
	hexagon.setPointCount(6);
	hexagon.setFillColor(Color::Transparent);
	hexagon.setOutlineThickness(1.f);
	hexagon.setOrigin(sqrt(3)/2.f * g_hex_size, g_hex_size);
	hexagon.setRotation(30.f);
	hexagon.setOrigin(g_hex_size, sqrt(3)/2.f * g_hex_size);
	hexagon.setPosition(g_hex_size, sqrt(3)/2.f * g_hex_size);

//	cout << "Going inside the Game Loop..." << endl;
	// run the program as long as the window is open
	while (window.isOpen()) {

		window.clear(Color::Black);
		
		for(int i=0;i<max_hexagons.y+1;i++){
			for(int j=0;j<max_hexagons.x+1;j++) {
				if (i==0 || j==0){
					// draw the top & left paddings
					hexagon.setPosition(hexgrid[i][j]);
					hexagon.setOutlineColor(Color::Yellow);
					window.draw(hexagon);
					hexagon.setOutlineColor(Color::White);
				} else { // draws the main hexgrid
					hexagon.setPosition(hexgrid[i][j]);
					window.draw(hexagon);
				}
			}
			// draw the right padding
			hexagon.setPosition(hexgrid[i][max_hexagons.x+1]);
			hexagon.setOutlineColor(Color::Yellow);
			window.draw(hexagon);
			hexagon.setOutlineColor(Color::White);
		}

		// Draw the bottom padding
		for(int j=1;j<max_hexagons.x+2;j++) {
			hexagon.setPosition(hexgrid[max_hexagons.y+1][j]);
			hexagon.setOutlineColor(Color::Yellow);
			window.draw(hexagon);
			hexagon.setOutlineColor(Color::White);
		}

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

		} // pollEvent
	} // window is open

	return 0;
} // main()


#include <SFML/Graphics.hpp>
#include <iostream>

// Declaring the SFML namespace
using namespace sf;
using namespace std;

// This is toggled between true/false whenever the player presses F
bool fullscreen_flag = true;

// Receives the referece of window, as well as the fullscreen_flag
// Toggles between default and Fullscreen mode
void toggle_fullscreen(RenderWindow& window, bool fullscreen_flag) {
	if (fullscreen_flag) {
		VideoMode DesktopVideoMode = VideoMode::getDesktopMode();
		window.create(DesktopVideoMode, "Small Game", Style::Fullscreen);
		window.clear(Color::Black);
		// window.draw(...)
		window.display();
	} else {
		window.create(VideoMode(800,600), "Small Game");
	}
}

int main() {
	
	// Declare the window
	RenderWindow window;

	toggle_fullscreen(window, fullscreen_flag);

	// run the program as long as the window is open
	while (window.isOpen()) {

		// check all the window's events that were triggered since the last iteration of
		// the game loop
		Event event;

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
		}
	}

	return 0;
}

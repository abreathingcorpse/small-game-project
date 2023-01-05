#include <SFML/Graphics.hpp>

// Declaring the SMFL namespace
using namespace sf;

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
bool fullscreen_flag = false;
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

#include <SFML/Graphics.hpp>

// Declaring the SMFL namespace
using namespace sf;

// This is toggled between true/false whenever the player presses F
bool fullscreen_flag = false;

// This is used for the antialiasing, otherwise the character doesn't print too well
ContextSettings settings;    

// Receives the referece of window, as well as the fullscreen_flag
// Toggles between default and Fullscreen mode
void toggle_fullscreen(RenderWindow& window, bool fullscreen_flag) {
	if (fullscreen_flag) {
		VideoMode DesktopVideoMode = VideoMode::getDesktopMode();
		window.create(DesktopVideoMode, "Small Game", Style::Fullscreen, settings);
	} else {
		window.create(VideoMode(800,600), "Small Game", Style::Default, settings);
	}
}

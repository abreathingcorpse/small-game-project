#include <iostream> // for debugging
#include <cmath> // for normalizing the velocity vector

// Declaring the namespaces
using namespace sf;
using namespace std;

// Define the constant parameters
float TRIANGLE_BASE = 18.0f;
float TRIANGLE_HEIGHT = 20.0f;
float TAILCUT_HEIGHT = 4.0f; // Must: TAILCUT_HEIGHT < TRIANGLE_HEIGHT

// Declare a ConvexShape for the character
ConvexShape character;

// velocity parameters
float v0 = 160.0; // in px / s
Vector2f direction; // vector that's modified by pressing WASD
Vector2f unitary_velocity; // normalized velocity vector
Vector2f velocity; // velocity vector
float rotation_angle = 0; // in degrees

// Game Loop parameters
float framerate = 1.f/60; // .f forces it to be a float, so that it's not 0
Time dt = sf::seconds(framerate);

void keyboard_movement(sf::Time elapsed) {

	while (elapsed.asMicroseconds() > 0) {
		Time deltaTime = min(dt, elapsed);
	
		direction = Vector2f(0,0); // set the vector to default before processing

		// TODO: This happens even if the window is out of focus. It shouldn't
		if (Keyboard::isKeyPressed(Keyboard::D) &&
		!Keyboard::isKeyPressed(Keyboard::A)) {

			// Pressing D modifies the direction vector,
			// which is then normalized and multiplied by v0
			direction += Vector2f(1,0);
			float direction_magnitude = sqrt ( pow(direction.x,2) + 
			pow(direction.y,2)  );
			unitary_velocity = direction / direction_magnitude;
			velocity = v0 * unitary_velocity;

			character.move(Vector2f(velocity.x * deltaTime.asSeconds(),
			velocity.y * deltaTime.asSeconds()));

			// If the player was pressing A and suddenly presses D
			// this woulnd't really be true however, the frames go so fast
			// that it becomes true very quickly
			rotation_angle = ( rotation_angle + 90.f ) / 2;
			character.setRotation(rotation_angle);
		}
		if (Keyboard::isKeyPressed(Keyboard::S) &&
		!Keyboard::isKeyPressed(Keyboard::W)) {

			// Pressing S modifies the direction vector,
			// which is then normalized and multiplied by v0
			direction += Vector2f(0,1);
			float direction_magnitude = sqrt ( pow(direction.x,2) + 
			pow(direction.y,2)  );
			unitary_velocity = direction / direction_magnitude;
			velocity = v0 * unitary_velocity;

			character.move(Vector2f(velocity.x * deltaTime.asSeconds(),
			velocity.y * deltaTime.asSeconds()));

			// If the player was pressing W and suddenly presses S
			// this woulnd't really be true however, the frames go so fast
			// that it becomes true very quickly
			rotation_angle = ( rotation_angle + 180.f ) / 2;
			character.setRotation(rotation_angle);
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
			rotation_angle = ( rotation_angle + 270.f ) / 2;
			character.setRotation(rotation_angle);
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
				rotation_angle = 315.f;
			} else if (Keyboard::isKeyPressed(Keyboard::D) &&
			!Keyboard::isKeyPressed(Keyboard::A)) {
				rotation_angle = 45.f;
			} else { rotation_angle = 0.f; }

			character.setRotation(rotation_angle);
		}

		elapsed -= deltaTime;

	} // while elapsed > 0
} // keyboard_movement()

#include <SFML/Graphics.hpp>

// Declaring the namespaces
using namespace sf;
using namespace std;

// Declare the tile and its size 
CircleShape hexagon;
//CircleShape offseted_hexagon;
const float g_hex_size = 20;

Vector2u calculate_hexgrid_size(RenderWindow& window) {
	Vector2u window_size = window.getSize();

	int delta_x = window_size.x % static_cast<int>((3/2)*g_hex_size);
	int delta_y = window_size.y % static_cast<int>(( sqrt(3)*g_hex_size ));
	
	int max_x_hexagons = (1/3.f) * (2*window_size.x/g_hex_size - 2*delta_x/g_hex_size - 1);
	int max_y_hexagons = (window_size.y - delta_y)/(sqrt(3)*g_hex_size);

	Vector2u max_hexagons(max_x_hexagons,max_y_hexagons);

	return max_hexagons;

}

void fill_hexgrid(Vector2f* hexgrid, Vector2u max_hexagons) {
	// Define the root hexagon
	*hexgrid = Vector2f(-1/2.f,0) * g_hex_size;
	// Get the size of the hexgrid memory array
	int k_max = (max_hexagons.y + 2) * (max_hexagons.x + 2);
	// Iterate throughout the whole hexgrid memory array
	for(int k = 1; k <= k_max; k++) {
		int i = k / (max_hexagons.x + 2);
		int j = k % (max_hexagons.x + 2);

		if(j == 0) {
			*(hexgrid + k) = *(hexgrid + k - (max_hexagons.x + 2))
					 + Vector2f(0, sqrt(3)) * g_hex_size;
		} else {
			float a = 0;
			if(j%2) { // checks if odd
				a = - sqrt(3)/2;
			} else {
				a = sqrt(3)/2;
			}
			cout << "a: " << a << endl;
			*(hexgrid + k) = *(hexgrid + k - 1) + Vector2f(3/2.f,a) * g_hex_size;
		}

		cout << i << "," << j << " (" << (hexgrid + k)->x << "," << (hexgrid + k)->y << ")"
		     << endl;
	}

}

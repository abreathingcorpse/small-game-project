#include <SFML/Graphics.hpp>

// Declaring the namespaces
using namespace sf;

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

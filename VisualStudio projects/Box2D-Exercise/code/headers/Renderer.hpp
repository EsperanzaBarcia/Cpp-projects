/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */


#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Box2DExercise
{
	class Renderer
	{
	public:

		/**
		*Converts Box2D coordenates to SFML coordinates. Otherwise the scene would look inverted.
		  */
		sf::Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale);

		/**
		* Method to draw shapes on the window
		*/
		void render(b2World& physics_world, sf::RenderWindow& window, float scale);

	};

}
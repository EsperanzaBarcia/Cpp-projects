/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#pragma once

#include <vector>
#include <Body.hpp>
#include <vec2.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include <string>

class Piece;
class World;

namespace Box2DExercise
{
	/**
	* Entity container class
	*/
	class Entity
	{
		/**
		* Reference to world
		*/
		World* world;
	public:
		/**
		*Tag to identify this tag
		*/
		std::string tag;

		/**
		*Start position
		*/
		glm::vec2 startPosition;

		/**
		*limit position
		*/
		glm::vec2 endPosition;

		/**
		*Reference to body
		*/
		std::unique_ptr<Body> body;

		/**
		*Constructor with reference to body
		*/
		Entity(World* worldref, std::string t = "");

		/** Add body to this entity method
		*/
		void AddBody(glm::vec2, BodyType type = BodyType::dynamic_Rb, float angle = 0, glm::vec2 endPos = glm::vec2(0, 0));

	};
}
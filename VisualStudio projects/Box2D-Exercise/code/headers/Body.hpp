/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */
#pragma once

#include <vector>
#include <Box2D/Box2D.h>
#include <vec2.hpp>
#include <SFML/Graphics.hpp>

class World;
class Piece;

namespace Box2DExercise
{
	/**
	*Body type enumeration
	*/
	enum class BodyType
	{
		dynamic_Rb,
		kinematic_Rb,
		static_Rb
	};

	/**
	*Containing class of Body
	*/
	class Body
	{
		/**
		* Reference to world
		*/
		World* world;

		/**
		*Reference to body
		*/
		b2Body* body;


		/**
		* definition of this Body
		*/
		b2BodyDef body_definition;

	public:

		/**
		*Constructor
		*/
		Body(World* worldref, glm::vec2 pos, uintptr_t pointer, BodyType type = BodyType::dynamic_Rb, float angle = 0);

		/**
		*Getter
		*/
		b2Body* getBody()
		{
			return body;
		}

		/**
		* Add circle fixture method
		*/
		void add_circle_piece(glm::vec2 center, float radius, float density, float restitution, float friction);

		/**
		* Add box fixture method
		*/
		void add_box_piece(glm::vec2 pos, glm::vec2 size, float density, float restitution, float friction, float angle = 0);

		/**
		*Add edge fixture method
		*/
		void add_edge_piece(glm::vec2 startPos, glm::vec2 endPos);

		/**
		*Add polygonal fixture method
		*/
		void add_polygon_piece(b2Vec2 vertices[4], int numberOfVertices);
	};
}
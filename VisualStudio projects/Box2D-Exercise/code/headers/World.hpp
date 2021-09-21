/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#pragma once


#include <memory>
#include <vector>
#include <Box2D/Box2D.h>

namespace Box2DExercise
{
	/**
	*Containing class of World
	*/
	class World
	{
	public:
		/**
		*reference to physics world
		*/
		std::unique_ptr< b2World > physics_world;

		/**
		*Constructor
		*/
		World(b2Vec2 gravity);

		/**
		*Method to add a new body to the world
		*/
		b2Body* CreateNewBody(b2BodyDef* bodyDef);

	};
}

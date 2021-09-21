/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#include <World.hpp>

namespace Box2DExercise
{
	World::World(b2Vec2 gravity)
	{
		physics_world = std::unique_ptr<b2World>(new b2World{ gravity });
	}

	b2Body* World::CreateNewBody(b2BodyDef* bodyDef)
	{
		//Body Creation
		return physics_world->CreateBody(bodyDef);
	}
}
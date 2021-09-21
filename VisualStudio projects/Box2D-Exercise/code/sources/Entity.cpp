/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */
#include <World.hpp>
#include <Entity.hpp>


namespace Box2DExercise
{
	Entity::Entity(World* worldref, std::string t)
	{
		body = nullptr;
		world = worldref;
		tag = t;
	}

	void Entity::AddBody(glm::vec2 pos, BodyType type, float angle, glm::vec2 endPos)
	{
		//positions
		startPosition = pos;
		endPosition = endPos;

		//avoiding the use of new
		//body creation 
		body.reset(new Body(world, pos, (uintptr_t)this, type, angle));
	}

}

/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#include <ContactListener.hpp>
#include <Body.hpp>
#include <iterator>

namespace Box2DExercise
{

	void ContactListener::BeginContact(b2Contact* contact)
	{
		//get fixture A
		b2BodyUserData bodyUserDataFixtureA = contact->GetFixtureA()->GetBody()->GetUserData();

		//get fixture B
		b2BodyUserData bodyUserDataFixtureB = contact->GetFixtureB()->GetBody()->GetUserData();

		//access to entities
		Entity* AEntity = (Entity*)bodyUserDataFixtureA.pointer;
		Entity* BEntity = (Entity*)bodyUserDataFixtureB.pointer;

		assert(AEntity != nullptr);
		assert(BEntity != nullptr);

		//If ball and elevator collide, the elevator moves up
		if (AEntity->tag == "elevator" && BEntity->tag == "ball")
		{
			if (AEntity->body.get()->getBody()->GetPosition().y < AEntity->endPosition.y)
			{
				AEntity->body.get()->getBody()->SetLinearVelocity(b2Vec2{ 0,.5f });
				BEntity->body.get()->getBody()->SetAwake(false);
			}
			else
			{
				AEntity->body.get()->getBody()->SetLinearVelocity(b2Vec2{ 0,.0f });
			}
		}
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		//get fixture A
		b2BodyUserData bodyUserDataFixtureA = contact->GetFixtureA()->GetBody()->GetUserData();

		//get fixture B
		b2BodyUserData bodyUserDataFixtureB = contact->GetFixtureB()->GetBody()->GetUserData();

		//access to entities
		Entity* AEntity = (Entity*)bodyUserDataFixtureA.pointer;
		Entity* BEntity = (Entity*)bodyUserDataFixtureB.pointer;

		assert(AEntity != nullptr);
		assert(BEntity != nullptr);


		//If ball and elevator end colliding, the elevator moves down
		if (AEntity->tag == "elevator" && BEntity->tag == "ball")
		{
			if (AEntity->body.get()->getBody()->GetPosition().y >= AEntity->startPosition.y)
				AEntity->body.get()->getBody()->SetLinearVelocity(b2Vec2{ 0,-.5f });
			else
			{
				AEntity->body.get()->getBody()->SetLinearVelocity(b2Vec2{ 0,.0f });
			}
			BEntity->body.get()->getBody()->SetAwake(true);
		}
	}

}
/*
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#include <map>
#include <memory>
#include <string>
#include <Joint.hpp>
#include <Entity.hpp>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "..\headers\InputProcesser.hpp"

namespace Box2DExercise
{
	void InputProcesser::AddEntity(Entity* entity)
	{
		//Adds an entity to list
		entities.push_back(entity);
	}

	void InputProcesser::AddJoint(Joint* joint)
	{
		//Adds a joint to list
		joints.push_back(joint);
	}

	void InputProcesser::MoveBody(Body& b, glm::vec2 impulse)
	{
		//Moves the body
		b.getBody()->ApplyLinearImpulse(b2Vec2{ impulse.x,impulse.y }, b.getBody()->GetLocalCenter(), true);
	}

	void InputProcesser::MoveJoint(Joint& j, float speed)
	{
		//Necessary casting to access properties
		b2RevoluteJoint* joint = dynamic_cast<b2RevoluteJoint*>(&j.getJoint());

		//activates the joint
		if (joint != nullptr)
			joint->SetMotorSpeed(speed);

		else
		{
			if (j.tag == 3)// car piston joint 
			{
				b2PrismaticJoint* joint2 = dynamic_cast<b2PrismaticJoint*>(&j.getJoint());
				joint2->SetMotorSpeed(speed);
			}
		}
	}

	bool InputProcesser::process(sf::Window& window, float motorSpeed, glm::vec2 impulse)
	{
		sf::Event event;
		//window events
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
					//In case of pressing left key
				case sf::Keyboard::Left:
				{
					//Moves car joints (wheels)
					assert(joints.size() > 0);
					for (Joint* joint : joints)
						if (joint->tag == 0)
							MoveJoint(*joint, motorSpeed);
					break;
				}
				//In case of pressing right key
				case sf::Keyboard::Right:
				{
					//Moves car joints (wheels)
					assert(joints.size() > 0);
					for (Joint* joint : joints)
						if (joint->tag == 0)
							MoveJoint(*joint, -(motorSpeed));
					break;
				}
				//In case of pressing space key
				case sf::Keyboard::Space:
				{
					//Applies impulse to piston
					assert(joints.size() > 0);
					for (Joint* joint : joints)
					{
						if (joint->tag == 3)
							MoveJoint(*joint, 8.f);
					}

					break;
				}
				}

				break;
			}

			//Al forces cancel when we release the key
			case sf::Event::KeyReleased:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
				{
					assert(joints.size() > 0);
					for (Joint* joint : joints)
						MoveJoint(*joint, 0);

					break;
				}
				case sf::Keyboard::Right:
				{
					assert(joints.size() > 0);
					for (Joint* joint : joints)
						MoveJoint(*joint, 0);

					break;
				}
				}

				break;
			}
			//Ends the execution if we press close
			case sf::Event::Closed:
			{
				return true;
			}
			}
		}

		return false;
	}

}
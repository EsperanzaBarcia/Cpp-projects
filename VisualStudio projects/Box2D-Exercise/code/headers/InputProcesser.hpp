/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#pragma once

#include <map>
#include <string>
#include <list>
#include <vec2.hpp>
#include <SFML/Window.hpp>

class Entity;

namespace Box2DExercise
{
	/**
	Class to handle input events
	*/
	class InputProcesser
	{
		/**
		*Entities moved by input
		*/
		std::list < Entity* >entities;

		/**
		*Joints moved by input
		*/
		std::list < Joint* >joints;

	public:

		/**
		*Method to add an entity to the list
		*/
		void AddEntity(Entity* entity);

		/**
		*Method to add a joint to the list
		*/
		void AddJoint(Joint* entity);

		/**
		* Method to move a body
		*/
		void MoveBody(Body& b, glm::vec2 impulse);

		/**
		* Method to activate a joint
		*/
		void MoveJoint(Joint& j, float speed);

		/**
		*Input processer
		*/
		bool process(sf::Window& window, float motorSpeed, glm::vec2 impulse);
	};
}
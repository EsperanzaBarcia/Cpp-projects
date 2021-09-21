/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#pragma once

#include <Box2D/Box2D.h>
#include <World.hpp>
#include <Body.hpp>
#include <memory>

namespace Box2DExercise
{
	/**
	*Containing class of Joint
	*/
	class Joint
	{
		/**
		*Reference to b2joint
		*/
		b2Joint* joint = nullptr;
	public:

		/**
		*Tag to identify this joint
		*/
		int tag = 0;

		/**
		*Method to make this joint a revolute joint
		*/
		void create_revolute_joint(World& physics_world, std::unique_ptr<Body>& body_a, std::unique_ptr<Body>& body_b, glm::vec2 localAnchorA = glm::vec2{ 0,0 }, glm::vec2 localAnchorB = glm::vec2{ 0,0 }, bool enable_motor = false, bool collideConnected = false,
			bool enable_limit = false, float maxMotorTorque = 0, float motorSpeed = 0, float lowerAngle = 0, float upperAngle = 0, int tag = 0);

		/**
		*Method to make this joint a distance joint
		*/
		void create_distance_joint(World& physics_world, std::unique_ptr<Body>& body_a, std::unique_ptr<Body>& body_b, glm::vec2 localAnchorA = glm::vec2{ 0,0 }, glm::vec2 localAnchorB = glm::vec2{ 0,0 }, bool collideConnected = false, int tag = 0);

		/**
		*Method to make this joint a prismatic joint
		*/
		void create_prismatic_joint(World& physics_world, std::unique_ptr<Body>& body_a, std::unique_ptr<Body>& body_b, glm::vec2 localAnchorA, glm::vec2 localAnchorB, glm::vec2 localAxis = glm::vec2(1.f, 0.f), bool collideConnected = false,
			bool enable_limit = false, float lowerTranslation = 0.0f, float upperTranslation = 0.0f, bool enableMotor = false, float maxMotorForce = 0.0f, float motorSpeed = 0.0f, int tag = 0);

		/**
		*Getters
		*/
		b2Joint& getJoint();

	};
}
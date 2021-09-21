/*
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#include <memory>
#include <Joint.hpp>

namespace Box2DExercise
{
	void Joint::create_revolute_joint(World& physics_world, std::unique_ptr<Body>& body_a, std::unique_ptr<Body>& body_b, glm::vec2 localAnchorA, glm::vec2 localAnchorB, bool enable_motor, bool collideConnected,
		bool enable_limit, float maxMotorTorque, float motorSpeed, float lowerAngle, float upperAngle, int t)
	{
		//definition and settings
		b2RevoluteJointDef joint_def;

		joint_def.bodyA = body_a->getBody();
		joint_def.bodyB = body_b->getBody();
		joint_def.enableMotor = enable_motor;
		joint_def.enableLimit = enable_limit;

		joint_def.collideConnected = collideConnected;

		joint_def.localAnchorA.Set(localAnchorA.x, localAnchorA.y);
		joint_def.localAnchorB.Set(localAnchorB.x, localAnchorB.y);

		joint_def.lowerAngle = lowerAngle;
		joint_def.maxMotorTorque = maxMotorTorque;
		joint_def.motorSpeed = motorSpeed;

		joint_def.upperAngle = upperAngle;

		//cast to save on parent class
		auto j = static_cast<b2RevoluteJoint*>(physics_world.physics_world->CreateJoint(&joint_def));

		joint = j;

		tag = t;

	}

	void Joint::create_distance_joint(World& physics_world, std::unique_ptr<Body>& body_a, std::unique_ptr<Body>& body_b, glm::vec2 localAnchorA, glm::vec2 localAnchorB, bool collideConnected, int t)
	{

		//definition and settings
		b2DistanceJointDef jointDef;

		jointDef.bodyA = body_a->getBody();
		jointDef.bodyB = body_b->getBody();
		jointDef.localAnchorA.Set(localAnchorA.x, localAnchorA.y);
		jointDef.localAnchorB.Set(localAnchorB.x, localAnchorB.y);

		jointDef.collideConnected = collideConnected;

		//cast to save on parent class
		auto j = static_cast<b2DistanceJoint*>(physics_world.physics_world->CreateJoint(&jointDef));

		joint = j;

		tag = t;
	}

	void Joint::create_prismatic_joint(World& physics_world, std::unique_ptr<Body>& body_a, std::unique_ptr<Body>& body_b, glm::vec2 localAnchorA, glm::vec2 localAnchorB, glm::vec2 localAxis, bool collideConnected,
		bool enable_limit, float lowerTranslation, float upperTranslation, bool enable_motor, float maxMotorForce, float motorSpeed, int t)
	{
		//definition and settings
		b2PrismaticJointDef joint_def;

		joint_def.bodyA = body_a->getBody();
		joint_def.bodyB = body_b->getBody();
		joint_def.enableMotor = enable_motor;
		joint_def.enableLimit = enable_limit;

		joint_def.localAxisA.Set(localAxis.x, localAxis.y);

		joint_def.collideConnected = collideConnected;

		joint_def.localAnchorA.Set(localAnchorA.x, localAnchorA.y);
		joint_def.localAnchorB.Set(localAnchorB.x, localAnchorB.y);

		joint_def.lowerTranslation = lowerTranslation;
		joint_def.upperTranslation = upperTranslation;
		joint_def.maxMotorForce = maxMotorForce;
		joint_def.motorSpeed = motorSpeed;

		//cast to save on parent class
		auto j = static_cast<b2PrismaticJoint*>(physics_world.physics_world->CreateJoint(&joint_def));

		joint = j;

		tag = t;

	}

	b2Joint& Joint::getJoint()
	{
		return *joint;
	}
}

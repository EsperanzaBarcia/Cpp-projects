/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 *
 * In this exercise, the ball must get to the V by the use of the mechanisms
 * The libraries used are SFMl an Box2D
 *
 *
 */

#include <memory>
#include <vector>
#include <World.hpp>
#include <Body.hpp>
#include <Joint.hpp>
#include <ContactListener.hpp>
#include <Entity.hpp>
#include <InputProcesser.hpp>

#include <Renderer.hpp>
#include <chrono>
#include <vec2.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;
using namespace glm;
using namespace Box2DExercise;

int main()
{
	//window creation
	RenderWindow window(VideoMode(1024, 720), "Practica animacion 3D", Style::Titlebar | Style::Close, ContextSettings(32));

	window.setVerticalSyncEnabled(true);

	//world creation
	Box2DExercise::World world(b2Vec2{ 0, -10.f });

	//collisions control
	ContactListener contactListener;
	world.physics_world->SetContactListener(&contactListener);

	//velocities
	//car motor
	float carSpeed = 8;

	//ball throw force
	vec2 ballJumpForce = { 0, .1f };

	//grabber motor speed
	float hookJointForce = 10;

	//grabber max wait time
	float maxWaitingTime = .5f;

	//renderer
	Renderer renderer;


#pragma region Limits

	//scene corner coordinates
	vec2 bottomLeft(0.01f, 0.f);
	vec2 topLeft(0.01f, 8.f);

	vec2 bottomRight(5.1f, 0.f);
	vec2 topRight(5.1f, 8.f);

	//scene limits
	Box2DExercise::Entity leftLimit(&world);
	leftLimit.AddBody(vec2(topLeft.x, 0), BodyType::static_Rb);
	leftLimit.body->add_edge_piece(bottomLeft, topLeft);

	Box2DExercise::Entity rightLimit(&world);
	rightLimit.AddBody(vec2(topRight.x, 0), BodyType::static_Rb);
	rightLimit.body->add_edge_piece(topRight, bottomRight);

	Box2DExercise::Entity bottomLimit(&world);
	bottomLimit.AddBody(vec2(0, bottomLeft.y), BodyType::static_Rb);
	bottomLimit.body->add_edge_piece(bottomLeft, bottomRight);

	Box2DExercise::Entity topLimit(&world);
	topLimit.AddBody(vec2(0, topLeft.y), BodyType::static_Rb);
	topLimit.body->add_edge_piece(topLeft, topRight);

#pragma endregion

#pragma region Ball

	//Ball creations
	Box2DExercise::Entity ball(&world, "ball");
	ball.AddBody(vec2(.5f, 3.f), BodyType::dynamic_Rb);
	ball.body->add_circle_piece(vec2(0, 0), .09f, 1.f, 0.f, .1f);

#pragma endregion

#pragma region Scenery

	//polygon vertices
	b2Vec2 vertices[4];

	vertices[0].Set(0.f, 0.f);
	vertices[1].Set(0.f, .7f);
	vertices[2].Set(1.3f, .7f);
	vertices[3].Set(2.2f, 0.f);

	Box2DExercise::Entity floorPolygon(&world);
	floorPolygon.AddBody(vec2(0, 0), BodyType::static_Rb);
	floorPolygon.body->add_polygon_piece(vertices, 4);
	floorPolygon.body->add_box_piece(vec2(2.f, 0.f), vec2(13.f, 1.f), .5f, .5f, .5f);

	//Middle platform
	Box2DExercise::Entity rampBody(&world);
	rampBody.AddBody(vec2(5.5f, 4.25f), BodyType::static_Rb, .8f);
	rampBody.body->add_box_piece(vec2(0, 0), vec2(3.f, .2f), .5f, .2f, .2f);

	Box2DExercise::Entity platformBody(&world);
	platformBody.AddBody(vec2(7.5f, 5.3f), BodyType::static_Rb);
	platformBody.body->add_box_piece(vec2(0, 0), vec2(2.f, .2f), .5f, .2f, .2f);

	Box2DExercise::Entity platform(&world);
	platform.AddBody(vec2(4.f, 3.2f), BodyType::static_Rb);
	platform.body->add_box_piece(vec2(0, 0), vec2(3.f, .2f), .5f, .2f, .2f);

	//V shape
	Box2DExercise::Entity leftV(&world);
	leftV.AddBody(vec2(.55f, 5.f), BodyType::static_Rb, -.8f);
	leftV.body->add_box_piece(vec2(0, 0), vec2(1.f, .2f), .5f, .2f, .2f);

	//right body
	Box2DExercise::Entity rightV(&world);
	rightV.AddBody(vec2(1.1f, 5.f), BodyType::static_Rb, .8f);
	rightV.body->add_box_piece(vec2(0, 0), vec2(1.f, .2f), .5f, .2f, .2f);

	//V joint
	Joint vjoint;
	vjoint.create_revolute_joint(world, leftV.body, rightV.body, vec2(.5f, 0), vec2(.5f, 0));

	//elevators limits
	b2Vec2 maxRightElevatorPosition = platformBody.body->getBody()->GetPosition();

	b2Vec2 maxLeftElevatorPosition = rightV.body->getBody()->GetPosition();

	// right elevator
	Box2DExercise::Entity rightElevator(&world, "elevator");
	rightElevator.AddBody(vec2(10.f, .15f), BodyType::kinematic_Rb, 0.f, vec2(maxRightElevatorPosition.x, maxRightElevatorPosition.y));
	rightElevator.body->add_box_piece(vec2(0, 0), vec2(3.f, .25f), .5f, .2f, 1.f);

	// left elevator
	Box2DExercise::Entity leftElevator(&world, "elevator");
	leftElevator.AddBody(vec2(2.3f, 3.2f), BodyType::kinematic_Rb, 0, vec2(maxLeftElevatorPosition.x, maxLeftElevatorPosition.y));
	leftElevator.body->add_box_piece(vec2(0, 0), vec2(1.5f, .2f), .5f, .75f, 1.f);


#pragma endregion

#pragma region Car

	//Structure
	Box2DExercise::Entity Car(&world, "car");
	Car.AddBody(vec2(.3f, 1.f), BodyType::dynamic_Rb);
	Car.body->add_box_piece(vec2(0, 0), vec2(1.f, .5f), 1.f, 0.f, .5f);
	Car.body->add_box_piece(vec2(-.4f, .4f), vec2(.1f, .4f), 1.f, 0, .2f);
	Car.body->add_box_piece(vec2(.4f, .4f), vec2(.1f, .4f), 1.f, 0, .2f);

	//Piston 
	Box2DExercise::Entity jumper(&world);
	jumper.AddBody(vec2(.7f, 2.f), BodyType::dynamic_Rb);
	jumper.body->add_box_piece(vec2(0, 0), vec2(.7f, .1f), 1.f, 0.f, .5f);


	//Wheels
	//Left wheel
	Box2DExercise::Entity LeftWheel(&world);
	LeftWheel.AddBody(vec2(.5f, 1.f), BodyType::dynamic_Rb);
	LeftWheel.body->add_circle_piece(vec2(0, 0), .2f, 3.f, .2f, .5f);

	//right wheel
	Box2DExercise::Entity rightWheel(&world);
	rightWheel.AddBody(vec2(1.f, 1.f), BodyType::dynamic_Rb);
	rightWheel.body->add_circle_piece(vec2(0, 0), .2f, 3.f, .2f, .5f);

	//Joints
	Joint leftWheelJoint;

	Joint rightWheelJoint;

	Joint carPistonJoint;

	//joints between car and wheels
	leftWheelJoint.create_revolute_joint(world, Car.body, LeftWheel.body, vec2(-.35f, -.5f), vec2(0, 0), true, true, false, 5.f, 0);

	rightWheelJoint.create_revolute_joint(world, Car.body, rightWheel.body, vec2(.35f, -.5f), vec2(0, 0), true, true, false, 5.f, 0);

	//piston
	carPistonJoint.create_prismatic_joint(world, Car.body, jumper.body, vec2(.0f, 1.5f), vec2(0.f, .5f), vec2(0.f, .2f), false, true, -.8f, -.6f, true, 10.f, -8.f, 3);

	b2PrismaticJoint* carPistonJoint2 = dynamic_cast<b2PrismaticJoint*>(&carPistonJoint.getJoint());


#pragma endregion

#pragma region Grabber

	//Base Structure   |
	//				  / \  
	Box2DExercise::Entity hook(&world);
	hook.AddBody(vec2(4, 3), BodyType::dynamic_Rb);
	hook.body->add_box_piece(vec2(0, 0), vec2(.1f, .5f), .5f, 0, .2f);
	hook.body->add_box_piece(vec2(.2f, -.3f), vec2(.1f, .5f), 1.f, 0, 0.f, .9f);

	//Grabber 
	//part 1
	hook.body->add_box_piece(vec2(-.2f, -.3f), vec2(.1f, .5f), 1.f, 0, 0, -.9f);

	Box2DExercise::Entity lefthookPiece2(&world);
	lefthookPiece2.AddBody(vec2(3, 2), BodyType::dynamic_Rb);
	lefthookPiece2.body->add_box_piece(vec2(0, 0), vec2(.1f, .4f), 1.f, 0, 0.f, .8f);

	Box2DExercise::Entity righthookPiece2(&world);
	righthookPiece2.AddBody(vec2(3.5f, 2.f), BodyType::dynamic_Rb);
	righthookPiece2.body->add_box_piece(vec2(0, 0), vec2(.1f, .4f), 1.f, 0, 0.f, -.8f);


	//Joints
	//Grabber with upper body
	Joint hookPlatformJoint;

	//it moves from side to side
	hookPlatformJoint.create_prismatic_joint(world, platform.body, hook.body, vec2(0, 0), vec2(0, .4f), vec2(1.f, 0.f), false,
		true, -1.2f, 1.5f, true, 5, .5f);

	//grabber arm
	Joint hookleftArmJoint;
	hookleftArmJoint.create_revolute_joint(world, hook.body, lefthookPiece2.body, vec2(-.25f, -.5f), vec2(0, 0), true,
		false, true, 10.f, 1.f, -.5f, .5f);

	//grabber arm
	Joint hookrightArmJoint;
	hookrightArmJoint.create_revolute_joint(world, hook.body, righthookPiece2.body, vec2(.25, -.5f), vec2(0, 0), true,
		false, true, 10.f, -1.f, -.5f, .5f);

	//conversions to use them later
	b2PrismaticJoint* joint = dynamic_cast<b2PrismaticJoint*>(&hookPlatformJoint.getJoint());

	b2RevoluteJoint* leftArmJoint = dynamic_cast<b2RevoluteJoint*>(&hookleftArmJoint.getJoint());

	b2RevoluteJoint* rightArmJoint = dynamic_cast<b2RevoluteJoint*>(&hookrightArmJoint.getJoint());


#pragma endregion

#pragma region Swing

	//base
	Box2DExercise::Entity ToyBase(&world);
	ToyBase.AddBody(vec2(5.f, .5f), BodyType::dynamic_Rb);
	ToyBase.body->add_box_piece(vec2(0, 0), vec2(.2f, .2f), 10.f, 0.f, 1.f);

	Box2DExercise::Entity stickBody(&world);
	stickBody.AddBody(vec2(5.4f, 1.f), BodyType::dynamic_Rb);
	stickBody.body->add_box_piece(vec2(0, 0), vec2(.05f, 1.f), .1f, 0, 1.f);

	//joint
	Joint thisJoint;
	thisJoint.create_revolute_joint(world, ToyBase.body, stickBody.body, vec2(0.f, 0.f), vec2(-0.15f, 0.f), false, true, false, 0.f, -2.f);

#pragma endregion

#pragma region Piston

	Box2DExercise::Entity PistonBase(&world);
	PistonBase.AddBody(vec2(10.f, 5.6f), BodyType::dynamic_Rb);
	PistonBase.body->add_box_piece(vec2(-.1f, 0), vec2(.2f, .1f), 1.f, 0, .2f);
	PistonBase.body->add_box_piece(vec2(-.5f, 0), vec2(1.f, .1f), 1.f, 0, .2f);

	//joint
	//it moves from side to side
	Joint pistonJoint;
	pistonJoint.create_prismatic_joint(world, rightLimit.body, PistonBase.body, vec2(7.f, 5.6f), vec2(0, 0), vec2(1.f, 0.f), false, true, -2.5f, 1.f, true, 100.f, 5.f);

	b2PrismaticJoint* pistonPrismJoint = dynamic_cast<b2PrismaticJoint*>(&pistonJoint.getJoint());

#pragma endregion

#pragma region Pusher

	Box2DExercise::Entity PusherBase(&world);
	PusherBase.AddBody(vec2(7.f, 6.f), BodyType::dynamic_Rb);
	PusherBase.body->add_box_piece(vec2(0, 0), vec2(.2f, .2f), 1.f, 0, .2f);
	PusherBase.body->add_box_piece(vec2(0, 0), vec2(.05f, 5.4f), .2f, 0, .2f);

	//joint
	Joint pusherBaseJoint;
	pusherBaseJoint.create_revolute_joint(world, topLimit.body, PusherBase.body, vec2(3.f, .2f), vec2(0.f, 0), true, false, false, 100.f, -2.f);

#pragma endregion


	const float physics_to_graphics_scale = 100.f;      // Escala para pasar de unidades de física a unidades de gráficos

	const float target_fps = 60.f;                     // Cuántos fotogramas por segundo se busca conseguir
	const float target_time = 1.f / target_fps;         // Duración en segundos de un fotograma a la tasa deseada

	float delta_time = target_time;                     // Previsión de la duración del fotograma actual
	bool  exit = false;

	Clock timer;

	//input processer
	InputProcesser processer;
	processer.AddJoint(&leftWheelJoint);
	processer.AddJoint(&rightWheelJoint);
	processer.AddJoint(&carPistonJoint);


	float mytimer = 0;

	//bool to know if grabber is waiting
	bool waiting = false;

	do
	{
		timer.restart();

		// Process input events:
		exit = processer.process(window, carSpeed, ballJumpForce);

		// Update:

		world.physics_world->Step(delta_time, 8, 4);

		//Right elevator top limit 
		if (rightElevator.body->getBody()->GetPosition().y >= maxRightElevatorPosition.y)
		{
			rightElevator.body->getBody()->SetLinearVelocity(b2Vec2{ 0,0 });
		}

		//Left elevator top limit  
		if (leftElevator.body->getBody()->GetPosition().y >= maxLeftElevatorPosition.y + .5f)
		{
			leftElevator.body->getBody()->SetLinearVelocity(b2Vec2{ 0,0 });
		}

		//Right elevator bottom limit 
		if (rightElevator.body->getBody()->GetPosition().y <= rightElevator.startPosition.y)
		{
			rightElevator.body->getBody()->SetLinearVelocity(b2Vec2{ 0,0 });
		}

		//Left elevator bottom limit 
		if (leftElevator.body->getBody()->GetPosition().y <= leftElevator.startPosition.y)
		{
			leftElevator.body->getBody()->SetLinearVelocity(b2Vec2{ 0,0 });
		}

		//direction change 
		if (pistonPrismJoint->GetJointTranslation() >= pistonPrismJoint->GetUpperLimit()
			|| pistonPrismJoint->GetJointTranslation() <= pistonPrismJoint->GetLowerLimit())
		{
			pistonPrismJoint->SetMotorSpeed(-(pistonPrismJoint->GetMotorSpeed()));
		}

		//direction change 
		if (carPistonJoint2->GetJointTranslation() >= carPistonJoint2->GetUpperLimit()
			|| carPistonJoint2->GetJointTranslation() < carPistonJoint2->GetLowerLimit())
		{
			carPistonJoint2->SetMotorSpeed(-5.f);

		}

		//Grabber waiting
		if (waiting)
		{
			mytimer += delta_time;
		}

		//direction change 
		else if (joint->GetJointTranslation() > joint->GetUpperLimit())
		{
			waiting = true;
			leftArmJoint->SetMotorSpeed(-hookJointForce);
			rightArmJoint->SetMotorSpeed(hookJointForce);
		}

		//direction change 
		else if (joint->GetJointTranslation() < joint->GetLowerLimit())
		{
			waiting = true;
			leftArmJoint->SetMotorSpeed(-hookJointForce);
			rightArmJoint->SetMotorSpeed(hookJointForce);

		}

		//Grabber timer 
		if (mytimer >= .5f)
		{
			mytimer = 0;
			waiting = false;
			joint->SetMotorSpeed(-(joint->GetMotorSpeed()));

			leftArmJoint->SetMotorSpeed(hookJointForce);
			rightArmJoint->SetMotorSpeed(-hookJointForce);

		}

		// Render:

		window.clear();

		renderer.render(*world.physics_world, window, physics_to_graphics_scale);

		window.display();

		float elapsed = timer.getElapsedTime().asSeconds();

		if (elapsed < target_time)
		{
			sleep(seconds(target_time - elapsed));
		}

		delta_time = timer.getElapsedTime().asSeconds();
	} while (!exit);

	return EXIT_SUCCESS;
}

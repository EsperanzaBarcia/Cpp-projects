/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#include <World.hpp>
#include <Entity.hpp>
#include "..\headers\Body.hpp"

namespace Box2DExercise
{
	Body::Body(World* worldRef, glm::vec2 pos, uintptr_t pointer, BodyType type, float angle)
	{
		//reference 
		world = worldRef;

		//type
		switch (type)
		{
		case Box2DExercise::BodyType::dynamic_Rb:
			body_definition.type = b2_dynamicBody;
			break;
		case Box2DExercise::BodyType::kinematic_Rb:
			body_definition.type = b2_kinematicBody;
			break;
		case Box2DExercise::BodyType::static_Rb:
			body_definition.type = b2_staticBody;
			break;
		default:
			break;
		}

		//body angle
		body_definition.angle = angle;

		//position
		body_definition.position.Set(pos.x, pos.y);

		//Pointer to entity container of this body
		body_definition.userData.pointer = pointer;

		//Finally, create the body
		body = world->CreateNewBody(&body_definition);
	}

	void Body::add_circle_piece(glm::vec2 center, float radius, float density, float restitution, float friction)
	{
		//Shape creation settings
		b2CircleShape body_shape;

		body_shape.m_radius = radius;
		body_shape.m_p = b2Vec2{ center.x,center.y };

		//Fixture creation settings
		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;
		body_fixture.density = density;
		body_fixture.restitution = restitution;
		body_fixture.friction = friction;

		//Adds the fixture to the body
		body->CreateFixture(&body_fixture);

	}

	void Body::add_box_piece(glm::vec2 pos, glm::vec2 size, float density, float restitution, float friction, float angle)
	{
		//Shape creation settings
		b2PolygonShape body_shape;

		const b2Vec2& center{ pos.x,pos.y };

		body_shape.SetAsBox(size.x / 2, size.y / 2, center, angle);

		//Fixture creation settings 
		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;
		body_fixture.density = density;
		body_fixture.restitution = restitution;
		body_fixture.friction = friction;

		//Adds the fixture to the body
		body->CreateFixture(&body_fixture);
	}

	void Body::add_edge_piece(glm::vec2 startPos, glm::vec2 endPos)
	{
		//Shape creation settings
		b2EdgeShape body_shape;

		body_shape.SetTwoSided(b2Vec2{ startPos.x,startPos.y }, b2Vec2{ endPos.x,endPos.y });// Coordenadas locales respecto al centro del body

		//Fixture creation settings 
		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;

		//Adds the fixture to the body
		body->CreateFixture(&body_fixture);
	}

	void Body::add_polygon_piece(b2Vec2 vertices[4], int numberOfVertices)
	{
		//Shape creation settings
		b2PolygonShape body_shape;

		body_shape.Set(vertices, numberOfVertices);

		//Fixture creation settings 
		b2FixtureDef body_fixture;

		body_fixture.shape = &body_shape;
		body_fixture.density = 1.00f;
		body_fixture.restitution = 0.f;

		//Adds the fixture to the body
		body->CreateFixture(&body_fixture);
	}
}
/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#include <Renderer.hpp>

namespace Box2DExercise
{
	sf::Vector2f Renderer::box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale)
	{
		return sf::Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
	}

	void Renderer::render(b2World& physics_world, sf::RenderWindow& window, float scale)
	{

		float window_height = (float)window.getSize().y;

		// loop along all bodies in scene

		for (b2Body* body = physics_world.GetBodyList(); body != nullptr; body = body->GetNext())
		{
			// obtains body transform

			const b2Transform& body_transform = body->GetTransform();

			// loop along all fixtures in scene

			for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
			{
				// Checks the shape 

				b2Shape::Type shape_type = fixture->GetShape()->GetType();

				if (shape_type == b2Shape::e_circle)
				{
					// Creates the CircleShape:
					b2CircleShape* circle = dynamic_cast<b2CircleShape*>(fixture->GetShape());

					float  radius = circle->m_radius * scale;
					b2Vec2 center = circle->m_p;

					sf::CircleShape shape;

					shape.setPosition(box2d_position_to_sfml_position(b2Mul(body_transform, center), window_height, scale) - sf::Vector2f(radius, radius));

					//Assigns the color
					if (body->GetType() == b2_dynamicBody)
						shape.setFillColor(sf::Color::Magenta);

					else if (body->GetType() == b2_kinematicBody)
						shape.setFillColor(sf::Color::Green);

					else if (body->GetType() == b2_staticBody)
						shape.setFillColor(sf::Color::Blue);


					shape.setOutlineThickness(1);
					shape.setOutlineColor(sf::Color::White);
					shape.setRadius(radius);

					window.draw(shape);
				}
				else
					if (shape_type == b2Shape::e_edge)
					{

						b2EdgeShape* edge = dynamic_cast<b2EdgeShape*>(fixture->GetShape());

						b2Vec2 start = b2Mul(body_transform, edge->m_vertex1);
						b2Vec2 end = b2Mul(body_transform, edge->m_vertex2);


						sf::Vertex line[] =
						{
							sf::Vertex(box2d_position_to_sfml_position(start, window_height, scale), sf::Color::Green),
							sf::Vertex(box2d_position_to_sfml_position(end, window_height, scale), sf::Color::Green),
						};

						window.draw(line, 2, sf::Lines);
					}
					else
						if (shape_type == b2Shape::e_polygon)
						{
							b2PolygonShape* box2d_polygon = dynamic_cast<b2PolygonShape*>(fixture->GetShape());
							sf::ConvexShape       sfml_polygon;

							int number_of_vertices = box2d_polygon->m_count;

							sfml_polygon.setPointCount(number_of_vertices);

							//Assigns the color
							if (body->GetType() == b2_dynamicBody)
								sfml_polygon.setFillColor(sf::Color::Magenta);

							else if (body->GetType() == b2_kinematicBody)
								sfml_polygon.setFillColor(sf::Color::Green);

							else if (body->GetType() == b2_staticBody)
								sfml_polygon.setFillColor(sf::Color::Blue);


							sfml_polygon.setOutlineThickness(1);
							sfml_polygon.setOutlineColor(sf::Color::White);

							for (int index = 0; index < number_of_vertices; index++)
							{
								sfml_polygon.setPoint
								(
									index,
									box2d_position_to_sfml_position(b2Mul(body_transform, box2d_polygon->m_vertices[index]), window_height, scale)
								);
							}

							window.draw(sfml_polygon);
						}
			}
		}

	}
}

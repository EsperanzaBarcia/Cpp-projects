/**
 * @file Player_Controller.hpp
 *
 * @brief Hija de Controller y message observer, esta clase responderá a los mensajes relacionados con el player
 además de procesar el componente de control
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#include <Entity.hpp>
#include <Transform_component.hpp>
#include <Scene.hpp>
#include <Player_Controller.hpp>
#include <iostream>
#include <string>


namespace engine
{
	Player_Controller::Player_Controller(Scene& s)
	{
		scene = &s;
	}

	void Player_Controller::handle(const Message& m)
	{
		for (auto& item : scene->get_entities())
		{
			Entity& currentEntity = *item.second;

			if (currentEntity.transform != entity->transform)
			{
				if (m.id == "MoveForward")
				{
					/*comprobación de distancia con muros
					si es el muro paramos*/
					if (glm::distance(entity->transform->position, scene->get_entities().find("TopWall")->second->transform->position) > 1.5f)
					{

						//moving_up = true;
						entity->transform->Set_Position(glm::vec3(entity->transform->position.x,
							entity->transform->position.y + 1 * speed,
							entity->transform->position.z));


					}
					else
					{
						/*si es un número lo desactivamos*/
						if (item.first.find("Number"))
						{
							if (glm::distance(entity->transform->position, currentEntity.transform->position) <= .4f)
							{
								currentEntity.active = false;
								std::cout << "Colisión con número" << std::endl;
							}
							else
								std::cout << "Colisión con muro superior" << std::endl;
						}
					}

				}
				else if (m.id == "MoveRight")
				{
					//si es el muro paramos
					if (glm::distance(entity->transform->position, scene->get_entities().find("RightWall")->second->transform->position) > 2.f)
					{
						entity->transform->Set_Position(glm::vec3(entity->transform->position.x + 1 * speed,
							entity->transform->position.y,
							entity->transform->position.z));
					}

					else
					{
						if (item.first.find("Number"))
						{
							if (glm::distance(entity->transform->position, currentEntity.transform->position) <= .4f)
							{
								currentEntity.active = false;
								std::cout << "Colisión con número" << std::endl;
							}
							else
								std::cout << "Colisión con muro derecho" << std::endl;
						}
					}
				}
				else if (m.id == "MoveDown")
				{

					//si es el muro paramos
					if (glm::distance(entity->transform->position, scene->get_entities().find("DownWall")->second->transform->position) > 1.5f)
					{
						entity->transform->Set_Position(glm::vec3(entity->transform->position.x,
							entity->transform->position.y - 1 * speed,
							entity->transform->position.z));
					}

					else
					{
						if (item.first.find("Number"))
						{
							if (glm::distance(entity->transform->position, currentEntity.transform->position) <= .4f)
							{
								currentEntity.active = false;
								std::cout << "Colisión con número" << std::endl;
							}
							else
								std::cout << "Colisión con muro inferior" << std::endl;
						}
					}
				}

				else if (m.id == "MoveLeft")
				{

					//si es el muro paramos
					if (glm::distance(entity->transform->position, scene->get_entities().find("LeftWall")->second->transform->position) > 1.5f)
					{
						entity->transform->Set_Position(glm::vec3(entity->transform->position.x - 1 * speed,
							entity->transform->position.y,
							entity->transform->position.z));
					}
					else
					{
						if (item.first.find("Number"))
						{
							if (glm::distance(entity->transform->position, currentEntity.transform->position) <= 1.f)
							{
								currentEntity.active = false;
								std::cout << "Colisión con número" << std::endl;
							}
							else
								std::cout << "Colisión con muro izquierdo" << std::endl;
						}

					}



				}
			}


		}
	}
	void Player_Controller::update(float delta)
	{
		/*if (moving_up)
		{
			entity->transform->Set_Position(glm::vec3(entity->transform->position.x,
				entity->transform->position.y + 1 * speed * delta,
				entity->transform->position.z));
			std::cout << "update" << std::endl;
		}*/
	}
	void Player_Controller::setEntity(Entity& e)
	{
		entity = &e;
	}
}
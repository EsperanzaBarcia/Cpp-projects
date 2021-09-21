/**
 * @file Entity.hpp
 *
 * @brief Cada entidad del subsistema ECS tiene esta clase
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */
#include <map>
#include <Component.hpp>
#include <Transform_component.hpp>
#include <Scene.hpp>
#include <Entity.hpp>
#include <iostream>


namespace engine
{
	Entity::Entity(Scene* s)
	{
		active = true;
		scene = s;
		transform = new Transform_component(this);
		std::cout << "Instanciada entidad en posicion" << "("
			<< transform->position.x << ","
			<< transform->position.y << ","
			<< transform->position.z << ")" << std::endl;;
	}

	glm::mat4 Entity::get_transform() const
	{
		/*Comprobar si funciona */
		glm::mat4 position = glm::translate(glm::mat4(), transform->position);
		glm::mat4 rotation = glm::rotate(1.f, transform->rotation);
		glm::mat4 scale = glm::scale(glm::mat4(), transform->scale);

		glm::mat4 transform_matrix = position * rotation * scale;

		/*Devuelve la matriz de transformación*/
		return transform_matrix;
	}


	void Entity::add_Component(std::string id, Component* c)
	{
		/*pair:http://www.cplusplus.com/reference/map/map/insert/ */
		components.insert(std::pair<std::string, std::shared_ptr<Component>>(id, c));

		std::cout << "Anadido componente " << components.find(id)->first << std::endl;
	}

	Component* Entity::get_Component(std::string id_to_find)
	{
		/*get devuelve el puntero*/
	//http://www.cplusplus.com/reference/memory/shared_ptr/get*/
		return components[id_to_find].get();
	}
}
/**
 * @file Entity.hpp
 *
 * @brief Cada entidad del subsistema ECS tiene esta clase
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */
#pragma once


#include <map>
#include <memory>
#include <string>
#include <gtx/transform.hpp>


namespace engine
{
	class Component;
	class Scene;
	class Transform_component;

	class Entity
	{

		Scene* scene;///< puntero a la escena en la que está la entidad

		std::map< std::string, std::shared_ptr<Component>> components;///< mapa de componentes de esta entidad

	public:

		bool active = true;///< la entidad puede estar activa o no

		Entity(Scene* s);///< Constructor que recibe la escena

		Transform_component* transform;///< Componente transform de esta entidad

		glm::mat4 get_transform() const; ///< matriz de transformación de la entidad

		void add_Component(std::string id, Component* c);///< método para añadir un componente

	
		Component* get_Component(std::string id_to_find);///<método para buscar un componente en el mapa
	};

}
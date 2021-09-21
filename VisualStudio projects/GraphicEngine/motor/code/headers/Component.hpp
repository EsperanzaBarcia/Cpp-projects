/**
 * @file Component.hpp
 *
 * @brief Clase a partir de la cual hereda cada componente de la escena
 * Parte imprescindible del subsistema ECS
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */
#pragma once 

#include <string>


namespace engine
{
	class Entity;

	class Component
	{
	public:
		std::string id;///< Id del componente por el que srá encontrado

	protected:
		Entity* entity;///< puntero a la entidad que le contiene

	public:

		Component(Entity* e);///< puntero a la entidad que le contiene

		
		virtual Entity* get_entity();///devuelve la entidad a la que está asociado este componente

	};
}
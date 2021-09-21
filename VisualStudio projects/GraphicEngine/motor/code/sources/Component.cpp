/**
 * @file Component.hpp
 *
 * @brief Clase a partir de la cual hereda cada componente de la escena
 * Parte imprescindible del subsistema ECS
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */
#include <Entity.hpp>
#include <Component.hpp>

namespace engine
{
	/*Constructor*/
	Component::Component(Entity* e)
	{
		entity = e;
	}

	Entity* Component::get_entity()
	{
		return entity;
	}

}
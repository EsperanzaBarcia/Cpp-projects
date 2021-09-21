/**
 * @file Render_Component.hpp
 *
 * @brief Hereda de component, las entidades podrán poseer este componente para rendereizar sus modelos 3d
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#pragma once

/*Necesario por herencia*/
#include "Component.hpp"
#include <memory>

namespace glt
{
	class Camera;
	class Model;
	class Model_Obj;
	class Light;
}


namespace engine
{
	class Render_Component : public Component
	{

	public:
		//// Se crea un puntero a Render_Node porque al usar una declaración adelantada
		//// para no exportar dependencias con esta cabecera, solo se pueden definir
		//// punteros o referencias a los tipos declarados de modo adelantado.

		std::shared_ptr<glt::Model_Obj>model;///< Referencia al modelo que se va a renderizar


	public:

		
		Render_Component(std::shared_ptr<glt::Model_Obj>m, Entity* entity) : Component(entity)///< Constructor
		{
			model = m;
		};
	};
}
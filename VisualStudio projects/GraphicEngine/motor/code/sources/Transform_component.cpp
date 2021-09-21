/**
 * @file Transform_Component.hpp
 *
 * @brief Componente que manejará posición, rotación y escala de cada entidad
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#include <Entity.hpp>
#include <Transform_component.hpp>

namespace engine
{
	void Transform_component::Set_Position(glm::vec3 newPos)
	{
		if (position != newPos)
			position = newPos;
	}
	void Transform_component::Set_Scale(glm::vec3 newScale)
	{
		if (scale != newScale)
			scale = newScale;
	}
	void Transform_component::Set_Rotation(glm::vec3 newRotation)
	{
		if (rotation != newRotation)
			rotation = newRotation;
	}

}
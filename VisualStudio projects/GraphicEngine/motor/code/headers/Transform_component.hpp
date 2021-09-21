/**
 * @file Transform_Component.hpp
 *
 * @brief Componente que manejar� posici�n, rotaci�n y escala de cada entidad
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */


#pragma once

/*Necesario por herencia*/
#include "Component.hpp"

#include <vec4.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>



namespace engine
{
	class Transform_component : Component
	{

	public:

		///su id es el del padre
		std::string id = Component::id;///< Id del componente por el que sr� encontrado

		glm::vec3 position;///< par�metros de posici�n
		glm::vec3 rotation;///< par�metros de rotaci�n
		glm::vec3 scale;///< par�metros de escala


	public:
		//rellenamos constructor del padre ademas del suyo
		Transform_component(Entity* e) :Component(e) ///< Constructor, asignamos datos por defecto
		{  
			Set_Position( glm::vec3(0, 0, 1));
			Set_Rotation(glm::vec3(1, 1, 1));
			Set_Scale(glm::vec3(1, 1, 1));
		};

		void Set_Position(glm::vec3 newPos);///< M�todo para cambiar la posici�n de la entidad que contiene el componente
		void Set_Rotation(glm::vec3 rotation);///< M�todo para cambiar la rotaci�n de la entidad que contiene el componente
		void Set_Scale(glm::vec3 newScale);///< M�todo para cambiar la escala de la entidad que contiene el componente

	};
}
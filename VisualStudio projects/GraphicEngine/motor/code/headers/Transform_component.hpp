/**
 * @file Transform_Component.hpp
 *
 * @brief Componente que manejará posición, rotación y escala de cada entidad
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
		std::string id = Component::id;///< Id del componente por el que srá encontrado

		glm::vec3 position;///< parámetros de posición
		glm::vec3 rotation;///< parámetros de rotación
		glm::vec3 scale;///< parámetros de escala


	public:
		//rellenamos constructor del padre ademas del suyo
		Transform_component(Entity* e) :Component(e) ///< Constructor, asignamos datos por defecto
		{  
			Set_Position( glm::vec3(0, 0, 1));
			Set_Rotation(glm::vec3(1, 1, 1));
			Set_Scale(glm::vec3(1, 1, 1));
		};

		void Set_Position(glm::vec3 newPos);///< Método para cambiar la posición de la entidad que contiene el componente
		void Set_Rotation(glm::vec3 rotation);///< Método para cambiar la rotación de la entidad que contiene el componente
		void Set_Scale(glm::vec3 newScale);///< Método para cambiar la escala de la entidad que contiene el componente

	};
}
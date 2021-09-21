/**
 * @file Task.hpp
 *
 * @brief Clase a partir de la cual hereda cada tarea o sistema
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#pragma once
#include "Scene.hpp"

namespace engine
{
	class Task
	{
	public:
		Scene* scene; ///< referencia a la escena
	public:
		virtual void run(float) = 0;
		
		virtual ~Task() = default;
	};
}
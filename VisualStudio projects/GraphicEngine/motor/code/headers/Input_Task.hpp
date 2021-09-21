/**
 * @file Input_Task.hpp
 *
 * @brief Sistema para recibir los input y enviar los mensajes correspondientes
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#pragma once
#include "Task.hpp"

namespace engine
{
	class Input_Task : public Task
	{
	public:
		Input_Task(Scene& s) { scene = &s; };///< Constructor

		void run(float) override;///<  Método que responderá a los input del usuario
	};
}

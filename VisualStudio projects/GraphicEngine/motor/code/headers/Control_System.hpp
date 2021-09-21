/**
 * @file Control_System.hpp
 *
 * @brief Sistena que procesar� los update de todos los componentes de control
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#pragma once

/*Inlcudes necesarios por herencia*/
#include "Task.hpp"
#include <Scene.hpp>

class Scene;

namespace engine
{
	class Control_System : public Task
	{
	public: 
		Control_System(Scene& s) { scene = &s; };///< Constructor
		void run(float delta) override;///< M�todo en el que se procesar�n los m�todos update de los controllers

	};
}

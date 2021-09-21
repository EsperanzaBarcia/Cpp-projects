/**
 * @file Controller_Component.hpp
 *
 * @brief Clase para componente de control
 * Habrá entidades que necesiten componente de control y otras que no,
 * el Player por ejemplo lo necesita
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#pragma once

 /*Necesario por herencia*/
#include "Component.hpp"

#include "Controller.hpp"

namespace engine
{
	
	class Controller_Component :public Component, public Controller
	{
		Controller* controller;///< Puntero al controlador

	};
}
/**
 * @file Message_Observer.hpp
 *
 * @brief Los objetos de esta clase atienden a que se envíe un mensaje para responder con acciones
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#pragma once

#include <Message.hpp>

namespace engine
{
	class Message_Observer
	{
	public:
		virtual void handle(const Message&) = 0;///< Método virtual puro que deberán rellenar los hijos de esta clase
	};

}
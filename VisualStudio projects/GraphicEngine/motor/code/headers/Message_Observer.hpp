/**
 * @file Message_Observer.hpp
 *
 * @brief Los objetos de esta clase atienden a que se env�e un mensaje para responder con acciones
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
		virtual void handle(const Message&) = 0;///< M�todo virtual puro que deber�n rellenar los hijos de esta clase
	};

}

/**
 * @file Message_Dipatcher.hpp
 *
 * @brief Clase que gestiona los mensajes, enviándolos a los observadores pendientes de ello
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#pragma once

#include <string>
#include <list>
#include <map>

#include <Message_Observer.hpp>

namespace engine
{
	class Message_Dipatcher
	{
		std::map< std::string, std::list< Message_Observer* > > message_observers;///< mapa de observadores de la escena 

	public:

		void add_observer(const std::string& id, Message_Observer* observer);///< método para añadir observadores a un mensaje concreto 

		void send(const Message& m);///< Método para enviar un mensaje a los observadores

	};
}
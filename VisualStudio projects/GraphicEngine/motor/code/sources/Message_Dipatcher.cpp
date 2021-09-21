
/**
 * @file Message_Dipatcher.hpp
 *
 * @brief Clase que gestiona los mensajes, enviándolos a los observadores pendientes de ello
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#include "Message_Dipatcher.hpp"

namespace engine
{
	/*Método para añadir observadores al mapa*/
	void Message_Dipatcher::add_observer(const std::string& id, Message_Observer* observer)
	{
		if (message_observers.find(id) != message_observers.end())
		{
			//cogemos la lista de observers coincidentes con el id
			std::list<Message_Observer*> observers = message_observers.find(id)->second;

			//añadimos el observer a la lista
			observers.push_back(observer);

			//guardamos todo en el mapa
			/*make pair: http://www.cplusplus.com/reference/utility/make_pair/*/
			message_observers.insert(std::make_pair(id, observers));

		}
		else
		{
			//creamos la lista
			std::list<Message_Observer*> observers;
			observers.push_back(observer);

			//añadimos los observadores
			message_observers.insert(std::make_pair(id, observers));
		}

	}

	/*Método para mandar el mensaje a sus observadores*/
	void Message_Dipatcher::send(const Message& m)
	{
		//busca a todos los observadores del id y les hace responder
		for (auto& observer : message_observers[m.id])
		{
			observer->handle(m);
		}
	}
}

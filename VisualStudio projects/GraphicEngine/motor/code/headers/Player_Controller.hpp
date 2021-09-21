/**
 * @file Player_Controller.hpp
 *
 * @brief Hija de Controller y message observer, esta clase responderá a los mensajes relacionados con el player
 además de procesar el componente de control
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#pragma once

 //Necesario por herencia
#include <Controller.hpp>
#include <Message_Observer.hpp>

namespace engine
{
	class Entity;
	class Player_Controller : public Controller, public Message_Observer
	{
		float speed = .01f;///< velocidad de movimiento del jugador

		Scene* scene;///< Puntero a la escena en la que está

		Entity* entity;///< Puntero a la entidad a la que pertence

	public:

		Player_Controller(Scene& s);///< Constructor

		void handle(const Message& m) override;///< heredado de Message_Observer, responde al mensaje recibido

		/*Por ahora la llamada a este método no funciona*/
		void update(float) override;///< heredado de Controller, actualiza lo relacionado con el controller

		void setEntity(Entity& e);///< método para asignar la entidad
	};

}
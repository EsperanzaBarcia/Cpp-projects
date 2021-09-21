/**
 * @file Input_Task.hpp
 *
 * @brief Sistema para recibir los input y enviar los mensajes correspondientes
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */
#include <Windows.h>
#include <Window.hpp>
#include <Event.hpp>
#include <Input_Task.hpp>
#include <Message.hpp>
#include <Message_Dipatcher.hpp>
#include <Scene.hpp>
#include <iostream>
using namespace std;

namespace engine
{
	void Input_Task::run(float)
	{
		Event event;
		while (scene->get_window().poll(scene->get_window(), event))
		{
			switch (event.type)
			{
			case Event::KEY_PRESSED:
				//cuando es pulsado una tecla concreta se envía un mensaje a los observadores de este
				if (event.data.keyboard.key_code == 28)//W
				{
					Message m{ "MoveForward" };
					scene->get_message_dispatcher().send(m);
				}
				else if (event.data.keyboard.key_code == 9)//D
				{
					Message m{ "MoveRight" };
					scene->get_message_dispatcher().send(m);
				}
				else if (event.data.keyboard.key_code == 24)//D
				{
					Message m{ "MoveDown" };
					scene->get_message_dispatcher().send(m);
				}
				else if (event.data.keyboard.key_code == 6)//A
				{
					Message m{ "MoveLeft" };
					scene->get_message_dispatcher().send(m);
				}
				break;
			}
		}
	}
}
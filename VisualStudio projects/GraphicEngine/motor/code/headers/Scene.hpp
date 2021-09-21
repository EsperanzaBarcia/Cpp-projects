/**
 * @file Scene.hpp
 *
 * @brief Clase donde se encontrarán las entidades y los componentes
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */


#pragma once

#include <map>
#include <string>
#include <memory>

namespace engine
{
	class Window;
	class Task;
	class Render_Component;
	class Render_System;
	class Control_System;
	class Input_Task;
	class Kernel;
	class Entity;
	class Controller;
	class Message_Observer;
	class Message_Dipatcher;


	class Scene
	{
		Window* window;///< puntero a ventana

		std::map<std::string, std::shared_ptr<Entity>> entities;///< mapa de entidades

		std::map<std::string, std::shared_ptr<Controller>> controllers;///< mapa de controladores

		Input_Task* input_task = nullptr;///< tarea que procesa los eventos de input

		Control_System* control_system = nullptr;///< tarea que procesa los eventos de  control

		Render_System* render_system = nullptr;///< tarea que procesa los eventos de render

		Message_Dipatcher* message_dispatcher;///< gestor de mensajes

		Kernel* kernel = nullptr;///< kernel de tareas

	public:

		Scene(Window& w);///< constructor

		Window& get_window() { return *window; };///< método que devuelve la ventana

	
		Input_Task& get_Input_Task();///< método que puntero a input task


		Render_System& get_Render_System();///< método que devuelve referencia a render system

		Message_Dipatcher& get_message_dispatcher();///< método que devuelve referencia al message dispatcher

		std::map<std::string, std::shared_ptr<Controller>>& get_controllers();///< método que devuelve referencia al message dispatcher

		/*Función para recibir las entidades de la escena*/
		std::map<std::string, std::shared_ptr<Entity>> get_entities();///< método que devuelve referencia al message dispatcher

		void add_entity(std::string id, Entity* entity);///<Función para añadir una entidad al mapa de la escena

		void add_controller(std::string id, Controller* controller);///< Función para añadir un controlador al mapa de la escena

		void add_observer(const std::string id, Message_Observer& o);///< Función para añadir un observer a un mensaje concreto

		void run(float delta);///< método que activa el kernel

	};

}
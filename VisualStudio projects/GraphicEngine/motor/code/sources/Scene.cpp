/**
 * @file Scene.hpp
 *
 * @brief Clase donde se encontrarán las entidades y los componentes
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */


#include <Window.hpp>
#include <Controller.hpp>
#include <Task.hpp>
#include <Input_Task.hpp>
#include <Kernel.hpp>
#include <Render_Node.hpp>
#include <Render_System.hpp>
#include <Render_Component.hpp>
#include <Control_System.hpp>
#include <Scene.hpp>
#include <Message_Observer.hpp>
#include <Message_Dipatcher.hpp>


namespace engine
{
	Scene::Scene(Window& w)
	{
		//comprobar si esta bien lo de poner referencia
		window = &w;

		//inicializamos el kernel
		kernel = new Kernel();

		//inicializamos el input task
		input_task = new Input_Task(*this);

		//inicializamos el control task
		control_system = new Control_System(*this);

		//inicializamos el render task
		render_system = new Render_System(*this);

		//inicializamos el message_dispatcher
		message_dispatcher = new Message_Dipatcher();

		//Añadimos las task al kernel
		kernel->tasks.push_back(input_task);

		kernel->tasks.push_back(control_system);

		kernel->tasks.push_back(render_system);

	}

	Input_Task& Scene::get_Input_Task()
	{
		if (input_task)
			return *input_task;
	}

	Render_System& Scene::get_Render_System()
	{
		if (render_system)
			return *render_system;
	}

	Message_Dipatcher& Scene::get_message_dispatcher()
	{
		if (message_dispatcher)
			return *message_dispatcher;
	}

	std::map<std::string, std::shared_ptr<Controller>>& Scene::get_controllers()
	{
		return controllers;
	}

	/*Función para recibir las entidades de la escena*/
	std::map<std::string, std::shared_ptr<Entity>> Scene::get_entities()
	{
		return entities;
	}

	void Scene::add_entity(std::string id, Entity* entity)
	{
		///pair:http://www.cplusplus.com/reference/map/map/insert/ 
		entities.insert(std::pair<std::string, Entity*>(id, entity));
	}

	void Scene::add_controller(std::string id, Controller* controller)
	{
		///pair:http://www.cplusplus.com/reference/map/map/insert/ 
		controllers.insert(std::pair<std::string, Controller*>(id, controller));
	}

	void Scene::add_observer(const std::string id, Message_Observer& o)
	{
		message_dispatcher->add_observer(id, &o);
	}

	void Scene::run(float delta)
	{
		//activamos el kernel
		kernel->run(delta);
	}
}
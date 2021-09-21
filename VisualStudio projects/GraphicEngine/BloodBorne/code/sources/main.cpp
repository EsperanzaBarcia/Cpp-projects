/**
* Este código ha sido realizado para crear todos los datos de la demo que funcionará gracias a la librería propia motor.lib
 *Esperanza Barcia Ortiz
 * JAN-2021
 */


#include <Window.hpp>
#include <Scene.cpp>
#include <Component.hpp>
#include <Controller_Component.hpp>
#include <Render_Component.hpp>
#include <Input_Task.hpp>
#include <Render_System.hpp>
#include <Entity.hpp>
#include <Transform_component.hpp>
#include <Player_Controller.hpp>

#include <memory>
#include <iostream>

using namespace engine;
using namespace glt;

int main()
{
	/*Ventana en la que se verá la demo*/
	Window w("My Bloodborn", 800, 600, false);

	/*Escena actual*/
	engine::Scene s(w);

#pragma region Instanciación del player

	//añadimos player
	Entity* player = new engine::Entity(&s);

	//añadimos la entidad de player
	s.add_entity("Player", player);

	//creamos un render component
	std::shared_ptr< Render_Component> rc = s.get_Render_System().create_render_component("render_component", player, "../assets/stanford-bunny.obj");

	//lo añadimos a la entidad
	player->add_Component("render_component", dynamic_cast<engine::Component*>(rc.get()));

	player->transform->Set_Scale(glm::vec3(.2f, .2f, .2f));
	player->transform->Set_Rotation(glm::vec3(1.f, 20.f, 0.f));

#pragma endregion

#pragma region Instanciación de los muros

#pragma region TopWall

	//MURO ARRIBA
	Entity* topWall = new engine::Entity(&s);

	//añadimos la entidad 
	s.add_entity("TopWall", topWall);

	//creamos un render component
	std::shared_ptr< Render_Component> topWallrender = s.get_Render_System().create_render_component("top_wall_component", topWall, "../assets/stanford-bunny.obj");

	//lo añadimos a la entidad
	topWall->add_Component("render_component", dynamic_cast<engine::Component*>(topWallrender.get()));

	topWall->transform->Set_Scale(glm::vec3(500.f, .5f, 1.f));
	topWall->transform->Set_Rotation(glm::vec3(180.f, 0.f, 0.f));
	topWall->transform->Set_Position(glm::vec3(0.f, 3.f, 1.f));


#pragma endregion 

#pragma region RightWall

	//MURO Derecha
	Entity* RightWall = new engine::Entity(&s);

	//añadimos la entidad 
	s.add_entity("RightWall", RightWall);

	//creamos un render component
	std::shared_ptr< Render_Component> rightWallrender = s.get_Render_System().create_render_component("right_wall_component", RightWall, "../assets/stanford-bunny.obj");

	//lo añadimos a la entidad
	RightWall->add_Component("render_component", dynamic_cast<engine::Component*>(rightWallrender.get()));

	RightWall->transform->Set_Scale(glm::vec3(.5f, 500.f, 1.f));
	RightWall->transform->Set_Rotation(glm::vec3(0.f, 20.f, 0.f));
	RightWall->transform->Set_Position(glm::vec3(3.5f, 1.f, 1.f));

#pragma endregion

#pragma region DownWall

	//MURO abajo
	Entity* DownWall = new engine::Entity(&s);

	//añadimos la entidad 
	s.add_entity("DownWall", DownWall);

	//creamos un render component
	std::shared_ptr< Render_Component> DownWallrender = s.get_Render_System().create_render_component("down_wall_component", DownWall, "../assets/stanford-bunny.obj");

	//lo añadimos a la entidad
	DownWall->add_Component("render_component", dynamic_cast<engine::Component*>(DownWallrender.get()));

	DownWall->transform->Set_Scale(glm::vec3(500.f, 1.f, 1.f));
	DownWall->transform->Set_Rotation(glm::vec3(180.f, 0.f, 0.f));
	DownWall->transform->Set_Position(glm::vec3(1.f, -3.f, 1.f));

#pragma endregion

#pragma region LeftWall

	//MURO izqueirda
	Entity* LeftWall = new engine::Entity(&s);

	//añadimos la entidad 
	s.add_entity("LeftWall", LeftWall);

	//creamos un render component
	std::shared_ptr< Render_Component> LeftWallrender = s.get_Render_System().create_render_component("up_wall_component", LeftWall, "../assets/stanford-bunny.obj");

	//lo añadimos a la entidad
	LeftWall->add_Component("render_component", dynamic_cast<engine::Component*>(LeftWallrender.get()));

	LeftWall->transform->Set_Scale(glm::vec3(.5f, 500.f, 1.f));
	LeftWall->transform->Set_Rotation(glm::vec3(0.f, 20.f, 0.f));
	LeftWall->transform->Set_Position(glm::vec3(-3.5f, 1.f, 1.f));

#pragma endregion

#pragma endregion

#pragma region Instanciación de números
	//añadimos player
	Entity* number1 = new engine::Entity(&s);

	//añadimos la entidad 
	s.add_entity("Number1", number1);

	//creamos un render component
	std::shared_ptr< Render_Component> number1_renderer_component = s.get_Render_System().create_render_component("number1_renderer_component", number1, "../assets/number_1.obj");

	//lo añadimos a la entidad
	number1->add_Component("render_component", dynamic_cast<engine::Component*>(number1_renderer_component.get()));

	number1->transform->Set_Scale(glm::vec3(.05f, .05f, .05f));
	number1->transform->Set_Rotation(glm::vec3(-180.f, 0, 1.f));
	number1->transform->Set_Position(glm::vec3(-1.f, .2f, 1.f));

#pragma endregion

#pragma region Instanciación de controlador

	//Creamos el player controller
	Player_Controller player_controller(s);
	player_controller.setEntity(*player);

	//añadimos el controller
	s.add_controller("Player_Controller", dynamic_cast<Controller*>(&player_controller));

	//añadir controller component
	player->add_Component("controller_component", dynamic_cast<Controller_Component*>(&player_controller));
#pragma endregion

#pragma region Creación de observadores que estarán pendientes de los mensajes del player controller
	//añadimos el observador de este controller
	s.add_observer("MoveRight", player_controller);

	//añadimos el observador de este controller
	s.add_observer("MoveDown", player_controller);

	//añadimos el observador de este controller
	s.add_observer("MoveForward", player_controller);

	//añadimos el observador de este controller
	s.add_observer("MoveLeft", player_controller);
#pragma endregion

	/*Activamos el bucle principal*/
	s.run(1 / 60);
}
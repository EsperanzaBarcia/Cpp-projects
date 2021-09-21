/**
 * @file Render_System.hpp
 *
 * @brief Sistema que llama a renderizar a todos los render component
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#pragma once

#include "Task.hpp"
#include <Render_Node.hpp>

namespace glt
{
	class Model;
	class Model_Obj;
	class Light;
}

namespace engine
{
	class Render_Component;

	class Render_System :public Task 
	{

		std::shared_ptr<glt::Camera> camera;///< referencia a la c�mara

		std::shared_ptr<glt::Light> light;///< referencia a la luz

	public:
		std::unique_ptr< glt::Render_Node > renderer;///< imprescindible para renderizar

		Render_System(Scene& s);///< constructor

		std::shared_ptr<Render_Component> create_render_component(const std::string id, Entity* entity, const std::string path);///< m�todo para crear un render component

		void run(float delta)override;///< m�todo para actualizar todos los render component


	private:

		std::shared_ptr<glt::Camera> create_camera_component(const std::string id);///< m�todo para crear la c�mara

		std::shared_ptr<glt::Light>create_light_component(const std::string id);///< m�todo para crear la luz

		std::shared_ptr<glt::Model> create_cube_model();///< m�todo para crear un cubo

		/** En este caso es necesario definir expl�citamente el destructor en el archivo
		  * de implementaci�n (CPP) para que el compilador pueda destruir el Render_Node.
		  * Si se deja que el compilador cree un destructor por defecto en el programa
		  * que use el engine, como solo tendr� una declaraci�n adelantada, no sabr� c�mo
		  * destruirlo y ello dar� lugar a un error de compilaci�n.
		  */
		~Render_System();

		void render();///< m�todo para renderizar
	};

}
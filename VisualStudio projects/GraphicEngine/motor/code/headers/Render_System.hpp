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

		std::shared_ptr<glt::Camera> camera;///< referencia a la cámara

		std::shared_ptr<glt::Light> light;///< referencia a la luz

	public:
		std::unique_ptr< glt::Render_Node > renderer;///< imprescindible para renderizar

		Render_System(Scene& s);///< constructor

		std::shared_ptr<Render_Component> create_render_component(const std::string id, Entity* entity, const std::string path);///< método para crear un render component

		void run(float delta)override;///< método para actualizar todos los render component


	private:

		std::shared_ptr<glt::Camera> create_camera_component(const std::string id);///< método para crear la cámara

		std::shared_ptr<glt::Light>create_light_component(const std::string id);///< método para crear la luz

		std::shared_ptr<glt::Model> create_cube_model();///< método para crear un cubo

		/** En este caso es necesario definir explícitamente el destructor en el archivo
		  * de implementación (CPP) para que el compilador pueda destruir el Render_Node.
		  * Si se deja que el compilador cree un destructor por defecto en el programa
		  * que use el engine, como solo tendrá una declaración adelantada, no sabrá cómo
		  * destruirlo y ello dará lugar a un error de compilación.
		  */
		~Render_System();

		void render();///< método para renderizar
	};

}
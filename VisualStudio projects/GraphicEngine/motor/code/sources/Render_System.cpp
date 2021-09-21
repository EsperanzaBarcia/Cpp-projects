/**
 * @file Render_System.hpp
 *
 * @brief Sistema que llama a renderizar a todos los render component
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#include <memory>

#include <Window.hpp>
#include <Component.hpp>
#include <Render_Component.hpp>
#include <Render_System.hpp>
#include <Transform_component.hpp>
#include <Cube.hpp>
#include <Model.hpp>
#include <Model_Obj.hpp>
#include <Light.hpp>
#include <Entity.hpp>

#include <iostream>

using namespace glt;

namespace engine
{
	Render_System::Render_System(Scene& s)
	{
		scene = &s;
		/*inicialización del renderer*/
		renderer.reset(new Render_Node);

		/*creamos el componente con su luz y su cámara*/
		camera = create_camera_component("camera");
		light = create_light_component("light");
	}

	std::shared_ptr<Render_Component> Render_System::create_render_component(const std::string id, Entity* entity, const std::string path)
	{
		/*cargamos el modelo desde la carpeta*/
		std::shared_ptr<glt::Model_Obj> model(new Model_Obj(path));

		/*añadimos el modelo al renderer*/
		renderer->add(id, model);

		std::cout << id << "añadido" << std::endl;

		return std::shared_ptr<Render_Component>(new Render_Component{ model,entity });

	}

	std::shared_ptr<glt::Camera> Render_System::create_camera_component(const std::string id)
	{
		/*creamos la cámara*/
		std::shared_ptr< glt::Camera > camera(new Camera(20.f, 1.f, 10.f, 1.f));

		/*añadimos la cámara al renderer*/
		renderer->add(id, camera);
		std::cout << id << "añadida" << std::endl;

		/*colocamos la cámara */
		renderer->get(id)->translate(Vector3(0.f, 0.f, 5.f));

		return camera;
	}

	std::shared_ptr<glt::Light> Render_System::create_light_component(const std::string id)
	{
		/*creamos la luz*/
		std::shared_ptr< glt::Light  > light(new Light);

		/*añadimos la luz al renderer*/
		renderer->add(id, light);
		std::cout << "Luz añadida" << std::endl;

		/*colocamos la luz */
		renderer->get("light")->translate(Vector3(10.f, 50.f, 10.f));

		return light;
	}

	std::shared_ptr<glt::Model> Render_System::create_cube_model()
	{
		/*modelo*/
		std::shared_ptr<glt::Model> model(new glt::Model);

		/* Es necesario añadir las mallas a los modelos antes de añadir los modelos a la escena:*/
		model->add(std::shared_ptr< Drawable >(new Cube), Material::default_material());

		renderer->add("cube", model);

		return model;
	}


	void Render_System::run(float delta)
	{
		for (auto& item : scene->get_entities())
		{
			Entity& currentEntity = *item.second;

			Component* render_component = currentEntity.get_Component("render_component");

			/*Actualizamos las posiciones */
			if (render_component)
			{
				if (currentEntity.active)
					dynamic_cast<Render_Component*>(render_component)->model->set_transformation(currentEntity.get_transform());
				else
					currentEntity.transform->scale = glm::vec3(0.f, 0.f, 0.f);

			}
		}
		//renderizamos con la cámara y luz
		render();
	}


	Render_System::~Render_System()
	{
		/* En este caso es necesario definir explícitamente el destructor en el archivo
		de implementación (CPP) para que el compilador pueda destruir el Render_Node
		pese a que no hay código explícito.*/
	}

	void Render_System::render()
	{
		// Se ajusta el viewport por si el tamaño de la ventana ha cambiado:

		GLsizei width = GLsizei(scene->get_window().get_width());
		GLsizei height = GLsizei(scene->get_window().get_height());


		renderer->get_active_camera()->set_aspect_ratio(float(width) / height);

		glViewport(0, 0, width, height);

		// Se renderiza la escena y se intercambian los buffers de la ventana para
		// hacer visible lo que se ha renderizado:
		scene->get_window().clear();

		renderer->render();

		scene->get_window().swap_buffers();
	}


}
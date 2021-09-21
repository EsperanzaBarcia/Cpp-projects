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
		/*inicializaci�n del renderer*/
		renderer.reset(new Render_Node);

		/*creamos el componente con su luz y su c�mara*/
		camera = create_camera_component("camera");
		light = create_light_component("light");
	}

	std::shared_ptr<Render_Component> Render_System::create_render_component(const std::string id, Entity* entity, const std::string path)
	{
		/*cargamos el modelo desde la carpeta*/
		std::shared_ptr<glt::Model_Obj> model(new Model_Obj(path));

		/*a�adimos el modelo al renderer*/
		renderer->add(id, model);

		std::cout << id << "a�adido" << std::endl;

		return std::shared_ptr<Render_Component>(new Render_Component{ model,entity });

	}

	std::shared_ptr<glt::Camera> Render_System::create_camera_component(const std::string id)
	{
		/*creamos la c�mara*/
		std::shared_ptr< glt::Camera > camera(new Camera(20.f, 1.f, 10.f, 1.f));

		/*a�adimos la c�mara al renderer*/
		renderer->add(id, camera);
		std::cout << id << "a�adida" << std::endl;

		/*colocamos la c�mara */
		renderer->get(id)->translate(Vector3(0.f, 0.f, 5.f));

		return camera;
	}

	std::shared_ptr<glt::Light> Render_System::create_light_component(const std::string id)
	{
		/*creamos la luz*/
		std::shared_ptr< glt::Light  > light(new Light);

		/*a�adimos la luz al renderer*/
		renderer->add(id, light);
		std::cout << "Luz a�adida" << std::endl;

		/*colocamos la luz */
		renderer->get("light")->translate(Vector3(10.f, 50.f, 10.f));

		return light;
	}

	std::shared_ptr<glt::Model> Render_System::create_cube_model()
	{
		/*modelo*/
		std::shared_ptr<glt::Model> model(new glt::Model);

		/* Es necesario a�adir las mallas a los modelos antes de a�adir los modelos a la escena:*/
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
		//renderizamos con la c�mara y luz
		render();
	}


	Render_System::~Render_System()
	{
		/* En este caso es necesario definir expl�citamente el destructor en el archivo
		de implementaci�n (CPP) para que el compilador pueda destruir el Render_Node
		pese a que no hay c�digo expl�cito.*/
	}

	void Render_System::render()
	{
		// Se ajusta el viewport por si el tama�o de la ventana ha cambiado:

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
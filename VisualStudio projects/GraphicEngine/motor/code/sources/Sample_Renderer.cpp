// This is free code released into the public domain.
// Drafted by ?ngel in January 2019.
// angel.rodriguez@esne.edu

#include <Window.hpp>
#include <Cube.hpp>
#include <Model.hpp>
#include <Light.hpp>
#include <Render_Node.hpp>
#include <Sample_Renderer.hpp>

using namespace std;
using namespace glt;

namespace engine
{

    Sample_Renderer::Sample_Renderer(Window& given_window)
    {
        window = &given_window;

        // Se crea el render node de OpenGL Toolkit:

        renderer.reset(new Render_Node);

        // Se crean los elementos b?sicos necesarios para dibujar un cubo:

        shared_ptr< Model  > cube(new Model);
        shared_ptr< Camera > camera(new Camera(20.f, 1.f, 50.f, 1.f));
        shared_ptr< Light  > light(new Light);

        // Es necesario a?adir las mallas a los modelos antes de a?adir los modelos a la escena:

        cube->add(shared_ptr< Drawable >(new Cube), Material::default_material());

        // Se a?aden los nodos a la escena:

        renderer->add("cube", cube);
        renderer->add("camera", camera);
        renderer->add("light", light);

        // Se configuran algunas propiedades de transformaci?n:

        renderer->get("camera")->translate(Vector3(0.f, 0.f, 5.f));
        renderer->get("light")->translate(Vector3(10.f, 10.f, 10.f));
    }

    Sample_Renderer::~Sample_Renderer()
    {
        // En este caso es necesario definir expl?citamente el destructor en el archivo
        // de implementaci?n (CPP) para que el compilador pueda destruir el Render_Node
        // pese a que no hay c?digo expl?cito.
    }

    void Sample_Renderer::render()
    {
        // Se ajusta el viewport por si el tama?o de la ventana ha cambiado:

        GLsizei width = GLsizei(window->get_width());
        GLsizei height = GLsizei(window->get_height());
     

        renderer->get_active_camera()->set_aspect_ratio(float(width) / height);

        glViewport(0, 0, width, height);

        // Se rota el objeto:

        auto cube = renderer->get("cube");

        cube->rotate_around_x(0.01f);
        cube->rotate_around_y(0.02f);
        cube->rotate_around_z(0.03f);

        // Se renderiza la escena y se intercambian los buffers de la ventana para
        // hacer visible lo que se ha renderizado:

        //window->clear();

        renderer->render();

       // window->swap_buffers();
    }

}

// This is free code released into the public domain.
// Drafted by �ngel in January 2019.
// angel.rodriguez@esne.edu

#pragma once

#include <memory>
#include <string>

class Window;

namespace glt
{

    class Render_Node;

}

namespace engine
{

    class Sample_Renderer
    {

        // Se crea un puntero a Render_Node porque al usar una declaraci�n adelantada
        // para no exportar dependencias con esta cabecera, solo se pueden definir
        // punteros o referencias a los tipos declarados de modo adelantado.

        std::unique_ptr< glt::Render_Node > renderer;

        Window* window;

    public:

        Sample_Renderer(Window& given_window);

        /** En este caso es necesario definir expl�citamente el destructor en el archivo
          * de implementaci�n (CPP) para que el compilador pueda destruir el Render_Node.
          * Si se deja que el compilador cree un destructor por defecto en el programa
          * que use el engine, como solo tendr� una declaraci�n adelantada, no sabr� c�mo
          * destruirlo y ello dar� lugar a un error de compilaci�n.
          */
        ~Sample_Renderer();

        void render();

    };

}
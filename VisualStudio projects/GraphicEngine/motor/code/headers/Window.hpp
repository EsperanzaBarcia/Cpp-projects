
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu

#pragma once

#include <string>
struct SDL_Window;
typedef void* SDL_GLContext;

namespace engine
{
	struct Event;
	class Window
	{

	private:

		SDL_Window* window;
		SDL_GLContext gl_context;

	public:

		Window(const std::string& title, int width, int height, bool fullscreen = false);
		~Window();

	public:

		/** Retorna el ancho actual de la ventana (el usuario puede cambiarlo).
		  */
		unsigned get_width() const;

		/** Retorna el alto actual de la ventana (el usuario puede cambiarlo).
		  */
		unsigned get_height() const;

		/** Permite extraer un evento de la cola de eventos asociada a la ventana.
		  */
		bool poll(Window& window, Event& event) const;

		void enable_vsync();

		void disable_vsync();

		/** Borra el buffer de la pantalla usando OpenGL.
		  */
		void clear() const;

		/** Intercambia el buffer visible con el buffer oculto.
		  */
		void swap_buffers() const;

	};

}

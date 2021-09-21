// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2013.12 - 2021.04

#ifndef VIEW_HEADER
#define VIEW_HEADER

#include <Color_Buffer.hpp>
#include <cstdlib>
#include <math.hpp>
#include <Rasterizer.hpp>
#include <vector>
#include <Model.hpp>

namespace SceneRenderer
{
	using  std::vector;
	using argb::Rgb888;
	using argb::Color_Buffer;

	class View
	{
	private:

		typedef Rgb888                Color;
		typedef Color_Buffer< Color > Color_Buffer;

		/**
		*Un vértice es un punto con 4 coordenadas(3D - x, y, z, w)
		*/
		typedef Point4f               Vertex;

	private:

		/**
			*Buffer donde se guarda la imagen que se va a mostrar en ventana
			*debe tener el mismo tamaño que la ventana
			* */
		Color_Buffer               color_buffer;

		/**
		*dibuja los triángulos en el buffer
		*/
		Rasterizer< Color_Buffer > rasterizer;

		unsigned width;
		unsigned height;


	public:
		vector<Model*>models;

		/**
		*Constructor
		*/
		View(unsigned width, unsigned height);

		void update();
		void render();

		void addModel(Model&);
	private:

		bool  is_frontface(const Vertex* const projected_vertices, const int* const indices);
		//float rand_clamp() { return float(rand() & 0xff) * 0.0039215f; }

	};

}

#endif

/**
*Esperanza Barcia
* MAY 2021
*/

#pragma once

#include <Color_Buffer.hpp>
#include <cstdlib>
#include <math.hpp>
#include <cmath>
#include <vector>
#include <string>

namespace SceneRenderer
{
	using  std::vector;
	using argb::Rgb888;
	using argb::Color_Buffer;

	class MeshClass
	{
	private:
#pragma region Definición de tipos
		/**
		La variable de color
		tiene un formato de pixel de 24 bits
		*/
		typedef Rgb888                Color;

		/**
		*Un vértice es un punto con 4 coordenadas(3D - x, y, z, w)
		*/
		typedef Point4f               Vertex;

		/**
		*Array de vértices de la malla
		*/
		typedef vector< Vertex >      Vertex_Buffer;

		/**
		*Array de índices que unen los vértices de la malla
		*/

		typedef vector< int    >      Index_Buffer;

		/**
		*Array de colores
		*/
		typedef vector< Color  >      Vertex_Colors;
#pragma endregion
	private:
		/**
		*coordenadas de cada vertice
		*/
		Vertex_Buffer     original_vertices;

		/**
		*color de cada vértice
		*/
		Vertex_Colors     original_colors;

		/**
		*Los índices indican como se unen los vértices para dibujar los triángulos(de 3 en 3)
		*Recordar que deben unirse en sistema horario o anti horario,
		*Depende del sistema de coordenadas(mano derecha o izquierda)
		*/
		Index_Buffer      original_indices;

		/**
		*Directorio desde donde se carga la malla
		*/
		std::string mesh_route;


	public:
		/**
		* Datos transformados ya, coma flotante
		*/
		Vertex_Buffer     transformed_vertices;

		/**
		* Coordenadas de display, enteras en este caso
		*/
		vector< Point4i > display_vertices;


	public:
		/**
		*Este método actualiza los vértices dependiendo de la posición del modelo
		*/
		void update(Matrix44&);

		/**
		*Este método carga la malla y guarda los datos de assimp en nuestra estructura
		*/
		void loadMesh(std::string route);

		void scale();
		void rotate_X();
		void rotate_Y();
		void rotate_Z();
		void translate();

		//PONER A PARTE?????
		float rand_clamp() { return float(rand() & 0xff) * 0.0039215f; }

		void render(Matrix44& modelTransformation);



	};
}
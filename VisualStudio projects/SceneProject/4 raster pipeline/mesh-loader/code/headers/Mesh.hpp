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
#pragma region Definici�n de tipos
		/**
		La variable de color
		tiene un formato de pixel de 24 bits
		*/
		typedef Rgb888                Color;

		/**
		*Un v�rtice es un punto con 4 coordenadas(3D - x, y, z, w)
		*/
		typedef Point4f               Vertex;

		/**
		*Array de v�rtices de la malla
		*/
		typedef vector< Vertex >      Vertex_Buffer;

		/**
		*Array de �ndices que unen los v�rtices de la malla
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
		*color de cada v�rtice
		*/
		Vertex_Colors     original_colors;

		/**
		*Los �ndices indican como se unen los v�rtices para dibujar los tri�ngulos(de 3 en 3)
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
		*Este m�todo actualiza los v�rtices dependiendo de la posici�n del modelo
		*/
		void update(Matrix44&);

		/**
		*Este m�todo carga la malla y guarda los datos de assimp en nuestra estructura
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
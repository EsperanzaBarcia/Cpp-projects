// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2013.12 - 2021.04

#include <cassert>
#include <cmath>
#include <math.hpp>
#include <View.hpp>
#include <iostream>

//Assimp nos da cada primitiva como una lista de triángulos
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace SceneRenderer
{
	//Se inicializan dimensiones, color buffer y rasterizer
	View::View(unsigned width, unsigned height)
		:
		width(width),
		height(height),
		color_buffer(width, height),
		rasterizer(color_buffer) {}

	void View::update()
	{
		/*
		// Se actualizan los parámetros de transformatión (sólo se modifica el ángulo):

		static float angle = 0.f;

		angle += 0.025f;

		// Se crean las matrices de transformación:

		Matrix44 identity(1);

		//se escala el modelo
		//cada objeto tendrá una escala diferente
		Matrix44 scaling = scale(identity, 1.f);
		Matrix44 rotation_y = rotate_around_y(identity, angle);
		//valor negativo en z aleja el modelo
		Matrix44 translation = translate(identity, Vector3f{ 0.f, 0.5f, -10.f });
		//se pone una perspectiva cónica
		Matrix44 projection = perspective(20, 1, 6, float(width) / height);

		// Creación de la matriz de transformación unificada (de coordenadas de modelo a proyectadas):
		Matrix44 transformation = projection * translation * rotation_y * scaling;

		// Se transforman todos los vértices usando la matriz de transformación resultante:

		for (size_t index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
		{
			// Se multiplican todos los vértices originales con la matriz de transformación y
			// se guarda el resultado en otro vertex buffer:

			Vertex& vertex = transformed_vertices[index] = transformation * original_vertices[index];

			// La matriz de proyección en perspectiva hace que el último componente del vector
			// transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

			float divisor = 1.f / vertex.w;

			vertex.x *= divisor;
			vertex.y *= divisor;
			vertex.z *= divisor;
			vertex.w = 1.f;
		}*/
	}

	void View::render()
	{
		//renderizar modelo 

		for (size_t i = 0; i < models.size(); i++)
		{
			//modificamos las coordenadas a coordenadas de display
			models[i]->NDC_ToDisplay(width, height);
			models[i]->render(width, height);
		}

		// Se borra el framebúffer y se dibujan los triángulos:
		rasterizer.clear();

		for (size_t i = 0; i < models.size(); i++)
		{
			for (vector<MeshClass*>::iterator it = models[i]->meshes.begin(); it < models[i]->meshes.end(); it++)
			{

				/*
					//Se recorren los indices de 3 en 3 y se pinta
				for (int* indices = it->original_indices.data(), *end = indices + meshes[i].original_indices.size(); indices < end; indices += 3)
				{
					if (is_frontface(transformed_vertices.data(), indices))
					{
						// Se establece el color del polígono a partir del color de su primer vértice:
						rasterizer.set_color(original_colors[*indices]);

						// Se rellena el polígono:
						//este método permite hacer polígonos convexos por si están recortados
						rasterizer.fill_convex_polygon_z_buffer(display_vertices.data(), indices, indices + 3);
					}
				}
				*/
			}
		}

		// Se copia el framebúffer oculto en el framebúffer de la ventana:
		color_buffer.blit_to_window();
	}

	bool View::is_frontface(const Vertex* const projected_vertices, const int* const indices)
	{
		const Vertex& v0 = projected_vertices[indices[0]];
		const Vertex& v1 = projected_vertices[indices[1]];
		const Vertex& v2 = projected_vertices[indices[2]];

		// Se asumen coordenadas proyectadas y polígonos definidos en sentido horario.
		// Se comprueba a qué lado de la línea que pasa por v0 y v1 queda el punto v2:

		return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) < 0.f);
	}

	void View::addModel(Model& model)
	{
		models.push_back(&model);
	}

}

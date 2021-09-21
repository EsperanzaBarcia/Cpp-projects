/**
*Esperanza Barcia
* MAY 2021
*/

#pragma once

#include <Mesh.hpp>

//Assimp nos da cada primitiva como una lista de triángulos
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace SceneRenderer
{
	void MeshClass::update(Matrix44& modelTransformation)
	{
		// Se transforman todos los vértices usando la matriz de transformación resultante:

		for (size_t index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
		{
			// Se multiplican todos los vértices originales con la matriz de transformación y
			// se guarda el resultado en otro vertex buffer:

			Vertex& vertex = transformed_vertices[index] = modelTransformation * original_vertices[index];

			// La matriz de proyección en perspectiva hace que el último componente del vector
			// transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

			float divisor = 1.f / vertex.w;

			vertex.x *= divisor;
			vertex.y *= divisor;
			vertex.z *= divisor;
			vertex.w = 1.f;
		}
	}

	void MeshClass::loadMesh(std::string route)
	{
		mesh_route = route;
		//instanciamos el importer
		Assimp::Importer importer;

		//convierte el modelo a un objeto de la librería
		auto scene = importer.ReadFile
		(
			route,
			//post procesado, tras cargarlo qué se hace
			//Se triangula, 
			//se unen los vértices que estén en el mismo sitio (necesario para índices y evitar vértices duplicados),
			//Opcional: divide en submallas
			aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
		);

		//A continuación se hace la relación de los datos de la librería
		//con nuestro sistema
		// Si scene es un puntero nulo significa que el archivo no se pudo cargar con éxito:

		if (scene && scene->mNumMeshes > 0)
		{
			//Para este ejemplo se coge la primera malla solamente:
			//normalmente hay meshes para los ojos, la boca, la ropa
			//si el modelo está formado por varias mallas solo te aparecerá ese trozo
			//si coges la primera nada más
			auto mesh = scene->mMeshes[0];

			size_t number_of_vertices = mesh->mNumVertices;

			// Se copian los datos de coordenadas de vértices:
			//cambiamos el tamaño del vector
			original_vertices.resize(number_of_vertices);

			for (size_t index = 0; index < number_of_vertices; index++)
			{
				//copio los vértices a MI array
				auto& vertex = mesh->mVertices[index];

				original_vertices[index] = Vertex(vertex.x, -vertex.y, vertex.z, 1.f);
			}

			//cambiamos tamaños, se rellenan más adelante
			transformed_vertices.resize(number_of_vertices);
			display_vertices.resize(number_of_vertices);

			// Se inicializan los datos de color de los vértices con colores aleatorios:

			original_colors.resize(number_of_vertices);

			for (size_t index = 0; index < number_of_vertices; index++)
			{
				//Se asignan colores al azar
				//Set espera un valor de coma flotante entre 0 y 1
				//para que se aprecie la geometría con un color plano, DEBERÍA ILUMINARSE
				//con el color del primer vértice se rellena el triángulo
				//se podrían cargar los colores de cada vértice que tenga el modelo ya
				original_colors[index].set(rand_clamp(), rand_clamp(), rand_clamp());
			}

			// Se generan los índices de los triángulos:
			//se extraen las caras de los triángulos
			size_t number_of_triangles = mesh->mNumFaces;

			//se cambia el tamaño del vector, lista de triángulos
			original_indices.resize(number_of_triangles * 3);

			Index_Buffer::iterator indices_iterator = original_indices.begin();

			//se recorren los índices
			for (size_t index = 0; index < number_of_triangles; index++)
			{
				auto& face = mesh->mFaces[index];

				assert(face.mNumIndices == 3);              // Una face puede llegar a tener de 1 a 4 índices,
															// pero nos interesa que solo haya triángulos
				auto indices = face.mIndices;

				//se guardan los índices de 3 en 3
				*indices_iterator++ = int(indices[0]);//primero lo iguala y luego avanza
				*indices_iterator++ = int(indices[1]);
				*indices_iterator++ = int(indices[2]);
			}
		}
	}
	void MeshClass::scale()
	{
		Matrix44 identity(1);
	}
	void MeshClass::translate()
	{
	}
	void MeshClass::render(Matrix44& modelTransformation)
	{
		//renderizar malla

		for (size_t index = 0, number_of_vertices = transformed_vertices.size(); index < number_of_vertices; index++)
		{
			//se truncan los decimales
			display_vertices[index] = Point4i(modelTransformation * transformed_vertices[index]);
		}

	}
}
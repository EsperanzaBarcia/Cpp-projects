/**
* Esperanza Barcia
* MAY 2021
*/

#pragma once

#include <Mesh.hpp>
#include <vector>

namespace SceneRenderer
{
	/**
	*Clase que almacena un modelo 3D
	*/
	class Model
	{

	public:
		/**
		* Mallas que forman parte de este modelo
		*/
		std::vector <MeshClass*> meshes;

	private:
		/**
		* Matriz de escala
		*/
		Matrix44 _scale;

		/**
		* Matriz de rotaci�n
		*/
		Matrix44 _rotation;

		/**
		* Matriz de traslaci�n
		*/
		Matrix44 _translation;

		/**
		* Matriz de proyecci�n de c�mara
		*/
		Matrix44 _projection;

		/**
		* Matriz de transformaci�n final
		*/
		Matrix44 _transformation;

	public:
		/**
		*Constructor que asigna la matriz de transformaci�n inicial
		*/
		Model(Vector3f position, float scale, Matrix44& projection);

		void render(float viewportScaleX, float viewportScaleY);

		/**
		*M�todo que llama al update de las mallas
		*/
		void update();

		void NDC_ToDisplay(float viewportScaleX, float viewportScaleY);
		void translate_Model(Vector3f position);
		void scale_Model(Vector3f newScale);
		//void translate();

		void addMesh(MeshClass& mesh);

	};

}
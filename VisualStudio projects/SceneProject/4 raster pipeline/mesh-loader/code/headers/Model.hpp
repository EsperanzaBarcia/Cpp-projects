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
		* Matriz de rotación
		*/
		Matrix44 _rotation;

		/**
		* Matriz de traslación
		*/
		Matrix44 _translation;

		/**
		* Matriz de proyección de cámara
		*/
		Matrix44 _projection;

		/**
		* Matriz de transformación final
		*/
		Matrix44 _transformation;

	public:
		/**
		*Constructor que asigna la matriz de transformación inicial
		*/
		Model(Vector3f position, float scale, Matrix44& projection);

		void render(float viewportScaleX, float viewportScaleY);

		/**
		*Método que llama al update de las mallas
		*/
		void update();

		void NDC_ToDisplay(float viewportScaleX, float viewportScaleY);
		void translate_Model(Vector3f position);
		void scale_Model(Vector3f newScale);
		//void translate();

		void addMesh(MeshClass& mesh);

	};

}
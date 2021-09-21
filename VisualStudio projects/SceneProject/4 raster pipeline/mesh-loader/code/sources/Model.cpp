/**
* Esperanza Barcia
* MAY 2021
*/

#include <Model.hpp>

namespace SceneRenderer
{
	Model::Model(Vector3f initialPosition, float initialScale, Matrix44& projection)
	{
		Matrix44 identity(1);
		_translation = translate(identity, initialPosition);
		_rotation = glm::rotate(identity, 0.f, glm::vec3(0.f, 0.f, 0.f));
		_scale = scale(identity, initialScale);
		_projection = projection;

		_transformation = _projection * _translation, _rotation, _scale;

	}
	void Model::render(float viewportScaleX, float viewportScaleY)
	{

		Matrix44 transformation = _translation * _scale;
		for (size_t i = 0; i < meshes.size(); i++)
		{
			meshes[i]->render(transformation);
		}
	}

	void Model::update()
	{
		for (size_t i = 0; i < meshes.size(); i++)
		{
			meshes[i]->update(_transformation);
		}
	}


	void Model::NDC_ToDisplay(float viewportScaleX, float viewportScaleY)
	{
		//se escalan los triángulos
		scale_Model(Vector3f(float(viewportScaleX / 10), float(viewportScaleY / 10), 100000000.f));

		//el 0,0 quedaría en una esquina, aquí se cambia
		//para que esté en el centro de la pantalla
		translate_Model(Vector3f{ float(viewportScaleX / 2), float(viewportScaleY / 2), 0.f });
	}

	void Model::translate_Model(Vector3f position)
	{
		Matrix44 identity(1);
		Matrix44 translation = translate(identity, position);
	}

	void Model::scale_Model(Vector3f newScale)
	{
		Matrix44 identity(1);
		//se escalan los triángulos
		Matrix44 scaling = scale(identity, newScale);
	}

	void Model::addMesh(MeshClass& mesh)
	{
		meshes.push_back(&mesh);
	}

}
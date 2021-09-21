// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2021.12 - 2021.04
/**
*Continuado por Esperanza Barcia
* MAY 2021
*/
#include <View.hpp>
#include <Mesh.hpp>
#include <Model.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace SceneRenderer;

int main()
{
	// Create the window and the view that will be shown within the window:

	constexpr auto window_width = 1024u;
	constexpr auto window_height = 720u;

	Window window(VideoMode(window_width, window_height), "Mesh Loader", Style::Titlebar | Style::Close);
	View   view(window_width, window_height);

	Matrix44 projection = perspective(20, 1, 15, float(window_width) / window_height);

	SceneRenderer::Vector3f v(0.f, 0.5f, -10.f);

	//creación primer modelo
	Model model(v, 1.f, projection);

	SceneRenderer::MeshClass mesh;

	mesh.loadMesh("../../../../shared/assets/rpgpp_lt_building_01.fbx");

	model.addMesh(mesh);

	view.addModel(model);

	window.setVerticalSyncEnabled(true);

	// Run the main loop:

	bool exit = false;

	do
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) exit = true;
		}

		view.update();

		view.render();

		window.display();

	} while (not exit);

	return 0;
}

/**
 * @file Control_System.hpp
 *
 * @brief Sistena que procesará los update de todos los componentes de control
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */


#include <Component.hpp>
#include <Controller_Component.hpp>
#include <Entity.hpp>
#include <Control_System.hpp>
#include <Scene.hpp>


namespace engine
{
	void Control_System::run(float delta)
	{
		//toma las entidades y hace el update de aquellas que tengan un controller
		for (auto& item : scene->get_entities())
		{
			Entity& currentEntity = *item.second;

			Component* component = currentEntity.get_Component("controller_component");

			if (component)
			{
				dynamic_cast<Controller_Component*>(currentEntity.get_Component("controller_component"))->update(delta);
			}
		}
	}

}
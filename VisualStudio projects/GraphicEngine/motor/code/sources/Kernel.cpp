/**
 * @file Kernel.hpp
 *
 * @brief El kernel procesará odas las tareas activs en escena
 *En este caso procesará los sitemas: Input, Control y Render en ese orden
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */

#include <Task.hpp>
#include <Kernel.hpp>

namespace engine
{
	void Kernel::run(float delta)
	{
		while (!stopped)
		{
			for (Task* task : tasks)
				task->run(delta);
		}
	}

	void Kernel::stop()
	{
		stopped = true;
	}
}
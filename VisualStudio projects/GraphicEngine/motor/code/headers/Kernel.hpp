/**
 * @file Kernel.hpp
 *
 * @brief El kernel procesar� odas las tareas activs en escena
 *En este caso procesar� los sitemas: Input, Control y Render en ese orden
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */
#include <list>

namespace engine
{
	class Kernel
	{
		bool stopped = false;///< Booleano para parar el kernel
	public:
		std::list<Task*> tasks;///< Lista de tareas a realizar

	public:
		void run(float delta);///< M�todo para ejecutar las tareas
		void stop();///<  Metodo para parar el kernel
	};
}
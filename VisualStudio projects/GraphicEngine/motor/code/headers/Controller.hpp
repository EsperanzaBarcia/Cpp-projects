/**
 * @file Controller.hpp
 *
 * @brief Clase a partir de la cual hereda cada componente de control
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */
#pragma once

namespace engine
{
	class Controller
	{
	public:
        
		virtual void update(float) = 0;///< Método virtual puro que deben rellenar los conmponentes de control
	};
}
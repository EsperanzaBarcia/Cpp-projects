/**
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */
#pragma once
#include <string>

namespace engine
{
	/** Esta clase Event es específica para los eventos de la ventana*/
	struct Event
	{
		enum Type
		{
			CLOSE,
			KEY_PRESSED,
			KEY_RELEASED
		}
		type;

		union Data
		{
			struct { int key_code; } keyboard;

			struct
			{
				float x, y;
				int   buttons;
			}
			mouse;
		}
		data;

	};
}

/**
 *  \author    Esperanza Barcia
 *  \date      Apr 2021
 */

#pragma once
#include <Entity.hpp>
#include <Box2D/Box2D.h>
#include <Body.hpp>
#include <vector>

namespace Box2DExercise
{
	/**
	*Class to handle collision callbacks
	*/
	class ContactListener :public b2ContactListener
	{
	public:
		/**
		*BeginContact Callback 
		*/
		void BeginContact(b2Contact* contact);

		/**
		*EndContact Callback 
		*/
		void EndContact(b2Contact* contact);

	};
}
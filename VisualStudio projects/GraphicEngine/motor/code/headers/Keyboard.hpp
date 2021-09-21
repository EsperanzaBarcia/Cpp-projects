
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu

#pragma once

namespace engine
{

    class Keyboard
    {
    public:

        enum Key_Code
        {
            KEY_UNKOWN,

            KEY_RETURN,
            KEY_ESCAPE,
            KEY_BACKSPACE,
            KEY_TAB,
            KEY_SPACE,

            KEY_A, KEY_B, KEY_C, KEY_D, KEY_E,
            KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
            KEY_K, KEY_L, KEY_M, KEY_N, KEY_O,
            KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
            KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y,
            KEY_Z,

            KEY_0,
            KEY_1,
            KEY_2,
            KEY_3,
            KEY_4,
            KEY_5,
            KEY_6,
            KEY_7,
            KEY_8,
            KEY_9,

            //...
        };

    public:

        /** Esta función sirve para traducir un código de tecla de SDL a uno propio del engine.
          * TO DO: La función se debería "esconder" en lugar de tenerla presente en la interfaz pública
          * (pese a que no crea dependencias con SDL a quien use el engine).
          */
        static Key_Code translate_sdl_key_code (int sdl_key_code);

    };

}


// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu

#include <SDL.h>
#include <Keyboard.hpp>

namespace engine
{

    Keyboard::Key_Code Keyboard::translate_sdl_key_code (int sdl_key_code)
    {
        // Se podría hacer un array de traducción directa, pero con la sentencia
        // switch el compilador lo hará por nosotros de un modo transparente y
        // de sobra eficiente.

        switch (sdl_key_code)
        {
            case SDLK_RETURN:       return KEY_RETURN;
            case SDLK_ESCAPE:       return KEY_ESCAPE;
            case SDLK_BACKSPACE:    return KEY_BACKSPACE;
            case SDLK_TAB:          return KEY_TAB;
            case SDLK_SPACE:        return KEY_SPACE;

            case SDLK_a:            return KEY_A;
            case SDLK_b:            return KEY_B;
            case SDLK_c:            return KEY_C;
            case SDLK_d:            return KEY_D;
            case SDLK_e:            return KEY_E;
            case SDLK_f:            return KEY_F;
            case SDLK_g:            return KEY_G;
            case SDLK_h:            return KEY_H;
            case SDLK_i:            return KEY_I;
            case SDLK_j:            return KEY_J;
            case SDLK_k:            return KEY_K;
            case SDLK_l:            return KEY_L;
            case SDLK_m:            return KEY_M;
            case SDLK_n:            return KEY_N;
            case SDLK_o:            return KEY_O;
            case SDLK_p:            return KEY_P;
            case SDLK_q:            return KEY_Q;
            case SDLK_r:            return KEY_R;
            case SDLK_s:            return KEY_S;
            case SDLK_t:            return KEY_T;
            case SDLK_u:            return KEY_U;
            case SDLK_v:            return KEY_V;
            case SDLK_w:            return KEY_W;
            case SDLK_x:            return KEY_X;
            case SDLK_y:            return KEY_Y;
            case SDLK_z:            return KEY_Z;

            case SDLK_0:            return KEY_0;
            case SDLK_1:            return KEY_1;
            case SDLK_2:            return KEY_2;
            case SDLK_3:            return KEY_3;
            case SDLK_4:            return KEY_4;
            case SDLK_5:            return KEY_5;
            case SDLK_6:            return KEY_6;
            case SDLK_7:            return KEY_7;
            case SDLK_8:            return KEY_8;
            case SDLK_9:            return KEY_9;

            // ...
        }

        return KEY_UNKOWN;
    }

}

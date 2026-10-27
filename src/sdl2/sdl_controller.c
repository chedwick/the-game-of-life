#include "sdl_controller.h"

#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"

// Globally available
SDL_GameController *gGameController = NULL;

void handle_controller_events(SDL_Event* event)
{
    // Xbox controller typically has 1 hat (D-pad)
    int dpad_hat_index = 0;
    switch (event->type)
    {
        case SDL_JOYBUTTONDOWN:
        case SDL_JOYBUTTONUP:
        {
            // Xbox button mapping (standard USB HID layout)
            // A = 0, B = 1, X = 2, Y = 3
            // Back = 6, Start = 7, Guide = 8 (may not trigger), etc.
            int button = event->jbutton.button;
            int state = event->jbutton.state;  // SDL_PRESSED or SDL_RELEASED

            const char *button_name = "Unknown";
            if (button == 0) button_name = "A";
            else if (button == 1) button_name = "B";
            else if (button == 2) button_name = "X";
            else if (button == 3) button_name = "Y";
            else if (button == 6) button_name = "Back";
            else if (button == 7) button_name = "Start";
            else if (button == 8) button_name = "Guide";

            break;
        }
        case SDL_JOYHATMOTION:
        {
            // D-pad is usually hat 0
            if (event->jhat.hat == dpad_hat_index)
            {
                Uint8 value = event->jhat.value;

                // const char *direction = "CENTERED";
                // if (value & SDL_HAT_UP)    direction = "UP";
                // if (value & SDL_HAT_DOWN)  direction = "DOWN";
                // if (value & SDL_HAT_LEFT)  direction = "LEFT";
                // if (value & SDL_HAT_RIGHT) direction = "RIGHT";

                // // Handle diagonals
                // if ((value & SDL_HAT_UP) && (value & SDL_HAT_LEFT))  direction = "UP-LEFT";
                // if ((value & SDL_HAT_UP) && (value & SDL_HAT_RIGHT)) direction = "UP-RIGHT";
                // if ((value & SDL_HAT_DOWN) && (value & SDL_HAT_LEFT)) direction = "DOWN-LEFT";
                // if ((value & SDL_HAT_DOWN) && (value & SDL_HAT_RIGHT)) direction = "DOWN-RIGHT";

                switch (value)
                {
                    case 1:
                        game.key = KEY_UP;
                        break;
                    case 2:
                        game.key = KEY_RIGHT;
                        break;
                    case 4:
                        game.key = KEY_DOWN;
                        break;
                    case 8:
                        game.key = KEY_LEFT;
                        break;
                }

                // TRACEG("D-pad: \n");
            }
            break;
        }

        case SDL_JOYAXISMOTION:
        {
            // Optional: detect left stick as analog D-pad alternative
            // Axis 0 = Left X, Axis 1 = Left Y
            if (event->jaxis.axis == 0 || event->jaxis.axis == 1)
            {
                Sint16 value = event->jaxis.value;
                float norm = value / 32767.0f;

                if (event->jaxis.axis == 0)
                {
                    if (norm < -0.7f) printf("Left Stick: LEFT\n");
                    else if (norm > 0.7f) printf("Left Stick: RIGHT\n");
                }
                else if (event->jaxis.axis == 1)
                {
                    if (norm < -0.7f) printf("Left Stick: UP\n");
                    else if (norm > 0.7f) printf("Left Stick: DOWN\n");
                }
            }
            break;
        }
    }
    if (event->type == SDL_CONTROLLERAXISMOTION)
    {
        // Handle axis (joystick/trigger) motion
        // NOTE: A dead zone check is often necessary for analog sticks
        const int JOYSTICK_DEAD_ZONE = 8000; 

        if (event->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
        {
            if (event->caxis.value < -JOYSTICK_DEAD_ZONE)
            {
                printf("Left Stick X moved Left\n");
            }
            else if (event->caxis.value > JOYSTICK_DEAD_ZONE)
            {
                printf("Left Stick X moved Right\n");
            }
        }
        // ... handle other axes (LEFTY, RIGHTX, RIGHTY, TRIGGERLEFT, TRIGGER_RIGHT)
    }
    else if (event->type == SDL_CONTROLLERDEVICEADDED)
    {
        // Handle hot-plugging of a controller
        // Re-run your controller detection logic here
    }
}


int sdl_initialize_controller()
{
    // Check for connected controllers
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            // Open the controller
            gGameController = SDL_GameControllerOpen(i);
            if (gGameController == NULL)
            {
                printf("Warning: Unable to open game controller %d! \
                      SDL Error: %s\n", i, SDL_GetError());
            }
            else
            {
                // Controller found and opened
                printf("Found and opened game controller:\n");
                printf("%s\n",SDL_GameControllerName(gGameController));
                break; // Use the first controller found
            }
        }
    }

    if (gGameController == NULL)
    {
        printf("No compatible game controller found.\n");
        return -1;
    }

    return 0;
}

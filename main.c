#include <stdio.h>
#include "SDL2/x86_64-w64-mingw32/include/SDL2/SDL.h"
#include <windows.h>
#include <getopt.h>

void press_key(char key);

void move_mouse(int mx, int my);


int main(int argc, char *argv[]) {
    static int press_centre_key = 0;
    double scale_x = 0.0550;
    double scale_y = 0.0170;
    double frame_rate = 60.0;
    char centre_key = 'C';
    int speed_limit_x = 30;
    int speed_limit_y = 10;
    int joystick_number = 0;
    int axis_number_x = 0;
    int axis_number_y = 1;
    int deadzone_x = 2000;
    int deadzone_y = 2000;


    int c;
    while (1)
    {
        static struct option long_options[] =
                {
                        {"enable_centre_key", no_argument,       &press_centre_key, 1},
                        {"disable_centre_key",   no_argument,       &press_centre_key, 0},
                        {"scale_x",    required_argument, 0, 1},
                        {"scale_y",  required_argument, 0, 2},
                        {"frame_rate",  required_argument, 0, 3},
                        {"centre_key",    required_argument, 0, 4},
                        {"speed_limit_x",  required_argument, 0, 5},
                        {"speed_limit_y",    required_argument, 0, 6},
                        {"joystick_number",  required_argument, 0, 7},
                        {"axis_number_x",    required_argument, 0, 8},
                        {"axis_number_y",  required_argument, 0, 9},
                        {"deadzone_x",    required_argument, 0, 10},
                        {"deadzone_y",  required_argument, 0, 11},
                        {0, 0, 0, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 1:
                scale_x =  strtod(optarg,0);
                break;

            case 2:
                scale_y =  strtod(optarg,0);
                break;

            case 3:
                frame_rate = strtod(optarg,0);
                break;

            case 4:
                centre_key = optarg[0];
                break;

            case 5:
                speed_limit_x = strtol(optarg, 0, 10);
                break;

            case 6:
                speed_limit_y = strtol(optarg, 0, 10);
                break;
            case 7:
                joystick_number = strtol(optarg, 0, 10);
                break;
            case 8:
                axis_number_x = strtol(optarg, 0, 10);
                break;
            case 9:
                axis_number_y = strtol(optarg, 0, 10);
                break;
            case 10:
                deadzone_x = strtol(optarg, 0, 10);
                break;
            case 11:
                deadzone_y = strtol(optarg, 0, 10);
                break;


            default:
                puts("abort\n");
                abort();
        }
    }

    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    printf("Number of joysticks connected: %d\n", SDL_NumJoysticks());

    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        printf("Joystick %d: %s\n", i, SDL_JoystickNameForIndex(i));
    }

    printf("\nOptions:\n");
    printf("    --frame_rate %f [number of events to send per second]\n",frame_rate);
    printf("    --scale_x %f   [decrease if movement hits limits at left/right extremes]\n", scale_x);
    printf("    --scale_y %f   [decrease if movement hits limits at top/bottom extremes]\n", scale_y);
    printf("    --disable_centre_key [whether to press key when joystick centred]\n");
    printf("    --enable_centre_key                                 (%i)\n",press_centre_key);
    printf("    --centre_key %c       [key to press when joystick centred]\n",centre_key);
    printf("    --speed_limit_x %i   [max pixels to turn per frame, dont exceed game's limit]\n",speed_limit_x);
    printf("    --speed_limit_y %i   [max pixels to turn per frame, dont exceed game's limit]\n",speed_limit_y);
    printf("    --joystick_number %i  [joystick to use, see list above]\n",joystick_number);
    printf("    --axis_number_x %i    [which axis is x]\n",axis_number_x);
    printf("    --axis_number_y %i    [which axis is y]\n",axis_number_y);
    printf("    --deadzone_x %i    [joystick deadzone horizontal]\n",deadzone_x);
    printf("    --deadzone_y %i    [joystick deadzone vertical]\n",deadzone_y);


    SDL_Init(SDL_INIT_JOYSTICK);
    SDL_Joystick *joystick = SDL_JoystickOpen(joystick_number);
    SDL_Event event;
    int px;
    int py;

    int done = 0;
    while (!done) {
        if (SDL_PollEvent(&event) && event.type == SDL_JOYAXISMOTION) {
            px = SDL_JoystickGetAxis(joystick, axis_number_x) * scale_x;
            py = SDL_JoystickGetAxis(joystick, axis_number_y) * scale_y;
            done = 1;
        }
    }

    while (1) {
        Sleep(1000.0 / frame_rate);
        SDL_PumpEvents();

        int x = SDL_JoystickGetAxis(joystick, axis_number_x) * scale_x;
        int y = SDL_JoystickGetAxis(joystick, axis_number_y) * scale_y;

        if (abs(x) < deadzone_x * scale_x && abs(y) < deadzone_y * scale_y ) {
            x = 0;
            y = 0;
            if(press_centre_key) press_key(centre_key);
        }

        int mx = 0;
        int my = 0;
        mx = x - px;
        my = y - py;
        if (mx < -speed_limit_x) mx = -speed_limit_x;
        if (mx > speed_limit_x) mx = speed_limit_x;
        if (my < -speed_limit_y) my = -speed_limit_y;
        if (my > speed_limit_y) my = speed_limit_y;


        move_mouse(mx, my);

        px = px + mx;
        py = py + my;


    }

    // this code is never run, we need a cleaner way to exit
    SDL_JoystickClose(joystick);
    SDL_Quit();
    return 0;

}

void move_mouse(int mx, int my) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = mx;
    input.mi.dy = my;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    SendInput(1, &input, sizeof(input));
}

void press_key(char key) {
    INPUT ip = {0};
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;


    ip.ki.wVk = key; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
}

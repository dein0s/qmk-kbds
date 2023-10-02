// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(colored_layers)
RGB_MATRIX_EFFECT(touch_typing)
RGB_MATRIX_EFFECT(touch_typing_simple)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "action_layer.h"
#include "color.h"

#define BASE_LAYER 0
#define MEDIA_LAYER 1
#define MAIN_LAYER 2
#define LEFT_LAYER 3
#define RIGHT_LAYER 4
#define ADJUST_LAYER 5

#define BASE_LAYER_COLOR RGB_RED
#define MEDIA_LAYER_COLOR RGB_CHARTREUSE
#define MAIN_LAYER_COLOR RGB_WHITE
#define LEFT_LAYER_COLOR RGB_CYAN
#define RIGHT_LAYER_COLOR RGB_YELLOW
#define ADJUST_LAYER_COLOR RGB_BLUE

bool array_contains(uint8_t *array, size_t array_size, uint8_t element)
{
    for (int i = 0; i < array_size; i++)
    {
        if (array[i] == element)
        {
            return true;
        }
    }

    return false;
}

static bool colored_layers(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
    switch(get_highest_layer(layer_state | default_layer_state)) {
        case BASE_LAYER: // BASE
            rgb_matrix_set_color_all(BASE_LAYER_COLOR);
            break;
        case MEDIA_LAYER: // MEDIA
            rgb_matrix_set_color_all(MEDIA_LAYER_COLOR);
            break;
        case MAIN_LAYER: // MAIN
            rgb_matrix_set_color_all(MAIN_LAYER_COLOR);
            break;
        case LEFT_LAYER: // LEFT
            rgb_matrix_set_color_all(LEFT_LAYER_COLOR);
            break;
        case RIGHT_LAYER: // RIGHT
            rgb_matrix_set_color_all(RIGHT_LAYER_COLOR);
            break;
        case ADJUST_LAYER: // ADJUST
            rgb_matrix_set_color_all(ADJUST_LAYER_COLOR);
            break;
        default:
            break;
    }
  return rgb_matrix_check_finished_leds(led_max);
}

static bool touch_typing(effect_params_t *params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    //                  1 | 0 | Q | P | [ | ] | A | ; | ' | Z | / 
    uint8_t pinkies[] = { 16, 25, 31, 40, 41, 42, 46, 55, 56, 60, 69};
    //                  2 | 9 | W | O | S | L | X | .
    uint8_t ringers[] = { 17, 24, 32, 39, 47, 54, 61, 68 };
    //                      3 | 8 | E | I | D | K | C | ,
    uint8_t middlers[] = { 18, 23, 33, 38, 48, 53, 62, 67 };
    //                          4 | 5 | R | T | F | G | V | B
    uint8_t left_indexes[] = { 19, 20, 34, 35, 49, 50, 63, 64 };
    //                          6 | 7 | Y | U | H | J | N | M
    uint8_t right_indexes[] = { 21, 22, 36, 37, 51, 52, 65, 66 };

    for (int i = led_min; i < led_max; i++)
    {
        if (array_contains(ringers, sizeof(ringers) / sizeof(ringers[0]), i))
        {
            rgb_matrix_set_color(i, RGB_GREEN);
            continue;
        }
        else if (array_contains(middlers, sizeof(middlers) / sizeof(middlers[0]), i))
        {
            rgb_matrix_set_color(i, RGB_ORANGE);
            continue;
        }
        else if (array_contains(pinkies, sizeof(pinkies) / sizeof(pinkies[0]), i))
        {
            rgb_matrix_set_color(i, RGB_YELLOW);
            continue;
        }
        else if (array_contains(left_indexes, sizeof(left_indexes) / sizeof(left_indexes[0]), i))
        {
            rgb_matrix_set_color(i, RGB_PINK);
            continue;
        }
        else if (array_contains(right_indexes, sizeof(right_indexes) / sizeof(right_indexes[0]), i))
        {
            rgb_matrix_set_color(i, RGB_BLUE);
            continue;
        }

        switch (get_highest_layer(layer_state | default_layer_state))
        {
            case BASE_LAYER:
                rgb_matrix_set_color(i, BASE_LAYER_COLOR);
                break;
            case MEDIA_LAYER:
                rgb_matrix_set_color(i, MEDIA_LAYER_COLOR);
                break;
            case MAIN_LAYER:
                rgb_matrix_set_color(i, MAIN_LAYER_COLOR);
                break;
            case LEFT_LAYER:
                rgb_matrix_set_color(i, LEFT_LAYER_COLOR);
                break;
            case RIGHT_LAYER:
                rgb_matrix_set_color(i, RIGHT_LAYER_COLOR);
                break;
            case ADJUST_LAYER:
                rgb_matrix_set_color(i, ADJUST_LAYER_COLOR);
                break;
            default:
                break;
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}


static bool touch_typing_simple(effect_params_t *params)
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    //                  1 | 0 | Q | P | [ | ] | A | ; | ' | Z | / 
    uint8_t pinkies[] = { 16, 25, 31, 40, 41, 42, 46, 55, 56, 60, 69};
    //                  2 | 9 | W | O | S | L | X | .
    uint8_t ringers[] = { 17, 24, 32, 39, 47, 54, 61, 68 };
    //                      3 | 8 | E | I | D | K | C | ,
    uint8_t middlers[] = { 18, 23, 33, 38, 48, 53, 62, 67 };
    //                          4 | 5 | R | T | F | G | V | B
    uint8_t left_indexes[] = { 19, 20, 34, 35, 49, 50, 63, 64 };
    //                          6 | 7 | Y | U | H | J | N | M
    uint8_t right_indexes[] = { 21, 22, 36, 37, 51, 52, 65, 66 };

    for (int i = led_min; i < led_max; i++)
    {
        if (array_contains(ringers, sizeof(ringers) / sizeof(ringers[0]), i))
        {
            rgb_matrix_set_color(i, RGB_GREEN);
            continue;
        }
        else if (array_contains(middlers, sizeof(middlers) / sizeof(middlers[0]), i))
        {
            rgb_matrix_set_color(i, RGB_ORANGE);
            continue;
        }
        else if (array_contains(pinkies, sizeof(pinkies) / sizeof(pinkies[0]), i))
        {
            rgb_matrix_set_color(i, RGB_YELLOW);
            continue;
        }
        else if (array_contains(left_indexes, sizeof(left_indexes) / sizeof(left_indexes[0]), i))
        {
            rgb_matrix_set_color(i, RGB_PINK);
            continue;
        }
        else if (array_contains(right_indexes, sizeof(right_indexes) / sizeof(right_indexes[0]), i))
        {
            rgb_matrix_set_color(i, RGB_BLUE);
            continue;
        }

        if (i != 0)
        {
            rgb_matrix_set_color(i, RGB_BLACK);
            continue;
        }
        else
        {
            switch (get_highest_layer(layer_state | default_layer_state))
            {
                case BASE_LAYER:
                    rgb_matrix_set_color(0, BASE_LAYER_COLOR);
                    break;
                case MEDIA_LAYER:
                    rgb_matrix_set_color(0, MEDIA_LAYER_COLOR);
                    break;
                case MAIN_LAYER:
                    rgb_matrix_set_color(0, MAIN_LAYER_COLOR);
                    break;
                case LEFT_LAYER:
                    rgb_matrix_set_color(0, LEFT_LAYER_COLOR);
                    break;
                case RIGHT_LAYER:
                    rgb_matrix_set_color(0, RIGHT_LAYER_COLOR);
                    break;
                case ADJUST_LAYER:
                    rgb_matrix_set_color(0, ADJUST_LAYER_COLOR);
                    break;
                default:
                    break;
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

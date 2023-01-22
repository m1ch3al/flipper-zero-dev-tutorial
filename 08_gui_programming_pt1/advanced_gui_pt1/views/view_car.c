
/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x08 - Advanced GUI (pt.1) 
 * 
 * An example using multiple view and exit dialog menu  
 * 
 *****************************************************************
 */

#include "view_car.h"

#include <furi.h>
#include <furi_hal.h>
#include <gui/elements.h>

Car* sharedCar;

// The funcion of this view is to to have two differents views 
// that work all together.

static void car_draw_callback(Canvas* canvas, void* context) {
    canvas_clear(canvas);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 14, 27, "Type - ");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 0, 37, "Model -");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 22, 47, "Color - ");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 46, 9, "View car");

    canvas_draw_line(canvas, 0, 13, 127, 13);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 49, 27, sharedCar->carType);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 49, 37, sharedCar->carModel);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 49, 47, sharedCar->carColor);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 45, 61, "Hold back to return");
}

static bool car_input_callback(InputEvent* event, void* context) {
    furi_assert(context);
    Car* car = context;
    if(event->type == InputTypeLong && event->key == InputKeyBack) {
        return false;
    }
    process_car_for_the_view(car, event);
    return true;
}

Car* view_car_alloc() {
    Car* car = malloc(sizeof(Car));
    car->view = view_alloc();

    strncpy(car->carType, "Totoya", BUFFER_SIZE);
    strncpy(car->carModel, "Yaris", BUFFER_SIZE);
    strncpy(car->carColor, "Red", BUFFER_SIZE);

    sharedCar = car;

    view_set_context(car->view, car);
    view_allocate_model(car->view, ViewModelTypeLocking, sizeof(Car));
    view_set_draw_callback(car->view, car_draw_callback);
    view_set_input_callback(car->view, car_input_callback);
    return car;
}

void view_car_free(Car* car) {
    furi_assert(car);
    view_free(car->view);
    free(car);
}

View* view_car_get_view(Car* car) {
    furi_assert(car);
    return car->view;
}

void process_car_for_the_view(Car* car, InputEvent* event) {
    with_view_model(
        car->view,
        PersonalizedViewModel * model,
        {
            if(event->type == InputTypePress) {
                if(event->key == InputKeyOk) {
                    model->ok_pressed = true;
                }
                if(event->key == InputKeyBack) {
                    model->back_pressed = true;
                }
            }
        },
        true);
}

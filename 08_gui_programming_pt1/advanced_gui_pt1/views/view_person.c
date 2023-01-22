
/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x08 - Advanced GUI (pt.1) 
 * 
 * An example using multiple view and exit dialog menu  
 * 
 *****************************************************************
 */

#include "view_person.h"

#include <furi.h>
#include <furi_hal.h>
#include <gui/elements.h>

Person* sharedPerson;

// The drawing callback for the Person* view
static void person_draw_callback(Canvas* canvas, void* context) {
    canvas_clear(canvas);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 14, 27, "Name - ");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 0, 37, "Surname -");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 22, 47, "Age - ");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 46, 9, "View Person");

    canvas_draw_line(canvas, 0, 13, 127, 13);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 49, 27, sharedPerson->name);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 49, 37, sharedPerson->surname);

    char string_age[5];
    itoa(sharedPerson->age, string_age, 10);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 49, 47, string_age);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 45, 61, "Hold back to return");
}

// Manage the input events on this callback from the Person* view
static bool person_input_callback(InputEvent* event, void* context) {
    furi_assert(context);
    Person* person = context;
    if(event->type == InputTypeLong && event->key == InputKeyBack) {
        return false;
    }
    process_person_for_the_view(person, event);
    return true;
}

// Memory allocation and configuration fro the Person* structure/View
Person* view_person_alloc() {
    Person* person = malloc(sizeof(Person));
    person->view = view_alloc();

    strncpy(person->name, "Jhon", BUFFER_SIZE);
    strncpy(person->surname, "Connor", BUFFER_SIZE);
    person->age = 25;

    sharedPerson = person;

    view_set_context(person->view, person);
    view_allocate_model(person->view, ViewModelTypeLocking, sizeof(Person));
    view_set_draw_callback(person->view, person_draw_callback);
    view_set_input_callback(person->view, person_input_callback);
    return person;
}

// Freeing up memory, releasing unused strctures
void view_person_free(Person* person) {
    furi_assert(person);
    view_free(person->view);
    free(person);
}

// Rreturn the View* of this personalized view 
View* view_person_get_view(Person* person) {
    furi_assert(person);
    return person->view;
}

void process_person_for_the_view(Person* person, InputEvent* event) {
    with_view_model(
        person->view,
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

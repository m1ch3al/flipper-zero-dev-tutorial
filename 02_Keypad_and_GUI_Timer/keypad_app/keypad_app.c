/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x02 - Keypad_app
 * 
 * This example shows you how to interact with the keypad on 
 * the Flip.x0, managing the all events stacked in the 
 * FuriMessageQueue. There's also an example of FuriTimer and 
 * how to use them to interact with the GUI.
 *****************************************************************
 */

#include <stdio.h>
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <notification/notification_messages.h>

// (*1) This will be the label that tells you which keypad-button is pressed.
char* currentKeyPressed;
int BUFFER = 10;

static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 34, 12, "First app");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 9, 40, "Key pressed - ");

    canvas_draw_line(canvas, 0, 16, 127, 16);

    // Reference to (*1)
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 71, 40, currentKeyPressed);
}

// (*2) Here we can define a callback for the Timer: every 2 seconds
// the furi-timer system will call our defined callback
static void timer_callback(FuriMessageQueue* event_queue) {
    furi_assert(event_queue);
    currentKeyPressed = "TIMER 2sec.";
}

static void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

int32_t main_fap(void* p) {
    UNUSED(p);
    // Initialization of (*1)
    // corrected by an meitwouldseem, thank you man !
    currentKeyPressed = "NONE";

    InputEvent event;
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, NULL);
    view_port_input_callback_set(view_port, input_callback, event_queue);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    // Creates a furi-timer and associate the proper callback defined in (*2)
    FuriTimer* timer = furi_timer_alloc(timer_callback, FuriTimerTypePeriodic, event_queue);
    // Starts the timer - expiration time in milliseconds (in this case, 2 seconds)
    furi_timer_start(timer, 2000);

    while(1) {
        furi_check(furi_message_queue_get(event_queue, &event, FuriWaitForever) == FuriStatusOk);
        if(event.key == InputKeyLeft) {
            currentKeyPressed = "LEFT";
        }
        if(event.key == InputKeyDown) {
            currentKeyPressed = "DOWN";
        }
        if(event.key == InputKeyRight) {
            currentKeyPressed = "RIGHT";
        }
        if(event.key == InputKeyUp) {
            currentKeyPressed = "UP";
        }
        if(event.key == InputKeyOk) {
            currentKeyPressed = "OK";
        }

        if(event.key == InputKeyBack) {
            break;
        }
    }

    // When you use the timer, remember to stop the timer
    furi_timer_stop(timer);
    // and free up the memory allocated for the timer
    furi_timer_free(timer);

    // Freeing up memory from all the unused resources.
    furi_message_queue_free(event_queue);
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    return 0;
}

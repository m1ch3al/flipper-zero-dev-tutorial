/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x03 - notification_example
 * 
 * This example shows you how to interact with the first type of 
 * notifications used by the Flip.x0, the vibration and the 
 * integrated LED.
 * 0x04 code explains in more detail the various types of 
 * notifications.
 ******************************************************************
 */

#include <stdio.h>
#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>

// This include is necessary for having notifications.
#include <notification/notification_messages.h>

// (1*) The small message on the screen after "Type - "
char* notificationString;
int BUFFER = 10;

// This variable will be used as a example-counter for
// interact with Flip.x0 notifications.
int counter = 0;

// Basically the structure of the FAP is always the same
static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 14, 12, "Notification, LED &Vibro");

    canvas_draw_line(canvas, 2, 18, 125, 18);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 4, 35, "Type -");

    // Update of the label : referring to (1*) as declaration
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 35, 35, notificationString);
}

static void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

// This timer callback checks every 1 seconds the module of the [counter] value.
// If the counter is divisible by 5 then the callback sets a vibration and a
// notification using the integrated led.
static void timer_callback(FuriMessageQueue* event_queue) {
    furi_assert(event_queue);
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    int result = 0;
    counter++;
    result = counter % 5;
    if(result == 0) {
        // turn on the integrated LED: color blue with blink activities
        notification_message(notifications, &sequence_blink_blue_100);

        // Vibration starts... :P
        furi_hal_vibro_on(true);
        notificationString = "LED & VIBRO";
    } else {
        notificationString = "TIMER";
        // Turn off vibration
        furi_hal_vibro_on(false);
    }
}

// Most of the code here, is just commented in the previuos one (0x02)
int32_t main_fap(void* p) {
    UNUSED(p);
    notificationString = (char*)malloc(sizeof(char) * BUFFER);
    notificationString = "OFF";

    InputEvent event;
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, NULL);
    view_port_input_callback_set(view_port, input_callback, event_queue);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    FuriTimer* timer = furi_timer_alloc(timer_callback, FuriTimerTypePeriodic, event_queue);
    furi_timer_start(timer, 1000);

    while(1) {
        furi_check(furi_message_queue_get(event_queue, &event, FuriWaitForever) == FuriStatusOk);

        if(event.key == InputKeyBack) {
            break;
        }
    }

    furi_timer_free(timer);
    furi_message_queue_free(event_queue);

    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);

    return 0;
}


// NEED TO INSERT COMMENTS...BUT THE CODE WORKS !

#include <stdio.h>
#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <notification/notification_messages.h>

char* notificationString;
int BUFFER = 10;
int counter = 0;
int result = 0;

static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 14, 12, "Notification, LED &Vibro");

    canvas_draw_line(canvas, 2, 18, 125, 18);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 4, 35, "Type -");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 35, 35, notificationString);
}

static void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

static void timer_callback(FuriMessageQueue* event_queue) {
    furi_assert(event_queue);
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);

    counter++;
    result = counter % 5;
    if(result == 0) {
        notification_message(notifications, &sequence_blink_blue_100);
        furi_hal_vibro_on(true);
        notificationString = "LED & VIBRO";
    } else {
        notificationString = "TIMER";
        furi_hal_vibro_on(false);
    }
}

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

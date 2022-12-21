#include <stdio.h>
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <notification/notification_messages.h>

char* currentKeyPressed;
int BUFFER = 10;
char* oldStatus;

static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 34, 12, "First app");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 9, 40, "Key pressed - ");

    canvas_draw_line(canvas, 0, 16, 127, 16);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 71, 40, currentKeyPressed);
}

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
    currentKeyPressed = (char*)malloc(sizeof(char) * BUFFER);
    oldStatus = (char*)malloc(sizeof(char) * BUFFER);
    oldStatus = "";
    currentKeyPressed = "NONE";
    InputEvent event;
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, NULL);
    view_port_input_callback_set(view_port, input_callback, event_queue);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    FuriTimer* timer = furi_timer_alloc(timer_callback, FuriTimerTypePeriodic, event_queue);
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

    // When you use the timer - below 2 lines are very important !!
    furi_timer_stop(timer);
    furi_timer_free(timer);

    furi_message_queue_free(event_queue);
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    return 0;
}

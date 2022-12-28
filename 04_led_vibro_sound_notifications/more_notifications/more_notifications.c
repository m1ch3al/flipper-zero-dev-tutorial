/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x04 - more_notifications
 *
 * This example shows you more configurations of notifications like:
 * - leds colors
 * - audio and volumes
 * - create and personalize a NotificationSequence
 ******************************************************************
 */

#include <stdio.h>
#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>

// Theese include is necessary for having notifications.
#include <notification/notification_messages.h>
#include <notification/notification.h>

// (1*) The small message on the screen after "Type - "
char* notificationString;
int BUFFER = 20;

// Basically the structure of the FAP is always the same
static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);

    canvas_clear(canvas);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 29, 15, "More notifications");

    canvas_draw_frame(canvas, 4, 23, 121, 34);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 12, 44, notificationString);
}

static void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

static void vibration_example() {
    notificationString = "3 secs vibration";
    furi_hal_vibro_on(false);
    furi_hal_vibro_on(true);
    furi_delay_ms(3000);
    furi_hal_vibro_on(false);
    notificationString = "";
    return;
}

static void display_on() {
    notificationString = "Display ON";
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    notification_message(notifications, &sequence_display_backlight_on);
    return;
}

// This functions shows you how to use the blinking functions on the
// integrated LED on your Flip.x0
static void blinking_integrated_LED() {
    notificationString = "Blinking LED";
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    notification_message(notifications, &sequence_blink_red_100);
    furi_delay_ms(1000);
    notification_message(notifications, &sequence_blink_green_100);
    furi_delay_ms(1000);
    notification_message(notifications, &sequence_blink_blue_100);
    furi_delay_ms(1000);
    notification_message(notifications, &sequence_blink_yellow_100);
    furi_delay_ms(1000);
    notification_message(notifications, &sequence_blink_cyan_100);
    furi_delay_ms(1000);
    notification_message(notifications, &sequence_blink_magenta_100);
    furi_delay_ms(1000);
    notification_message(notifications, &sequence_blink_white_100);
    return;
}

// I created my personal NotificationSequence
// the sequence starts turning off the backlight of the diplay
const NotificationSequence my_sequence = {
    &message_display_backlight_off,
    &message_note_e4,
    &message_delay_1000,
    &message_note_c4,
    &message_delay_1000,
    NULL,
};

// I think the name of the function means all.
// All definitions of the various note are in : [your_firmware_folder]/applications/services/notification/notification_messages_notes.c
static void generate_sounds() {
    notificationString = "Generate sound";
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    notification_message(notifications, &sequence_success);
    furi_delay_ms(1000);
    notification_message(notifications, &sequence_error);
    furi_delay_ms(1000);
    // Here I can call my personalized sequence to generate a Notification
    notification_message(notifications, &my_sequence);
}

// Most of the code here, is just commented in the previuos one (0x02)
int32_t main_fap(void* p) {
    UNUSED(p);
    notificationString = (char*)malloc(sizeof(char) * BUFFER);
    notificationString = "Notifications";

    InputEvent event;
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, NULL);
    view_port_input_callback_set(view_port, input_callback, event_queue);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    bool first_time = true;

    while(1) {
        if(first_time == true) {
            notificationString = "Notifications";
            furi_delay_ms(1000);
            display_on();
            vibration_example();
            blinking_integrated_LED();
            generate_sounds();
        } else {
            first_time = false;
            notificationString = "Press back to exit";
        }
        furi_check(furi_message_queue_get(event_queue, &event, FuriWaitForever) == FuriStatusOk);
        if(event.key == InputKeyBack) {
            break;
        }
    }

    furi_message_queue_free(event_queue);

    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);

    return 0;
}

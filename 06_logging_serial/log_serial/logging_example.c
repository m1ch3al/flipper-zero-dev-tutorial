/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x06 - Logging example
 * 
 * Learn how to integrate the serial logging through FlipperCLI 
 * 
 *****************************************************************
 */

#include <stdio.h>
#include <furi.h>
#include <gui/gui.h>
#include <string.h>

// I increased the beauty of the GUI using more views
#include "menu.h"

int menu_stage = 0;

static void draw_callback(Canvas* canvas, void* context) {
    if(menu_stage == 0) {
        draw_splash_screen(canvas);
    }
    if(menu_stage == 1) {
        draw_log_interface(canvas);
    }
    if(menu_stage == 2) {
        draw_quit_application(canvas);
    }
}

static void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

// Here we generates variuos types of LOG message
static void generate_logs(void) {
    for(int i = 0; i < 10; i++) {
        // This is an INFORMATION message
        FURI_LOG_I("INFORMATION tag", "This is an INFORMATION-LOG message !!");
        furi_delay_ms(5000);

        // This is an DEBUG message
        FURI_LOG_D("DEBUG tag", "This is a DEBUG-LOG message !!");
        furi_delay_ms(5000);

        // this is a WARNING message
        FURI_LOG_W("WARNING tag", "This is a WARNING-LOG message !!");
        furi_delay_ms(5000);

        // This is an ERROR message
        FURI_LOG_E("ERROR tag", "This is a ERROR-LOG message !!");
        furi_delay_ms(5000);
    }
}

int32_t main_fap(void* p) {
    UNUSED(p);
    InputEvent event;
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, NULL);
    view_port_input_callback_set(view_port, input_callback, event_queue);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    bool request_exit = false;
    while(1) {
        furi_check(furi_message_queue_get(event_queue, &event, FuriWaitForever) == FuriStatusOk);
        if(event.key == InputKeyOk && menu_stage == 0) {
            menu_stage = 1;
            generate_logs();
        }
        if(event.key == InputKeyBack) {
            menu_stage = 2;
            furi_delay_ms(3000);
            break;
        }
    }

    // Freeing up memory from all the unused resources.
    furi_message_queue_free(event_queue);
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    return 0;
}

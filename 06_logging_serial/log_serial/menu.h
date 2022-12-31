#include <furi.h>
#include <input/input.h>
#include <notification/notification_messages.h>
#include <gui/gui.h>
#include <furi_hal.h>
#include "logging_example_icons.h"

static void draw_splash_screen(Canvas* canvas) {
    canvas_clear(canvas);
    canvas_draw_icon(canvas, 0, 4, &I_Background_128x11);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 83, 25, "Example");
    canvas_draw_icon(canvas, 5, 0, &I_Space_65x18);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 18, 12, "Logging");
    canvas_draw_icon(canvas, -2, 24, &I_WarningDolphin_45x42);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 50, 46, "Use FlipperCLI");
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 73, 57, "and press OK");
}

static void draw_log_interface(Canvas* canvas) {
    canvas_clear(canvas);
    canvas_draw_icon(canvas, 0, 16, &I_DFU_128x50);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 3, 8, "Generating LOG messages");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 10, 20, "every 5 secs.");
}

static void draw_quit_application(Canvas* canvas) {
    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 5, 37, "Bye bye M8!");
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 44, 12, "Returning to OS...");
    canvas_draw_icon(canvas, 72, 17, &I_DolphinCommon_56x48);
}

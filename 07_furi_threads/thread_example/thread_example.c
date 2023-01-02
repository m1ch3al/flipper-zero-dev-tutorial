/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x07 - Thread example
 * 
 * An exaample using the FuriThreads  
 * 
 *****************************************************************
 */

#include <stdio.h>
#include <furi.h>
#include <gui/gui.h>
#include <string.h>
#include <furi_hal.h>
#include <stdlib.h>
#include <string.h>

#include "thread_example_icons.h"

#define BUFFER_SIZE 10

typedef struct {
    int time_table_number;
    FuriThread* thread;
} TimeTableThread;

bool stop;

int time_table_2;
int time_table_3;
int time_table_5;
int time_table_8;

TimeTableThread* timeTableThread2;
TimeTableThread* timeTableThread3;
TimeTableThread* timeTableThread5;
TimeTableThread* timeTableThread8;

static void draw_callback(Canvas* canvas, void* context) {
    char label_time_table_2[BUFFER_SIZE];
    itoa(time_table_2, label_time_table_2, BUFFER_SIZE);

    char label_time_table_3[BUFFER_SIZE];
    itoa(time_table_3, label_time_table_3, BUFFER_SIZE);

    char label_time_table_5[BUFFER_SIZE];
    itoa(time_table_5, label_time_table_5, BUFFER_SIZE);

    char label_time_table_8[BUFFER_SIZE];
    itoa(time_table_8, label_time_table_8, BUFFER_SIZE);

    canvas_draw_icon(canvas, -1, 24, &I_WarningDolphin_45x42);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 2, 9, "Flip.x0 teaching times tables");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 52, 30, "n.2 - ");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 52, 40, "n.3 - ");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 52, 50, "n.5 - ");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 52, 60, "n.8 - ");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 75, 30, label_time_table_2);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 75, 40, label_time_table_3);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 75, 50, label_time_table_5);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 75, 60, label_time_table_8);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 2, 19, "press OK to start...");
}

static void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

// Function associated to the thread execution
static int32_t thread_body(void* context) {
    TimeTableThread* time_table_thread = (TimeTableThread*)context;

    while(!stop) {
        if(time_table_thread->time_table_number == 2) {
            time_table_2 += time_table_thread->time_table_number;
            furi_delay_ms(1200);
        }
        if(time_table_thread->time_table_number == 3) {
            time_table_3 += time_table_thread->time_table_number;
            furi_delay_ms(1500);
        }
        if(time_table_thread->time_table_number == 5) {
            time_table_5 += time_table_thread->time_table_number;
            furi_delay_ms(1000);
        }
        if(time_table_thread->time_table_number == 8) {
            time_table_8 += time_table_thread->time_table_number;
            furi_delay_ms(2200);
        }
    }
    return 0;
}

static void start_thread_count(TimeTableThread* timeTableThread) {
    char string_time_table[BUFFER_SIZE];
    itoa(timeTableThread->time_table_number, string_time_table, BUFFER_SIZE);
    char thread_name[25] = "ThreadTimeTable_";
    strcat(thread_name, string_time_table);

    timeTableThread->thread = furi_thread_alloc();
    furi_thread_set_name(timeTableThread->thread, thread_name);
    furi_thread_set_stack_size(timeTableThread->thread, 1024);
    furi_thread_set_context(timeTableThread->thread, timeTableThread);
    furi_thread_set_callback(timeTableThread->thread, thread_body);
    furi_thread_start(timeTableThread->thread);
    return;
}

static void intialize_thread(int time_table_value) {
    if(time_table_value == 2) {
        timeTableThread2 = malloc(sizeof(TimeTableThread));
        timeTableThread2->time_table_number = time_table_value;
        start_thread_count(timeTableThread2);
    }
    if(time_table_value == 3) {
        timeTableThread3 = malloc(sizeof(TimeTableThread));
        timeTableThread3->time_table_number = time_table_value;
        start_thread_count(timeTableThread3);
    }
    if(time_table_value == 5) {
        timeTableThread5 = malloc(sizeof(TimeTableThread));
        timeTableThread5->time_table_number = time_table_value;
        start_thread_count(timeTableThread5);
    }
    if(time_table_value == 8) {
        timeTableThread8 = malloc(sizeof(TimeTableThread));
        timeTableThread8->time_table_number = time_table_value;
        start_thread_count(timeTableThread8);
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

    time_table_2 = 0;
    time_table_3 = 0;
    time_table_5 = 0;
    time_table_8 = 0;

    stop = false;
    while(1) {
        furi_check(furi_message_queue_get(event_queue, &event, FuriWaitForever) == FuriStatusOk);
        if(event.key == InputKeyOk) {
            // start counts
            intialize_thread(2);
            intialize_thread(3);
            intialize_thread(5);
            intialize_thread(8);
        }
        if(event.key == InputKeyBack) {
            stop = true;
            break;
        }
    }

    furi_thread_join(timeTableThread2->thread);
    furi_thread_join(timeTableThread3->thread);
    furi_thread_join(timeTableThread5->thread);
    furi_thread_join(timeTableThread8->thread);

    furi_thread_free(timeTableThread2->thread);
    furi_thread_free(timeTableThread3->thread);
    furi_thread_free(timeTableThread5->thread);
    furi_thread_free(timeTableThread8->thread);

    free(timeTableThread2);
    free(timeTableThread3);
    free(timeTableThread5);
    free(timeTableThread8);

    // Freeing up memory from all the unused resources.
    furi_message_queue_free(event_queue);
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    return 0;
}

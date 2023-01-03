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

// This file is generated automatically when you want to
// use images inside your GUI
#include "thread_example_icons.h"

#define BUFFER_SIZE 10

// I define a structure composed by the number of the time table
// to generate and a pointer to a FuriThread
typedef struct {
    int time_table_number;
    FuriThread* thread;
} TimeTableThread;

int time_table_2;
int time_table_5;
// I created two time tables : 2 and 5
TimeTableThread* timeTableThread2;
TimeTableThread* timeTableThread5;

// This variable tells to the threads when
// they have to stop theiself.
bool stop;

static void draw_callback(Canvas* canvas, void* context) {
    // Convert here from integer to string, the value of the time-table
    // generated and updated from the timeTableThread(n)
    char label_time_table_2[BUFFER_SIZE];
    itoa(time_table_2, label_time_table_2, BUFFER_SIZE);
    char label_time_table_5[BUFFER_SIZE];
    itoa(time_table_5, label_time_table_5, BUFFER_SIZE);

    // GUI design
    canvas_draw_icon(canvas, -1, 24, &I_WarningDolphin_45x42);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 2, 9, "Flip.x0 teaching times tables");
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 52, 30, "n.2 - ");
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 52, 50, "n.5 - ");
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 2, 19, "press OK to start...");

    // The GUI update the value of the time-tables
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 75, 30, label_time_table_2);
    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 75, 50, label_time_table_5);
}

static void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

// This function is the BODY of the thread. When the thread will
// start, this function will be executed.
static int32_t thread_body(void* context) {
    TimeTableThread* time_table_thread = (TimeTableThread*)context;
    while(!stop) {
        if(time_table_thread->time_table_number == 2) {
            time_table_2 += time_table_thread->time_table_number;
            furi_delay_ms(200);
        }
        if(time_table_thread->time_table_number == 5) {
            time_table_5 += time_table_thread->time_table_number;
            furi_delay_ms(750);
        }
    }
    return 0;
}

// this function allocate memory for a FuriThread, it sets the name, the stack size,
// the content, the callback and starts it.
static void configure_and_start_thread(TimeTableThread* timeTableThread) {
    char string_time_table[BUFFER_SIZE];
    itoa(timeTableThread->time_table_number, string_time_table, BUFFER_SIZE);
    char thread_name[25] = "ThreadTimeTable_";
    strcat(thread_name, string_time_table);

    // Memory allocation for the FuriThread
    timeTableThread->thread = furi_thread_alloc();
    // Setting the name of the FuriThread
    furi_thread_set_name(timeTableThread->thread, thread_name);
    // Setting the stack size
    furi_thread_set_stack_size(timeTableThread->thread, 1024);
    // Setting the *context
    furi_thread_set_context(timeTableThread->thread, timeTableThread);
    // Setting the callback - keep in mind that the signature of the function
    // must be like this : static int32_t thread_body(void* context)
    furi_thread_set_callback(timeTableThread->thread, thread_body);
    // Starts the FuriThread !!
    furi_thread_start(timeTableThread->thread);
    return;
}

// This function is made for initialize the FuriThreads.
// Since we have two identical thread (it changes only the time-table value), the function
// configure_and_start_thread() is made for avioid code repetition.
static void intialize_thread(int time_table_value) {
    if(time_table_value == 2) {
        timeTableThread2 = malloc(sizeof(TimeTableThread));
        timeTableThread2->time_table_number = time_table_value;
        configure_and_start_thread(timeTableThread2);
    }
    if(time_table_value == 5) {
        timeTableThread5 = malloc(sizeof(TimeTableThread));
        timeTableThread5->time_table_number = time_table_value;
        configure_and_start_thread(timeTableThread5);
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
    time_table_5 = 0;

    stop = false;
    while(1) {
        furi_check(furi_message_queue_get(event_queue, &event, FuriWaitForever) == FuriStatusOk);
        if(event.key == InputKeyOk) {
            // The user press OK and we can start to create FuriThreads, allocate memory for them
            // configure FuriThread parameters and finally start the FuriThread.
            intialize_thread(2);
            intialize_thread(5);
        }
        if(event.key == InputKeyBack) {
            stop = true;
            break;
        }
    }

    furi_delay_ms(500);

    // Wait fot the correct termination of the FuriThreads
    furi_thread_join(timeTableThread2->thread);
    furi_thread_join(timeTableThread5->thread);

    // VERY IMPORTANT !!
    // Once the user wants press back, it's VERY IMPORTANT to release and free-up the
    // resources/memory allocated for the FuriThreads.
    furi_thread_free(timeTableThread2->thread);
    furi_thread_free(timeTableThread5->thread);

    // Free-up the memory for the allocation
    free(timeTableThread2);
    free(timeTableThread5);

    // Freeing up memory from all the unused resources.
    furi_message_queue_free(event_queue);
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    return 0;
}

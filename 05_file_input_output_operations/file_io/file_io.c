/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 
 * 0x05 - FILE I/O 
 * 
 * This example shows you how to work with file I/O
 * Create and Read the content of a simple text file.
 * Rename and delete operation on the filesystem
 ******************************************************************
 */

#include <stdio.h>
#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <notification/notification_messages.h>
#include <notification/notification.h>
#include <storage/filesystem_api_defines.h>
#include <storage/storage.h>

char* main_label;
char* line_upper;
char* line_center;
char* line_bottom;
int BUFFER = 30;

// Basically the structure of the FAP is always the same
static void draw_callback(Canvas* canvas, void* ctx) {
    UNUSED(ctx);
    canvas_clear(canvas);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 24, 9, "File (Input/Output)");

    canvas_draw_line(canvas, 0, 12, 126, 12);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 1, 23, main_label);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 1, 32, line_upper);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 1, 42, line_center);

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 1, 52, line_bottom);
}

static void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    FuriMessageQueue* event_queue = ctx;
    furi_message_queue_put(event_queue, input_event, FuriWaitForever);
}

// This function creates a simple text file.
static void create_file() {
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);

    // We need a storage struct (gain accesso to the filesystem API )
    Storage* storage = furi_record_open(RECORD_STORAGE);

    // storage_file_alloc gives to us a File pointer using the Storage API.
    File* file = storage_file_alloc(storage);

    // this functions open a file, using write access and creates new file if not exist.
    // Full declaration and more detailes information can be found here :
    // [firmware_folder]/applications/services/storage/filesystem_api_defines.h
    // the directive EXT_PATH tells that your Flip.x0 will use the external storate (microSD)
    bool result =
        storage_file_open(file, EXT_PATH("apps/Examples/test.log"), FSAM_WRITE, FSOM_OPEN_ALWAYS);
    char* content = (char*)malloc(sizeof(char) * BUFFER);
    content = "This is an Awesome test !!\n";
    if(result) {
        // this function write data on a file
        storage_file_write(file, content, strlen(content));

        // Closing the "file descriptor"
        storage_file_close(file);

        // Freeing up memory
        storage_file_free(file);
        notification_message(notifications, &sequence_success);
        main_label = "File created successfully.";
        line_upper = "press LEFT for read the file";
        line_center = "press RIGHT for rename the file";
        line_bottom = "press DOWN for delete the file";
    } else {
        main_label = "Error: file not created.";
        notification_message(notifications, &sequence_error);
    }
    return;
}

// Same concept as create_file() function but...
static void read_file() {
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    char* filepath;
    filepath = (char*)malloc(sizeof(char) * BUFFER);
    filepath = "apps/Examples/test.log";
    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);

    // here I used FSOM_OPEN_EXISTING (Open file, fail if file doesn't exist)
    bool result =
        storage_file_open(file, EXT_PATH("apps/Examples/test.log"), FSAM_READ, FSOM_OPEN_EXISTING);

    if(result) {
        int buffer_size = 128;
        char* buffer = (char*)malloc(sizeof(char) * buffer_size);

        // read the content of the file and insert into a buffer.
        storage_file_read(file, buffer, buffer_size);
        line_upper = "file content:";
        line_center = "";
        line_bottom = buffer;

        // free resources
        storage_file_close(file);
        storage_file_free(file);
        notification_message(notifications, &sequence_success);
    } else {
        main_label = "Can't read the file content.";
        notification_message(notifications, &sequence_error);
    }
}

// ------------- Filesystem operations -------------
static void rename_file() {
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    Storage* storage = furi_record_open(RECORD_STORAGE);

    // storage_common_rename functions allow you to rename a file inside the filesystem
    FS_Error result = storage_common_rename(
        storage, EXT_PATH("apps/Examples/test.log"), EXT_PATH("apps/Examples/test2.log"));
    if(result == FSE_OK) {
        notification_message(notifications, &sequence_success);
        main_label = "Rename op. successfully";
        return;
    } else {
        main_label = "Can't rename the file.";
        notification_message(notifications, &sequence_error);
    }
}

// The function is very similar to the rename_file()
static void delete_file() {
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    Storage* storage = furi_record_open(RECORD_STORAGE);

    // the functions for delete a file from the filesystem is [storage_common_remove]
    FS_Error result = storage_common_remove(storage, EXT_PATH("apps/Examples/test.log"));
    if(result == FSE_OK) {
        notification_message(notifications, &sequence_success);
        main_label = "Delete op. successfully";
        return;
    } else {
        FS_Error result = storage_common_remove(storage, EXT_PATH("apps/Examples/test2.log"));
        if(result == FSE_OK) {
            notification_message(notifications, &sequence_success);
            main_label = "Delete op. successfully";
            return;
        } else {
            main_label = "Can't delete the file.";
            notification_message(notifications, &sequence_error);
            return;
        }
        main_label = "Can't delete the file.";
        notification_message(notifications, &sequence_error);
        return;
    }
}

// Most of the code here, is just commented in the previuos one (0x02)
int32_t main_fap(void* p) {
    UNUSED(p);
    main_label = (char*)malloc(sizeof(char) * BUFFER);
    main_label = "Press OK for create a file";

    InputEvent event;
    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, NULL);
    view_port_input_callback_set(view_port, input_callback, event_queue);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    bool file_created = false;
    int choose_value = 0;
    while(1) {
        furi_check(furi_message_queue_get(event_queue, &event, FuriWaitForever) == FuriStatusOk);
        if(event.key == InputKeyOk && file_created == false) {
            create_file();
            furi_record_close(RECORD_NOTIFICATION);
            file_created = true;
        }
        if(event.key == InputKeyLeft && file_created == true) {
            line_upper = "press OK for READ the file";
            line_center = "";
            line_bottom = "";
            choose_value = 1;
        }
        if(event.key == InputKeyRight && file_created == true) {
            line_upper = "press OK for RENAME the file";
            line_center = "";
            line_bottom = "";
            choose_value = 2;
        }
        if(event.key == InputKeyDown && file_created == true) {
            line_upper = "press OK for DELETE the file";
            line_center = "";
            line_bottom = "";
            choose_value = 3;
        }

        if(event.key == InputKeyOk && choose_value > 0) {
            if(choose_value == 1) {
                choose_value = 0;
                line_upper = "";
                line_center = "READING file";
                line_bottom = "";
                read_file();
                furi_record_close(RECORD_NOTIFICATION);
            }
            if(choose_value == 2) {
                choose_value = 0;
                line_upper = "";
                line_center = "RENAMING file";
                line_bottom = "";
                rename_file();
                furi_record_close(RECORD_NOTIFICATION);
            }
            if(choose_value == 3) {
                choose_value = 0;
                line_upper = "";
                line_center = "DELETING file";
                line_bottom = "";
                delete_file();
                furi_record_close(RECORD_NOTIFICATION);
            }
        }

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
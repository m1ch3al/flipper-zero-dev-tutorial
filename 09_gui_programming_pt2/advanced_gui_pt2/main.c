
/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x09 - Advanced GUI (pt.2) 
 * 
 * An example to show you how to create TextInput, Textbox and
 * 3 types of Buttons (left, center, right) inside a Widget 
 * 
 *****************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <notification/notification.h>
#include <notification/notification_messages.h>

#include "advanced_gui.h"

int32_t main_fap(void* p) {
    UNUSED(p);

    // Turn on the display
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    notification_message(notifications, &sequence_display_backlight_on);

    // Inside [advanced_gui.c] there's the implementation of the application

    // Here, my app will be allocated
    AdvancedGUI* app = advanced_gui_app_alloc();

    // Start the application :)
    run_flipper_application(app);
    return 0;
}

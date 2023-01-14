/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x08 - Advanced GUI example
 * 
 * An example using advanced GUI components, like menus, 
 * dialogs, button and more.   
 * 
 *****************************************************************
 */

/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x08 - Advanced GUI (pt.1) 
 * 
 * An example using multiple view and exit dialog menu  
 * 
 *****************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <furi.h>
#include <furi_hal.h>
#include <notification/notification.h>
#include <notification/notification_messages.h>

#include "advanced_gui.h"
#include "views/view_person.h"
#include "views/view_car.h"

int32_t main_fap(void* p) {
    UNUSED(p);

    // I want to turn on the display
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);
    notification_message(notifications, &sequence_display_backlight_on);

    // Here, my app will be allocated
    AdvancedGUI* app = advanced_gui_app_alloc();

    // I need to call view_dispatcher_run() to launch the GUI
    // see structures.h for more information about the struct used in this example
    view_dispatcher_run(app->view_dispatcher);

    // freeing memory and return to FreeRTOS
    advanced_gui_app_free(app);
    return 0;
}

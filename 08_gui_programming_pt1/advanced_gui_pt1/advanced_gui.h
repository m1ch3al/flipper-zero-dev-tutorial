
/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x08 - Advanced GUI (pt.1) 
 * 
 * An example using multiple view and exit dialog menu  
 * 
 *****************************************************************
 */

#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>
#include <gui/view.h>

#include "structures.h"

void submenu_callback(void* context, uint32_t index);
uint32_t application_exit(void* context);
AdvancedGUI* advanced_gui_app_alloc();
uint32_t exit_confirm_view(void* context);
void app_dialog_callback(DialogExResult result, void* context);
void advanced_gui_app_free(AdvancedGUI* app);
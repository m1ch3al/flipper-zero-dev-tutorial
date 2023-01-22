
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

#include "structures.h"

void submenu_callback(void* ctx, uint32_t index);
void text_input_callback(void* ctx);
bool back_event_callback(void* ctx);
void configure_submenu(AdvancedGUI* app);
void configure_text_input_box(AdvancedGUI* app, ValueMutex* state_mutex);
static void button_callback(GuiButtonType result, InputType type, void* context);
void configure_widget(AdvancedGUI* app, ValueMutex* state_mutex);
void configure_view_dispatcher(AdvancedGUI* app, ValueMutex* state_mutex);
AdvancedGUI* advanced_gui_app_alloc();
void advanced_gui_app_free(AdvancedGUI* app);
void run_flipper_application(AdvancedGUI* app);

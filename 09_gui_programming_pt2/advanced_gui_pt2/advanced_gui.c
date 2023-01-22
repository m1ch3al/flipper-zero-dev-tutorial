
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

#include "advanced_gui.h"

// Callback when I'll make a choice on the first view of the FAP
void submenu_callback(void* ctx, uint32_t index) {
    furi_assert(ctx);
    AdvancedGUI* app = ctx;
    if(index == SubMenuTextInput) {
        app->view_id = ViewTextInputBoxExample;
        view_dispatcher_switch_to_view(app->view_dispatcher, ViewTextInputBoxExample);
    }
    if(index == SubMenuButton) {
        app->view_id = ViewWidgetButtonsExample;
        view_dispatcher_switch_to_view(app->view_dispatcher, ViewWidgetButtonsExample);
    }
}

// Callback for manage the "save" button
void text_input_callback(void* ctx) {
    AdvancedGUI* app = acquire_mutex((ValueMutex*)ctx, 25);
    FURI_LOG_D("text_input_callback", "Input text: %s", app->input);
    text_box_set_text(app->text_box, app->input);
    view_dispatcher_switch_to_view(app->view_dispatcher, ViewTextBoxExample);
    release_mutex((ValueMutex*)ctx, app);
}

bool back_event_callback(void* ctx) {
    const AdvancedGUI* app = acquire_mutex((ValueMutex*)ctx, 25);
    view_dispatcher_stop(app->view_dispatcher);
    release_mutex((ValueMutex*)ctx, app);
    return true;
}

// adding items on the submenu
void configure_submenu(AdvancedGUI* app) {
    submenu_add_item(app->submenu, "TextInput/Textbox", SubMenuTextInput, submenu_callback, app);
    submenu_add_item(app->submenu, "Widget/Buttons", SubMenuButton, submenu_callback, app);
}

// Configuration for the TextInputBox (callback, header, and others stuff)
void configure_text_input_box(AdvancedGUI* app, ValueMutex* state_mutex) {
    // for more information, please have a trip on the following source code:
    // [your-firmware-folder]/applications/services/gui/modules/text_input.c
    text_input_set_result_callback(
        app->text_input, text_input_callback, state_mutex, app->input, TEXT_BUFFER_SIZE, true);
    text_input_set_header_text(app->text_input, "Input Text Box");
}

// Callback for the buttons (Please, activate the serial LOG on the FlipperZero CLI)
static void button_callback(GuiButtonType result, InputType type, void* context) {
    if((result == GuiButtonTypeLeft) && (type == InputTypeShort)) {
        FURI_LOG_D("button_callback", "Button labelled LEFT is pressed");
    }
    if((result == GuiButtonTypeRight) && (type == InputTypeShort)) {
        FURI_LOG_D("button_callback", "Button labelled RIGHT is pressed");
    }
    if((result == GuiButtonTypeCenter) && (type == InputTypeShort)) {
        FURI_LOG_D("button_callback", "Button labelled CENTER is pressed (short press)");
    }
    if((result == GuiButtonTypeCenter) && (type == InputTypeLong)) {
        FURI_LOG_D("button_callback", "Button labelled CENTER is pressed (long press)");
    }
}

// Create inside a Widget*, three (3) buttons
void configure_widget(AdvancedGUI* app, ValueMutex* state_mutex) {
    widget_add_button_element(app->widget, GuiButtonTypeLeft, "LEFT", button_callback, app);
    widget_add_button_element(app->widget, GuiButtonTypeCenter, "CNTR", button_callback, app);
    widget_add_button_element(app->widget, GuiButtonTypeRight, "RGHT", button_callback, app);
    widget_add_string_element(
        app->widget, 63, 20, AlignCenter, AlignCenter, FontPrimary, "See LOGs on Flipper CLI");
}

void configure_view_dispatcher(AdvancedGUI* app, ValueMutex* state_mutex) {
    // Gui
    app->gui = furi_record_open(RECORD_GUI);
    view_dispatcher_enable_queue(app->view_dispatcher);
    // View dispatcher
    view_dispatcher_add_view(
        app->view_dispatcher, ViewSubmenuExample, submenu_get_view(app->submenu));
    view_dispatcher_add_view(
        app->view_dispatcher, ViewTextInputBoxExample, text_input_get_view(app->text_input));
    view_dispatcher_add_view(
        app->view_dispatcher, ViewTextBoxExample, text_box_get_view(app->text_box));
    view_dispatcher_add_view(
        app->view_dispatcher, ViewWidgetButtonsExample, widget_get_view(app->widget));

    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);

    view_dispatcher_set_navigation_event_callback(app->view_dispatcher, back_event_callback);
    view_dispatcher_set_event_callback_context(app->view_dispatcher, state_mutex);
    view_dispatcher_switch_to_view(app->view_dispatcher, ViewSubmenuExample);
}

// Allocation of the (GUI) components for the Application
AdvancedGUI* advanced_gui_app_alloc() {
    AdvancedGUI* app = malloc(sizeof(AdvancedGUI));
    app->view_dispatcher = view_dispatcher_alloc();
    app->text_input = text_input_alloc();
    app->text_box = text_box_alloc();
    text_box_set_font(app->text_box, TextBoxFontText);
    app->submenu = submenu_alloc();
    app->widget = widget_alloc();
    return app;
}

// Freeing up the memory from the unused objects
void advanced_gui_app_free(AdvancedGUI* app) {
    furi_assert(app);
    text_input_free(app->text_input);
    text_box_free(app->text_box);
    widget_free(app->widget);
    submenu_free(app->submenu);
    // Free views
    view_dispatcher_remove_view(app->view_dispatcher, ViewSubmenuExample);
    view_dispatcher_remove_view(app->view_dispatcher, ViewTextBoxExample);
    view_dispatcher_remove_view(app->view_dispatcher, ViewTextInputBoxExample);
    view_dispatcher_remove_view(app->view_dispatcher, ViewWidgetButtonsExample);
    view_dispatcher_free(app->view_dispatcher);
    // Close gui record
    furi_record_close(RECORD_GUI);
    app->gui = NULL;
    // Free rest
    free(app);
}

// Calling this function, will call all the functions needed for running the FAP
void run_flipper_application(AdvancedGUI* app) {
    ValueMutex state_mutex;
    bool result = init_mutex(&state_mutex, app, sizeof(AdvancedGUI));
    if(!result) {
        FURI_LOG_E("advanced_gui_app_alloc", "cannot create mutex\r\n");
        free(app);
        return -1;
    }

    configure_submenu(app);
    configure_text_input_box(app, &state_mutex);
    configure_view_dispatcher(app, &state_mutex);
    configure_widget(app, &state_mutex);

    // I need to call view_dispatcher_run() to launch the GUI
    // see structures.h for more information about the struct used in this example
    view_dispatcher_run(app->view_dispatcher);

    furi_record_close(RECORD_GUI);
    delete_mutex(&state_mutex);
    advanced_gui_app_free(app);
}

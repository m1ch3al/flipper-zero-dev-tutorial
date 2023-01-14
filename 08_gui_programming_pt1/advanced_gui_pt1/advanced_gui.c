
/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x08 - Advanced GUI (pt.1) 
 * 
 * An example using multiple view and exit dialog menu  
 * 
 *****************************************************************
 */

#include "advanced_gui.h"

void submenu_callback(void* context, uint32_t index) {
    furi_assert(context);
    AdvancedGUI* app = context;
    if(index == SubmenuIndexPerson) {
        app->view_id = ViewPerson;
        view_dispatcher_switch_to_view(app->view_dispatcher, ViewPerson);
    }
    if(index == SubmenuIndexCar) {
        app->view_id = ViewCar;
        view_dispatcher_switch_to_view(app->view_dispatcher, ViewCar);
    }
}

uint32_t application_exit(void* context) {
    UNUSED(context);
    return VIEW_NONE;
}

uint32_t exit_confirm_view(void* context) {
    UNUSED(context);
    return ViewExitConfirm;
}

void app_dialog_callback(DialogExResult result, void* context) {
    furi_assert(context);
    AdvancedGUI* app = context;
    if(result == DialogExResultLeft) {
        view_dispatcher_stop(app->view_dispatcher);
    } else if(result == DialogExResultRight) {
        view_dispatcher_switch_to_view(app->view_dispatcher, app->view_id);
        // Show last view
    } else if(result == DialogExResultCenter) {
        view_dispatcher_switch_to_view(app->view_dispatcher, ViewSubmenu);
    }
}

void advanced_gui_app_free(AdvancedGUI* app) {
    furi_assert(app);

    // Free views
    view_dispatcher_remove_view(app->view_dispatcher, 0);
    submenu_free(app->submenu);
    view_dispatcher_free(app->view_dispatcher);

    // Close gui record
    furi_record_close(RECORD_GUI);
    app->gui = NULL;

    // Free rest
    free(app);
}

AdvancedGUI* advanced_gui_app_alloc() {
    AdvancedGUI* app = malloc(sizeof(AdvancedGUI));
    // Gui
    app->gui = furi_record_open(RECORD_GUI);
    // View dispatcher
    app->view_dispatcher = view_dispatcher_alloc();

    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);

    // views
    app->submenu = submenu_alloc();
    submenu_add_item(app->submenu, "Item 1 - Person", SubmenuIndexPerson, submenu_callback, app);
    submenu_add_item(
        app->submenu, "Item 2 - only 4 demo", SubmenuIndexPerson, submenu_callback, app);
    submenu_add_item(
        app->submenu, "Item 3 - only 4 demo", SubmenuIndexPerson, submenu_callback, app);
    submenu_add_item(
        app->submenu, "Item 4 - only 4 demo", SubmenuIndexPerson, submenu_callback, app);
    submenu_add_item(app->submenu, "Item 5 - car", SubmenuIndexCar, submenu_callback, app);

    view_set_previous_callback(submenu_get_view(app->submenu), application_exit);
    view_dispatcher_add_view(app->view_dispatcher, ViewSubmenu, submenu_get_view(app->submenu));

    // Dialog view
    app->dialog = dialog_ex_alloc();
    dialog_ex_set_result_callback(app->dialog, app_dialog_callback);
    dialog_ex_set_context(app->dialog, app);
    dialog_ex_set_left_button_text(app->dialog, "Exit");
    dialog_ex_set_right_button_text(app->dialog, "Stay");
    dialog_ex_set_center_button_text(app->dialog, "Menu List");
    dialog_ex_set_header(app->dialog, "Close Current App?", 16, 12, AlignLeft, AlignTop);
    view_dispatcher_add_view(
        app->view_dispatcher, ViewExitConfirm, dialog_ex_get_view(app->dialog));

    app->personGui = view_person_alloc();
    view_set_previous_callback(view_person_get_view(app->personGui), exit_confirm_view);
    // Associate view_id  with Person*
    view_dispatcher_add_view(
        app->view_dispatcher, ViewPerson, view_person_get_view(app->personGui));

    app->carGui = view_car_alloc();
    view_set_previous_callback(view_car_get_view(app->carGui), exit_confirm_view);
    view_dispatcher_add_view(app->view_dispatcher, ViewCar, view_car_get_view(app->carGui));

    // Switch to menu
    app->view_id = ViewSubmenu;
    view_dispatcher_switch_to_view(app->view_dispatcher, app->view_id);

    return app;
}
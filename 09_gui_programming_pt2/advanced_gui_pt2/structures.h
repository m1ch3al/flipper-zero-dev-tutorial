
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

#pragma once

#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_input.h>
#include <gui/modules/text_box.h>
#include <gui/modules/widget.h>
#include <furi.h>
#include <furi_hal.h>

// Max string size
#define TEXT_BUFFER_SIZE 256

// AdvancedGUI struct
typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    uint32_t view_id;

    // Submenu item for make the choice
    Submenu* submenu;

    // A full virtual keyboard and a small textbox for
    // write inside what we want !
    TextInput* text_input;
    // A simple TextBox for display the data that we
    // have inserted before.
    TextBox* text_box;

    // The container for the personalized buttons
    Widget* widget;
    char input[TEXT_BUFFER_SIZE];
    char output[(TEXT_BUFFER_SIZE * 26) + (26)];
} AdvancedGUI;

// ViewID associated to the View(s)
typedef enum {
    ViewSubmenuExample,
    ViewTextInputBoxExample,
    ViewTextBoxExample,
    ViewWidgetButtonsExample,
} ViewID;

// Submenu index for making the first choice
// when the FAP will start
typedef enum {
    SubMenuTextInput,
    SubMenuButton,
} SubMenuItem;

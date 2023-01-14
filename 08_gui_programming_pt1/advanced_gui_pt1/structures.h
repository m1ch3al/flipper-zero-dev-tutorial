
/*****************************************************************
 * Flip.x0 Tutorial
 *                                                     by M1ch3al
 * 0x08 - Advanced GUI (pt.1) 
 * 
 * An example using multiple view and exit dialog menu  
 * 
 *****************************************************************
 */

#pragma once

#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>
#include <gui/view.h>

// Max string size
#define BUFFER_SIZE 20

// AdvancedGUI struct
typedef struct {
    // gui object for the menu list
    Gui* gui;
    // view dispatcher for jump to other viewws
    ViewDispatcher* view_dispatcher;
    // A submenu component to see a list of item on the Flip.x0 screen
    Submenu* submenu;
    // this component is used for show the dialog that asking if you
    // want to stay or leave the application
    DialogEx* dialog;
    // The current ID of the GUI
    uint32_t view_id;
    // Reference to a Person struct
    Person* personGui;
    // reference to a Car struct
    Car* carGui;
} AdvancedGUI;

// A simple struct with a View*, showing name, surname and age of a Person
typedef struct {
    char name[BUFFER_SIZE];
    char surname[BUFFER_SIZE];
    int age;
    View* view;
} Person;

// A simple struct with a View*, showing some car information
typedef struct {
    char carType[BUFFER_SIZE];
    char carModel[BUFFER_SIZE];
    char carColor[BUFFER_SIZE];
    View* view;
} Car;

// Index of enum for the menu Items
typedef enum {
    SubmenuIndexPerson,
    SubmenuIndexCar,
} SubmenuIndex;

// ViewID associated to the View(s)
typedef enum {
    ViewSubmenu,
    ViewPerson,
    ViewCar,
    ViewExitConfirm,
} ViewID;

// A view Model for manage/store keypad events
typedef struct {
    bool ok_pressed;
    bool back_pressed;
} PersonalizedViewModel;
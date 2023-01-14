
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

#include "../structures.h"
#include <gui/view.h>

Person* view_person_alloc();

void view_person_free(Person* person);

View* view_person_get_view(Person* person);

void process_person_data_for_the_view(Person* person, InputEvent* event);

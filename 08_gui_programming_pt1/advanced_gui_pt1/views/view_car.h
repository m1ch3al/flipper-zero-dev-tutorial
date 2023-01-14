
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

Car* view_car_alloc();

void view_car_free(Car* car);

View* view_car_get_view(Car* car);

void process_car_data_for_the_view(Car* car, InputEvent* event);

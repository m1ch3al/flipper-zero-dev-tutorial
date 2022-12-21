#!/usr/bin/python3

import os

FAP_FOLDER = 'applications_user'


def main():
    os.system('clear')
    print_title()
    stop = False
    print('Insert the name of the application you want to create (max 20 chars):')
    user_data = input()
    application_name = None
    if 0 < len(user_data) <= 20:
        application_name = user_data.lower()
        print('To meet standards, the FAP name will be lower-case : {}'.format(application_name))
    else:
        print('the name is not valid, please insert a valid FAP name')
        return -1
    if application_name is not None:
        print('Please, specify the folder of the FlipperZero firmware:')
        user_data = input()
        print('The specified folder [{}] is correct ? (Y/N)'.format(user_data))
        correctness = input()
        if 'y' in correctness.lower():
            firmware_folder = user_data
            complete_application_filepath = os.path.join(firmware_folder, FAP_FOLDER, application_name)
            print('The FAP skeleton will be created here : {}'.format(complete_application_filepath))
            create_folders(complete_application_filepath)
            create_application_fam(complete_application_filepath, application_name)
            create_readme(complete_application_filepath)
            create_main_entry(complete_application_filepath, application_name)


def create_folders(complete_application_filepath):
    print('creating the required folder(s).......')
    os.mkdir(complete_application_filepath)
    os.mkdir(os.path.join(complete_application_filepath, "images"))
    print('done')


def create_application_fam(complete_application_filepath, application_name):
    application_fam = os.path.join(complete_application_filepath, 'application.fam')
    fd = open(application_fam, 'w')
    fd.write('App(\n')
    fd.write('  appid="{}",\n'.format(application_name))
    fd.write('  # this field will be showed on the Flip.x0 FAP browser\n'.format(application_name))
    fd.write('  name="{}",\n'.format(application_name))
    fd.write('  apptype=FlipperAppType.EXTERNAL,\n')
    fd.write('  entry_point="main_fap",\n'.format(application_name))
    fd.write('  stack_size=1 * 1024,\n')
    fd.write('  # Where the application will be stored into the Flip.x0\n')
    fd.write('  fap_category="dev_apps",\n')
    fd.write('  # This is needed if I have some images\n')
    fd.write('  fap_icon_assets="images",\n')
    fd.write(')\n')
    fd.close()


def create_main_entry(complete_application_filepath, application_name):
    main_entry = os.path.join(complete_application_filepath, '{}.c'.format(application_name))
    fd = open(main_entry, 'w')
    fd.write("#include <stdio.h>\n")
    fd.write("#include <furi.h>\n")
    fd.write("#include <gui/gui.h>\n")
    fd.write("#include <input/input.h>\n")
    fd.write("#include <notification/notification_messages.h>\n\n")

    fd.write('static void app_draw_callback(Canvas* canvas, void* ctx) {\n')
    fd.write('    UNUSED(ctx);\n')
    fd.write('    canvas_clear(canvas);\n')
    fd.write('    //TODO - insert your canvas_* instruction\n')

    fd.write('    // Optional - some log from serial\n')
    fd.write('    FURI_LOG_D("app_draw_callback", "GUI draw");\n')
    fd.write('}\n\n')

    fd.write('static void app_input_callback(InputEvent* input_event, void* ctx) {\n')
    fd.write('    furi_assert(ctx);\n')
    fd.write('    FuriMessageQueue* event_queue = ctx;\n')
    fd.write('    furi_message_queue_put(event_queue, input_event, FuriWaitForever);\n')
    fd.write('}\n\n')

    fd.write('int32_t main_fap(void* p) {\n')
    fd.write('    UNUSED(p);\n')
    fd.write('    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));\n\n')

    fd.write('    // Configure viewport\n')
    fd.write('    ViewPort* view_port = view_port_alloc();\n')
    fd.write('    view_port_draw_callback_set(view_port, app_draw_callback, view_port);\n')
    fd.write('    view_port_input_callback_set(view_port, app_input_callback, event_queue);\n\n')

    fd.write('    // Register viewport in GUI\n')
    fd.write('    Gui* gui = furi_record_open(RECORD_GUI);\n')
    fd.write('    gui_add_view_port(gui, view_port, GuiLayerFullscreen);\n')
    fd.write('    InputEvent event;\n\n')
    fd.write('    // TODO - Continue here...\n\n')
    fd.write('    return 0;')
    fd.write('}\n')
    fd.close()




def create_readme(complete_application_filepath):
    fd = open(os.path.join(complete_application_filepath, 'README.md'), 'w')
    fd.write("")
    fd.close()


def print_title():
    print("  _____ _ _                      _____              ")
    print(" |  ___| (_)_ __  _ __   ___ _ _|__  /___ _ __ ___  ")
    print(" | |_  | | | '_ \| '_ \ / _ \ '__|/ // _ \ '__/ _ \ ")
    print(" |  _| | | | |_) | |_) |  __/ |  / /|  __/ | | (_) |")
    print(" |_|   |_|_| .__/| .__/ \___|_| /____\___|_|  \___/ ")
    print("           |_|   |_|                                ")
    print("                               Dev App initializer  ")
    print("                                        by M1ch3al  \n")


if __name__ == '__main__':
    main()

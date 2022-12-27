

## Flipper Zero dev tutorial with examples.
A fun journey to discover Flipper Zero and how FAP (Flipper-zero APplication) are developed.
![title](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/title.png?raw=true)
> VERY IMPORTANT:
> Most likely I will write some bullshit: feel free to clone my repository, try, change and why not, improve my code.

> ## As a developer I am used to working with Linux and this tutorial was written using ubuntu 20.04.5 LTS. I do not tried on Microsoft Windows.

FlipperZero uses a particular structure for build its application called **SCons** (more information can be found here: https://scons.org): this ambitious project is a substitute of the classic Make and the configurations files are Python scripts for use the power of a real programming language to solve build problems. 

>   NOTE: for those whom is interested learning more about SCons, I advise to NOT continue. This tutorial helps you how to create applications for your FlipperZero, not about compilation and/or internal FreeRTOS information.


# Simple FAP structure.
A FAP (Flipperzero APplication) has a particular filesystem structure like this:

    [FAP-name]
        ├── application.fam (type: text file, compulsory)
        ├── icon.png (type: image, optional)
        ├── README.md (type: text file, optional)
        │
        ├── [images] (type: folder, optional)
        │      └── {all the images required by the FAP}
        │
        ├── main.c (type: text file, optional)
        └── {others .c/.h files used by the FAP}

Let's analyze all the part of the FAP:

## application.fam
This one of the most important file, if you want to create a FAP.
For example, if you are familiar with Java/Kotlin (especially for Android OS) probably you'll remember *AndroidManifest.xml*: the concept is the same.
If you don't what is a manifest, don't worry: this is a simple text (ascii) file with a list of "declarations" required to run the FAP correctly.
Within **application.fam** it's possible to find all the information regarding the behavior of the FAP: you can specify the resources that the FAP will use (like images), which kind of application will be (a plugin or external), the entry point of the FAP, the **appid**, the category and so on. Most of them will be will be analyzed individually, allowing you to implement the functionality of all the statements.

## icon.png
When you turned on your Flip.x0, probably you saw a many FAP in the various menu of the system.
Every FAP has a name and an icon: that's means you can personalize your app as you want.
![flipper_icons](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/flipper_icons.png?raw=true)


Just for convenience, in this tutorial, I will use the name **icon.png** for the small FAP icons we'll created together, but feel free to change the name of the file and obliviously inside the application.fam (we will also see this later).
Remember that the declaration of an icon for a FAP, is not necessary: when you'll compile your application, the icon will be not showed in the list and you will see only the name with a blank space on the left.  

## README (.md)
I don't want to dwell too much on this part: everybody knows (probably if you're a developer) the importance of a README file especially if you want to distribute your FAP using the most common channels like GitHub or other site like it.

## images (folder)
if your FAP need to display some images, that it's a good reason for keep all the resources organized inside a folder. In the same way, feel free to change the name of this folder as you prefer, but remember to change the name in the application.fam.

 ## main.c
 Somewhere, the main function will be defined, right?
 During the compilation phase, the SCons system will check the content of all the .c files inside your FAP folder and it will recognize the name of the main function (declared inside the application.fam).
So...it's better to keep the code organized: it doesn't matter the names of the .c files inside you FAP application: the important thing (for your convenience) is to have a .c file with an easily recognizable name that allow you to understand where is the main entry of the application.
If you know the C language, probably you well understood who am I referring to:

    int main(int argc,  char  *argv[])  {
        // Do something here...
        return 0;  
    }
For the Flipper Zero Application, we need the same thing.
Keep calm: we will see later in details.

# Content of application.fam
This is an example of how the manifest of your Flip.x0 application is made.  
Let's take for example **my_first_app** (inside *01_my_very_first_fap/my_first_app/* folder of this repository)
You will find only two files: 
- my_first_app.c
- application.fam
The content of the application.fam is the following:

        App(
	        appid="my_first_app",
	        name="My First App",
	        apptype=FlipperAppType.EXTERNAL,
	        entry_point="my_first_app_main",
	        stack_size=1 * 1024,
	        fap_category="Examples",
	        
	        # Added for explanation
	        fap_icon="icon.png",
	        fap_icon_assets="images",
	    )    
Let's analyze now all the declaration of the fam.
## appid
This instruction helps your Flip.x0 the identify your FAP inside all the ecosystem.
The **appid** has to be unique, otherwise during compilation phase, the compiler **(fbt)** will throw an error.
My suggestion is to choose a name that could be understand easily.

## name
 This field represents the string that will be displayed on your Flip.x0 when you'll use the browser, as shown in the image below.
 
 
![flipper_icons](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/fam_name.png?raw=true)


## apptype
This directive specified which kind of FAP you want to create.
At the moment, the documentation is very poor and I only found four types of **apptype**:
 - FlipperAppType.PLUGIN
 - FlipperAppType.EXTERNAL
 - FlipperAppType.SETTINGS
 - FlipperAppType.METAPACKAGE
 
  **PLUGIN** is used if you want to create FAP as *plugin* to interact with of Flip.x0. 
 The plugins are compiled into the kernel and will be flashed as part of the firmware in the main SoC, furthermore writing plugins require the developer to edit/maintain `/applications/meta/applications.fam`
 
  **EXTERNAL** is used (as in this case) for delopy FAP 
 The compiled FAP are separated programs and you can store the build version (.fap file) inside your Flip.x0 microSD.

**SETTINGS**
I'm not an expert but I can suppose that if you want to develop FAP using Settings app-type, probably you want to have integration with the FreeRTOS inside your Flip.x0 

** METAPACKAGE **
Sincerely I don't understand well what represents this kind of option: when the documentation will be availabe, I'll satisfy my curiosity.

## entry_point
Is the main function of your FAP. Like in C with the **main** function, here you can have a different naming option, but the concept is the same.
In this example I have this portion of code:

    int32_t my_first_app_main(void* p) {
        UNUSED(p);
    }
As you can see above,  this kind of function is equivalent to this one:

    int main(int argc,  char  *argv[])  {
        // Do something here...
        return 0;  
    }
when you write in pure C (for Unix/Linux like).

## stack_size
I don't think there is much need to explain this statement: you can specify the size of the stack inside your FAP :P

## fap_icon
Use this declaration if you want to give to your FAP a bit of elegance.
In this case, we have an "icon.png" as a FAP icon.
The important information you need to know are:
 - the size of the icon: 10 pixel x 10 pixel 
 - the colors palette: only white (for the background) and black are allowed

## fap_icon_assets
This directive specify a folder name and basically, tells to your Flip.x0 where load the images to draw into the GUI.
If you use this declaration, make sure to have the folder created before compiling the FAB, otherwise the compilation phase will fail.

# How to build a FAP.
Let's use as example the first application in this tutorial.
First of all, open a terminal ad move yourself into your favorite folder for the development.
Use git to clone the official repository of Flip.x0 firmware or use a custom firmware like RogueMaster, as I did. 
If you want to use the official firmware repository you need launch this command: 

    git clone https://github.com/flipperdevices/flipperzero-firmware.git

Otherwise (like me) this is the RogueMaster firmware:

    git clone https://github.com/RogueMaster/flipperzero-firmware-wPlugins.git

once the repository is cloned, enter inside the firmware folder and explore what is inside:

    drwxrwxr-x 19 user user    4096 dic 22 13:35 .
    drwxrwxr-x 14 user user    4096 dic 23 12:49 ..
    drwxrwxr-x  9 user user    4096 dic 18 14:09 applications
    drwxrwxr-x  5 user user    4096 dic 21 21:09 applications_user
    drwxrwxr-x  8 user user    4096 dic 18 14:09 assets
    drwxrwxr-x  2 user user    4096 dic 18 14:09 brew-cask
    -rw-rw-r--  1 user user     134 dic 18 14:09 Brewfile
    drwxrwxr-x  4 user user    4096 dic 21 21:56 build
    -rwxrwxr-x  1 user user     643 dic 20 09:48 buildRelease.sh
    -rw-rw-r--  1 user user    3419 dic 20 09:48 CHANGELOG.md
    -rw-rw-r--  1 user user    5358 dic 18 14:09 .clang-format
    -rw-rw-r--  1 user user    5226 dic 18 14:09 CODE_OF_CONDUCT.md
    -rw-rw-r--  1 user user    2874 dic 18 14:09 CODING_STYLE.md
    -rwxrwxr-x  1 user user      92 dic 21 21:55 compile.sh
    -rw-rw-r--  1 user user    4764 dic 18 14:09 CONTRIBUTING.md
    drwxrwxr-x  4 user user    4096 dic 18 14:09 debug
    drwxrwxr-x  3 user user    4096 dic 21 21:56 dist
    drwxrwxr-x  3 user user    4096 dic 20 09:48 documentation
    -rw-rw-r--  1 user user    9486 dic 18 14:09 .drone.yml
    -rw-rw-r--  1 user user     173 dic 18 14:09 .editorconfig
    -rwxrwxr-x  1 user user     727 dic 18 14:09 fbt
    -rw-rw-r--  1 user user     388 dic 18 14:09 fbt.cmd
    -rw-rw-r--  1 user user    2271 dic 18 14:09 fbt_options.py
    drwxrwxr-x  3 user user    4096 dic 18 14:09 firmware
    -rw-rw-r--  1 user user    8047 dic 18 14:09 firmware.scons
    drwxrwxr-x  3 user user    4096 dic 18 14:09 furi
    -rw-rw-r--  1 user user     605 dic 18 14:09 GAMES_ONLY.md
    drwxrwxr-x  9 user user    4096 dic 22 13:35 .git
    -rw-rw-r--  1 user user      64 dic 18 14:09 .gitattributes
    drwxrwxr-x  3 user user    4096 dic 18 14:09 .github
    -rw-rw-r--  1 user user     624 dic 22 13:35 .gitignore
    -rw-rw-r--  1 user user    1198 dic 18 14:09 .gitmodules
    drwxrwxr-x 34 user user    4096 dic 18 14:09 lib
    -rw-rw-r--  1 user user   35149 dic 18 14:09 LICENSE
    -rw-rw-r--  1 user user    3393 dic 18 14:09 MACOS_GUIDE.md
    -rw-rw-r--  1 user user    1259 dic 18 14:09 Makefile
    -rw-rw-r--  1 user user   54919 dic 20 09:48 patreon.png
    -rw-rw-r--  1 user user     575 dic 18 14:09 .pvsconfig
    -rw-rw-r--  1 user user     279 dic 18 14:09 .pvsoptions
    -rw-rw-r--  1 user user   31567 dic 22 13:35 ReadMe.md
    -rw-rw-r--  1 user user    3986 dic 18 14:09 RoadMap.md
    -rw-rw-r--  1 user user 9881732 dic 22 09:50 .sconsign.dblite
    -rw-rw-r--  1 user user    8326 dic 18 14:09 SConstruct
    drwxrwxr-x  9 user user    4096 dic 18 14:55 scripts
    drwxrwxr-x  3 user user    4096 dic 18 14:09 site_scons
    -rw-rw-r--  1 user user    1080 dic 20 09:48 SUPPORT.md
    -rw-rw-r--  1 user user   10760 dic 18 14:09 test_iso7816_helpers.c
    -rw-rw-r--  1 user user   20665 dic 18 14:09 test_mrtd_helpers.c
    drwxrwxr-x  3 user user    4096 dic 18 14:11 toolchain
    drwxrwxr-x  3 user user    4096 dic 18 14:13 .vscode

it will be possible to notice an executable file inside the firmware folder called **fbt** *that is the core of our entertainment*.
For more information about **fbt** please use the following link: [https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/fbt.md](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/fbt.md)
As you can read from the documentation, **fbt** stands for ***F**lipper **B**uild **T**ool* and it's the entry point for firmware-related commands and utilities. It is invoked by `./fbt` in the firmware project root directory. Internally, it is a wrapper around the [SCons](https://scons.org/) build system.

### Visual Studio Code integration (optional)
Personally, for the development of the IoT firmware, I am very happy with Visual Studio Code, but you can use what you prefer.
`fbt`  includes basic development environment configuration for VSCode. 
To deploy it, run  `./fbt vscode_dist` from the folder of the Flip.x0 firmware. 
That will copy initial environment configuration to  `.vscode`  folder. After that, you can use that configuration by starting VSCode and choosing firmware root folder in "File > Open Folder" menu.

-   On first start, you'll be prompted to install recommended plug-ins. Please install them for best development experience.  _You can find a list of them in  `.vscode/extensions.json`._
-   Basic build tasks are invoked in Ctrl+Shift+B menu.
-   Debugging requires a supported probe. That includes:
    -   Wi-Fi devboard with stock firmware (blackmagic),
    -   ST-Link and compatible devices,
    -   J-Link for flashing and debugging (in VSCode only).  _Note that J-Link tools are not included with our toolchain and you have to  [download](https://www.segger.com/downloads/jlink/)  them yourself and put on your system's PATH._
-   Without a supported probe, you can install firmware on Flipper using USB installation method.

## Prepare the environment and compile our first FAP :)
Finally it's time to fill out our first application: for this part of the tutorial, I will use **[my_first_app](https://github.com/m1ch3al/flipper-zero-dev-tutorial/tree/main/01_My_very_first_FAP/my_first_app)** as a reference code.
Navigate into the folder tree of the Flip.x0 firmware and enter inside `application_user` folder.
Copy the folder **[my_first_app](https://github.com/m1ch3al/flipper-zero-dev-tutorial/tree/main/01_My_very_first_FAP/my_first_app)** inside the `application_user` folder.
The content should be something like this:
```bash
user@yourpc:flipperzero-firmware-wPlugins/applications_user$ tree 
.
├── my_first_app
│   ├── application.fam
│   └── my_first_app.c
└── README.md

1 directory, 3 files
user@yourpc:flipperzero-firmware-wPlugins/applications_user$ 
```
Now return to the root of Flip.x0 firmware with a `cd ..` command and prepare yourself for the compilation phase. On the terminal type:

    ./fbt fap_my_first_app
  and wait for the magic.
  When you create a FAP and you want to compile that application, you need to run the compiler with a prefix before the name of your app: in this case, the name of the FAP is **my_first_app* (that is also the name of the folder...) the word `fap_` before the name identifies and tells to the SCons to compile THAT application.
  Every kind of application must be compiled with a `fap_` as prefix before its name.
  
> A small example.
> Suppose to have an amazing FAP to compile and its name is **awesome_program** (as the name of the folder in which it is contained) the command for the compilation will be the following:

    ./fbt fap_awesome_program

But, now let's go back to the previous stage and see what happened to the FAP compilation.

    2022-12-24 16:44:41,216 [INFO] Packing
    	LINK	build/f7-firmware-C/.extapps/my_first_app_d.elf
    2022-12-24 16:44:41,291 [INFO] Complete
    2022-12-24 16:44:41,305 [INFO] Complete
    	PBVER	build/f7-firmware-C/assets/compiled/protobuf_version.h
    	PREGEN	build/f7-firmware-C/sdk_origin.i
    	SDKSRC	build/f7-firmware-C/sdk_origin.i
    	SDKCHK	firmware/targets/f7/api_symbols.csv
    API version 11.3 is up to date
    	APPMETA	build/f7-firmware-C/.extapps/my_first_app.fap
    	FAP	build/f7-firmware-C/.extapps/my_first_app.fap
    	APPCHK	build/f7-firmware-C/.extapps/my_first_app.fap
    	
Close to the end of our compilation output, we can clearly notice that we successfully created our FAP binary: your first FAP is waiting for you in this folder !

    build/f7-firmware-C/.extapps/my_first_app.fap

At this point we can deploy our application in two different ways: let's see how we can proceed.

## Deploy FAP inside your Flip.x0
For deploy our FAP into our Flip.x0, we can proceed in two ways:
 1. Launch the application using the `./fbt` command
 2. Copy the compiled FAP inside our Flip.x0 

**1) Using the Flipper Build Tool**

Connect your Flip.x0 to your computer using the USB-Type C cable (the device will be powered on automatically).
Make sure that the serial device associated to your Flip.x0 is not used by any program. 
**Close any instance** of qFlipper application or other kind of software that can perform some serial communication with your Flip.x0 like minicom or miniterm.
When you're ready, on the terminal type the following command:

    ./fbt launch_app APPSRC=my_first_app
    
After some time the Flipper Build Tool will call a script called `runfap.py` and as if by magic your first FAP will appear on your Flip.x0 !

 ![flipper_icons](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/my_first_app.png?raw=true)
 
 You can exit from the application by pressing the back button.
  ![my_first_fap_in_action](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/first_app.gif?raw=true)

  
**2) Copy the .fap file inside your Flip.x0 and run the application manually**
Locate your .fap binary reading the output of the compilation phase, in my case the file was created into this folder and the full path is :

    [your_working_folder]/flipperzero-firmware/build/f7-firmware-C/.extapps/my_first_app.fap

Launch the qFlipper application, select the file-manager and drag 'n' drop the file into the folder `Examples` (just for keep all the stuff organized) like in the image below.
![my_first_fap_in_action](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/copy_fap.png?raw=true)

  
Once you complete the drag n' drop operation, you can find your FAP in the list of applications and it will be accessible by pressing the center button (OK) and navigate through Applications &rarr; Examples &rarr; My First App

![my_first_fap_in_action](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/explore_first_app.gif?raw=true)

## And now, what can I do?
Learning, for sure :) 
Now you know how to compile and deploy FAP inside your Flip.x0: all you have to do is learn to develop with the examples that I will add into this repository.

> The code will be strong commented to allow you to better understand all the API calls to FreeRTOS and Furi

### And here, a small gift for you: https://ilin.pt/stuff/fui-editor/
**It's a web-base application for build Flip.x0 GUI very easily.**

|N.|Example name|Small description|
|--|--|--|
|01|My First App|The simplest possible FAP using GUI|
|02|Keypad and GUI timer|A simple FAP showing how to interact wit the Flip.x0 buttons and timer|
|03|Notifications|A simple FAP using notification (blinking LED and vibration)|
|04| TO DO | |

 

## Flipper Zero dev tutorial with examples.
A fun journey to discover Flipper Zero and how FAP (Flipper-zero APplication) are developed.
![title](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/title.png?raw=true)
> VERY IMPORTANT:
> Most likely I will write some bullshit: feel free to clone my repository, try, change and why not, improve my code.

FlipperZero uses a particular structure for build its application called **SCons** (more information can be found here: https://scons.org)

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
This one of the most important file if you want to create a FAP.
For example, if you are familiar with Java/Kotlin (especially for Android OS) probably you'll remember *AndroidManifest.xml*: the concept is the same.
If you don't what is a manifest, don't worry: this is a simple text (ascii) file with a list of "declarations" required to run the FAP correctly.
Within **application.fam** it's possible to find all the information regarding the behavior of the FAP: you can specify the resources that the FAP will use (like images), which kind of application will be (a plugin or external), the entry point of the FAP, the **appid**, the category and so on. Most of them will be will be analyzed individually, allowing you to implement the functionality of all the statements.

## icon.png
When you powered on your Flip.x0, probably you saw a many FAP in the various menu of the system.
Every FAP has a name and an icon: that's meaning you can personalize  your app as you want.
![flipper_icons](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/flipper_icons.png?raw=true)
Just for convenience, in this tutorial, I will use the name **icon.png** for the small FAP icons we'll created together, but feel free to change the name of the file and obliviously inside the application.fam (we will also see this later).
Remember that the declaration of an icon for a FAP, is not necessary: when you'll compile your application, the icon will be not showed in the list and you will see only the name with a blank space on the left.  

## README (.md)
I don't want to dwell too much on this part: everybody knows (probably if you develop software) the importance of a README file especially if you want to distribute your FAP using the most common channels like GitHub or other kind of online repository management system.

## images (folder)
if you FAP need to display some images, that it's a good reason for keep all the resources organized inside a folder. In the same way, feel free to change the name of this folder as you prefer, but remember to change the name in the application.fam.

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
	    )    
Let's analyze now all the declaration of the fam.
## appid
This instruction helps your Flip.x0 the identify your FAP inside all the ecosystem.
The **appid** has to be unique, otherwise during compilation phase, the compiler **(fbt)** will throw an error.
  
 
 



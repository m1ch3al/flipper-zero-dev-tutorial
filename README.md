## Flipper Zero dev tutorial with examples.
A fun journey to discover Flipper Zero and how FAP (Flipper-zero APplication) are developed.

> VERY IMPORTANT:
> Most likely I will write some bullshit: feel free to clone my repository, try, change and why not, improve my code.

FlipperZero uses a particular structure for build its application called **SCons** (more information can be found here: https://scons.org)

>   NOTE: for those whom is interested learning more about SCons, I advise to NOT continue. This tutorial helps you how to create applications for your FlipperZero, not about compilation and/or internal FreeRTOS information.

## Simple FAP structure.
A FAP (Flipperzero APplication) has a particular filesystem structure like this:

    [FAP-name]
        ├── application.fam (type: text file, compulsory)
        ├── icon.png (type: image, optional)
        ├── README.md (type: text file, optional)
        │
        ├── [images] (type: folder, optional)
        │      └── {all the images required by the FAP}
        │
        ├── FAP-name.c (type: text file, optional)
        └── {others .c/.h files used by the FAP}

Let's analyze all the part of the FAP:

# application.fam
This one of the most important file if you want to create a FAP.
For example, if you are familiar with Java/Kotlin (especially for Android OS) probably you'll remember *AndroidManifest.xml*: the concept is the same.
If you don't what is a manifest, don't worry: this is a simple text (ascii) file with a list of "declarations" required to run the FAP correctly.
Within **application.fam** it's possible to find all the information regarding the behavior of the FAP: you can specify the resources that the FAP will use (like images), which kind of application will be (a plugin or external), the entry point of the FAP, the **appid**, the category and so on. Most of them will be will be analyzed individually, allowing you to implement the functionality of all the statements.

# icon.png
![flipper_icons](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/images/flipper_icons.png) 

 



https://ilin.pt/stuff/fui-editor/


 

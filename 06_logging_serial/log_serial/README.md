# Logging Serial Example.
**This small piece of code will show you how to insert active logging message inside your FAP.**

> **{ VERY IMPORTANT }**
>
> Why a readme here ?
>
> I know that you want to write and test your code, but I suggest to take 2 mins of your time for reading this small document to obtain the better understanding of the content.

## Step n.1
### Compile and deploy the .fap
Compile the code to create the binary and drag'n'drop the `logging_example.fap` inside your Flip.x0 using the qFlipper application or use the command line `./fbt launch_app APPSRC=logging_example`.
The FAP on your Flip.x0 will be like this:
 
![splash](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/06_logging_serial/log_serial/images/splash.png?raw=true)

Wait a few moment, please do not press the OK because we need to finish some configurations.

## Step n.2
### Enable log level and Debug inside you Flip.x0.
In order to see the log message from your Flip.x0 through the ACM serial interface, you need to change some settings.

On the initial splash-screen, press the OK (center) button and navigate to **Settings** -> **System** and enable the **Debug** option, setting the option to **ON**.

After that, choos the **Log Level**: for this code example, select **Debug** because it's the lowest level I used for the tutorial.    
![enable_debug](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/06_logging_serial/log_serial/images/enale_debug.gif?raw=true)


## Step n.3
### Check log messages on FlipperCLI.
Close every programs that can use the serial communication with your Flip.x0 (like qFlipper or the execution of the `fbt` command).
Connect to your Flip.x0 to your PC by an USB-C data cable and open a TTY-terminal (like PuTTY, minicom, miniterm - any serial terminal/reader is fine for this purpose).
Connect to your Flip.x0 using your preferred software (in my case, I used miniterm)
Remember that the **BAUDRATE of the Flip.x0 is 9600**.
Usually, for the Linux systems, the Flip.x0 is recognized as an **ACM** serial port (that's meaning that the connected device use an _abstract control model_ for manage itself) so, you will find your device as `/dev/ttyACM0` or `/dev/ttyACM1` (the last one like in my case).
Once connected, you can see a welcome ASCII dolphin from the Flip.x0 like showed in the figure below.

![title](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/06_logging_serial/log_serial/images/flipper_cli.png?raw=true)  
 
 To enable the LOG on the console, type `log` followed by enter.
 
 ## Step 4
 ### Launch the application and check out the debug messages.
 After few moments, the Flipper-CLI will start to display the messages that we need !!
 Checkout the image below !
 
![title](https://github.com/m1ch3al/flipper-zero-dev-tutorial/blob/main/06_logging_serial/log_serial/images/log_messages.png?raw=true)
 
 

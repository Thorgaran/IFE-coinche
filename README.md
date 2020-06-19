# IFE-coinche

This is a project for our first-year C class. The "Coinche" is a French card game with overly complicated rules.  
For more informations, the project report can be found [here](https://github.com/Thorgaran/IFE-coinche/blob/master/docs/Project_report.pdf).

# Building

## Windows

Make sure to have gcc installed.  
Because of Unicode issues, if you compile through MinGW, the display will break, so we recommend compiling it through [Cygwin](https://www.cygwin.com/).  
Run `make coinche.exe clean` in the project directory.  
This will create a coinche.exe file.  

## Linux

Compiling this project on linux hasn't been tested, but it will *probably* work.  
Feel free to try it out.  

# Running

You can either compile the project yourself following the steps above, or you can get the latest release [here](https://github.com/Thorgaran/IFE-coinche/releases/latest).  
Because this project was compiled with Cygwin, the cygwin1.dll file provided is needed to launch the executable.  

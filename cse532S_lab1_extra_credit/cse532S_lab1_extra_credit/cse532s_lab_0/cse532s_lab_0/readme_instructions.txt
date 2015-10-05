CSE 532 Fall 2015 Lab 0
=======================

##Team member

* Yiheng Ding  ---  dingyiheng@wustl.edu
* Ren Wan  ---  wanren@wustl.edu
* Lei Wu  ---  wu.lei@wustl.edu

##Instruction

###Unpack

Use the *cse532s_lab_0.zip* to unpack to get the all the files. Including:


    play.h
    play.cpp  ---  the play class header and source files
    Source.cpp --- the main function and fetcher function source file
    result.txt  --- the file contains result of major test

    Guidenstern.txt
    King.txt
    Queen.txt
    Rosencrantz.txt  ---  each character's script with index
    hamlet_ii_2_config.txt  --- the txt used to test the project
    hamlet_ii_2_config_2.txt  --- another txt used to test the project
    hamlet_ii_2_config_3.txt  --- another txt used to test the project
    


###Build

1. Open Visual Studio 2013 and create an empty C++ project and then import the *play.h*, *play.cpp* and *Source.cpp* to build this project.

2. And then you have two ways to run the project.

- The first way is to run the project using the executable from CMD. Launch CMD window, and type in the following command:
    

    `<.exe name> hamlet_ii_2_config.txt`


**This command take a config file as argument. Make sure you type in the correct location of the config file. If the config file is not in the same folder with the .exe, you may want to use a relative path to locate it.**

- Also you may use Visual Studio to run the project. In Visual Studio project panel, right click on the project, choose Properties --> Debugging --> Command argument --> Input, set the entry to: `hamlet_ii_2_config.txt`. Then run the project, and you can get the result.







CSE 532 Fall 2015 Lab 0 Extra Credit
====================================

##Instruction

###Unpack

In the *cse532s_lab_0_extra_credit* folder, you can see the contents of the folder like this:

    
    play.h
    play.cpp  ---  the play class header and source files
    Source.cpp --- the main function and three functions source file
    hamlet_act_ii_scene_2.txt  ---  txt used for testing

    hamlet_ii_2_config.txt  ---  the output config file
    Guidenstern.txt --- the output character scripts of the program
    King.txt
    Queen.txt
    Rosencrantz.txt 
    


###Build

1. Open Visual Studio 2013 and create an empty C++ project and then import the *play.h*, *play.cpp* and *Source.cpp* to build this project.

2. And then you have two ways to run the project.

- The first way is to run the project using the executable from CMD. Launch CMD window, and type in the following command:

    `<.exe name> hamlet_act_ii_scene_2.txt hamlet_ii_2_config.txt Hamlet Prince of Denmark ACT II Scene II A room in the Castle by William Shakespeare`

**This command take 3 arguments. The first one is a existing play script file, the second one is the output config file, the remaining line will be the description of the play. Make sure you type in the correct location of these files. If the play script file is not in the same folder with the .exe, you may want to use a relative path to locate it.**


- Also you may use Visual Studio to run the project. In Visual Studio project panel, right click on the project, choose Properties --> Debugging --> Command argument --> Input, set the entry to: `hamlet_act_ii_scene_2.txt hamlet_ii_2_config.txt Hamlet Prince of Denmark ACT II Scene II A room in the Castle by William Shakespeare`. Then run the project, and you can get the result.

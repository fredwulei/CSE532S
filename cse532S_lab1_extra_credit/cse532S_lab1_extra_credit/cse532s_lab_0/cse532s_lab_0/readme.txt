CSE 532 Fall 2015 Lab 0
=======================

##Team member

* Yiheng Ding  ---  dingyiheng@wustl.edu
* Ren Wan  ---  wanren@wustl.edu
* Lei Wu  ---  wu.lei@wustl.edu


##Overview

Lab 0 is relatively simple, I just follow the instruction provided by the website to design the whole program.
The program was designed into three major part, the play class, the main function and the fetcher function.

The play class hold the lines transfered by threads from each single characters fragment scripts. It has a complex data structure to store the characters' names ,line index and lines. and also provides input stream operator overload and lock guard to prevent race condition.

The main function does two things, the first is to read the config file and store important information and the second is to set up the each thread with its own function with variables.

The fetcher function is used to fetch lines from each single script with order synchronously. It will take the play class instance and separate ifstream to do its job.

And I also use the scope locking and thread safe interface pattern to finish this lab.


##The Wrapper Facade

The wrapper facade is mainly presented in the designing of the fetcher function, it can take a reference of a play class instance and different character's name and different ifstream. And the function will input the corresponding lines into right file.

##Insights

The one that I want to talk most is the data structure I choose to store the lines.Instead of using any useless data structure like vector, I choose map to present the lines, which is like: map<int,map<string,string>>, the first one is to store the line index and the second pair is to store the <character,line>. The biggest advantage of using such trick is the only thing I need to do is using thread to read file and input into play class instance without taking care of the sequence of lines.

So the print function of play class is very simple, just iterate through the map, the sequence is on the right track.

##Question and observation

The most tricky part I have been encountered is the badly formed line problem,I need to skip the whitespace and blank line, sometimes this two tasks are self-conflict. But finally, I choose transfer each line form getline into a new istringstream to deal with this problem.

Another issue is that we originally want to use a map structure to hold all the threads. But when we applying RAII to our custom SafeThread class, we now cannot assign the instance to the map, since copy constructor is deleted. We have not figure out how to solve this issue yet.



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





##Evaluation:

The files for testing is in the play folder. Including :
    
    Guidenstern.txt
    King.txt
    Queen.txt
    Rosencrantz.txt  ---  each character's script with index


The four characters' script files are badly formed, including reversal of index, white space between valid line, blank lines and so on.
    
    hamlet_ii_2_config.txt  --- the txt used to test the project
    hamlet_ii_2_config_2.txt  --- another txt used to test the project
    hamlet_ii_2_config_3.txt  --- another txt used to test the project


The three config files are also badly formed, including blank lines, but our program still works appropriately. And the result is in result.txt




CSE 532 Fall 2015 Lab 0 Extra Credit
====================================

##Overview

Extra credit part is designed into three part, play class ,main function and three functions.
The play class is kinda different from previous one, because this time we need to separate each character's lines for the convenience of the threads' works.So I use another complex data structure,which is map<string,map<int,string>> , the first string key part prevent the duplicate of the characters, and it leads to <index,line> data structures which is convenient for the output.

The main function part deal with the arguments reading problem, it reads in the play name, config file to generate and the script file to process. And it also set up the threads.

The three functions: fetcher ,config and print are to deal with the input and output problem.

##Insight, Observation and Question

The unique and high-efficient data structure is the most exquisite part. 
I didn't run into many problem when I programmed this one. The only thing deserves to mention is the "." after each character's name, so I use find_last_of function of string to get the right substring of a name.




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



##Evaluation

I use the following file for test:

    hamlet_act_ii_scene_2.txt  ---  txt used for testing

And I got the result of :

    Guidenstern.txt
    King.txt
    Queen.txt
    Rosencrantz.txt 
    hamlet_ii_2_config.txt  ---  the result of this program

In this program, I didn't set up too much code for the encountering of badly-formed lines, such as ,if it encounter some line with two blank lines, it will fail.
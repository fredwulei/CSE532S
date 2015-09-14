CSE 532 Fall 2015 Lab 0
Team member:
	Yiheng Ding  ---  dingyiheng@wustl.edu
	Ren Wan	 ---  wanren@wustl.edu
	Lei Wu  ---  wu.lei@wustl.edu

Instruction:
Unpack:
	Use the cse532s_lab_0.zip to unpack to get the all the files. Including:
	play  ---  folder contains the txt used to test.
		play/Guidenstern.txt
		play/King.txt
		play/Queen.txt
		play/Rosencrantz.txt  ---  each character's script with index
		play/hamlet_ii_2_config.txt  --- the txt used to test the project
		play/hamlet_ii_2_config_2.txt  --- another txt used to test the project
		play/hamlet_ii_2_config_3.txt  --- another txt used to test the project
	play.h
	play.cpp  ---  the play class header and source files
	Source.cpp --- the main function and fetcher function source file
	-----------------------------------------------------------------------------
	result.txt  --- the file contains result of majot test

Build:
	open vs2013 and create a empty c++ project and import the play.h ,play.cpp and Source.cpp build this project.

	And then you have two ways to run the project.
	First is to open cmd to cd to the folder containing the .exe file and place the play folder in the same folder.Type in :

		<.exe name> play/hamlet_ii_2_config.txt

	Second is to place the play folder in the same folder with the three header and sources fils and open the vs2013 solution, open project properties, choose debugging --> command argument --> input :

		play/hamlet_ii_2_config.txt

	and then run, you will get the result.






CSE 532 Fall 2015 Lab 0 Extra credit

Instruction:
Unpack:
	play  ---  folder contains the txt used to test.
		play/hamlet_act_ii_scene_2.txt  ---  txt used for testing
	play.h
	play.cpp  ---  the play class header and source files
	Source.cpp --- the main function and three functions source file
	-----------------------------------------------------------------------------
	play/Guidenstern.txt
	play/King.txt
	play/Queen.txt
	play/Rosencrantz.txt 
	play/hamlet_ii_2_config.txt  ---  the result of this program
Build:
	open vs2013 and create a empty c++ project and import the play.h ,play.cpp and Source.cpp build this project.

	And then you have two ways to run the project.
	First is to open cmd to cd to the folder containing the .exe file and place the play folder in the same folder.Type in :

		<.exe name> hamlet_act_ii_scene_2.txt hamlet_ii_2_config.txt Hamlet Prince of Denmark ACT II Scene II A room in the Castle by William Shakespeare

	Second is to place the play folder in the same folder with the three header and sources fils and open the vs2013 solution, open project properties, choose debugging --> command argument --> input :

		hamlet_act_ii_scene_2.txt hamlet_ii_2_config.txt Hamlet Prince of Denmark ACT II Scene II A room in the Castle by William Shakespeare

	and then run, you will get the result under the play folder.
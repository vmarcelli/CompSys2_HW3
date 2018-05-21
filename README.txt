Valerio Marcelli
vowels.cpp
Assignment1

== Instructions for Running vowels.cpp in a Linux Environment ==
1.	Compiling the code
	Making sure that you are in the same directory as vowels.cpp enter the following command
	g++ vowels.cpp -lpthread -o program
	This will add an .exe file in your directory named program. 
	If you wish, you may replace ‘program’ with any name that you want to name the .exe file as. 
	
	PLEASE COMPILE YOUR CODE WITH  C++11 DEFAULT
	
	If you are unsure as to if you are using C++11 as a default, then compile with this instead:
	g++ -std=c++11 vowels.cpp -lpthread -o program

2.	Running the program
	For this instruction we’ll assume you kept the name program for the .exe, otherwise use whatever name you assigned.
	To run the program type in the following
	./program “stringofdirectorypath”
	The first part is your .exe being told to run, what follows should be a 
	string that leads to the directory which contains file1.txt – file20.txt.
	PLEASE USE QUOTES WHEN TYPING IN THE DIRECTORY PATH
	Your command line argument must be in the form of a string input, otherwise the program will not run!
	
	A correct example would be:
	./program “C:/Documents/User/Person/Folder/subfolder”
	
	Incorrect examples are as follows:
	./program “C:\using\backslash\instead\of\forwardslash”
	./program C:/Not/using/quotes

3.	Using the program
	Everything in the program is automated after this. 
	Sit back and watch the numbers print out on the screen!

== Assumptions on program use ==
This program is assuming that there are 20 files named file1.txt to file20.txt in the directory that you provide. 
This program will look for these files, and if not found will not function correctly. 
It further assumes that each file contains at least one line of writing in them. 
Lastly, it assumes that you’ve followed the instructions in this READ-ME file. 

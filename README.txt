Valerio Marcelli
hw3.cpp
Assignment3

== Instructions for Running vowels.cpp in a Linux Environment ==
1.	Compiling the code
	Making sure that you are in the same directory as hw3.cpp enter the following command
	g++ hw3.cpp -lpthread -lrt -o program
	This will add an .exe file in your directory named program. 
	If you wish, you may replace ‘program’ with any name that you want to name the .exe file as. 
	
	PLEASE COMPILE YOUR CODE WITH  C++11 DEFAULT
	
	If you are unsure as to if you are using C++11 as a default, then compile with this instead:
	g++ -std=c++11 vowels.cpp -lpthread -o program

2.	Running the program
	For this instruction we’ll assume you kept the name program for the .exe, otherwise use whatever name you assigned.
	To run the program type in the following
	./program [Number of seats] [Number of patients]
	The first part is your .exe being told to run, what follows should two numbers seperated by
	a single space.
	Your command line arguments must be in the form of an integer input, otherwise the program will not run!
	
	A correct example would be:
	./program 5 4
	
	Incorrect examples are as follows:
	./program five .3
	./program 0.2 23.4

3.	Using the program
	Everything in the program is automated after this. 
	Sit back and watch the numbers print out on the screen!
	Once you are done, press Ctrl + C to exit the program

== Assumptions on program use ==
This programs assumes that you are using correct inputs for the command line
arguements and that you already know that the only way to exit is through 
Ctrl + C. 
Lastly, it assumes that you’ve followed the instructions in this READ-ME file. 

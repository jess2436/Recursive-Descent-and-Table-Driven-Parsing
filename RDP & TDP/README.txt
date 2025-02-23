CSC 173: Computation and Formal Systems 
Project 2: Recursive Descent and Table-Driven Parsing 
Shadiya Akhter: sakhter@u.rochester.edu
Jessica Chen: jchen204@u.rochester.edu

Once in command line and project folder is included →

TO BUILD/COMPILE PROJECT:
make
TO RUN PROJECT:
./proj2
TO CLEAN:
make clean
The “make clean” command will remove generated object files as well as the executable.

PROGRAM OUTPUT:
Once the run is complete, the user will see the first line as:
“CSC173 Project 1 by Jessica Chen & Shadiya Akhter” 
followed by part one of the project which tests the Recursive Descent Parser. 
The program will open with a prompt for user input:
“Enter your input ('quit' to quit): ”
followed by the the recursive testing:
“RECURSIVE DESCENT PARSING...” 
The parse tree for the input will be printed out following that test statement.
The program will then go on to test part two of the project which is the table-driven parser:
“TABLE DRIVEN PARSING...”
which will also print out the parse tree for the input. Our Part 2 prints out how the stack is looking as well as the state and the lookahead just for clearer understanding.

Each input will have the same procedure until the user enters ‘quit’ which will terminate the program. 

* Our Part 2 also doesn’t print as many nodes in the parse tree as Part 1 does, but in the printed statements of the stack the process is all there! 
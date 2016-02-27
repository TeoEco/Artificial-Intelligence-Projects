Instructions for compiling and running the main.cpp file :

The code is in C++ under the file name main.cpp 

There are few files included:
1. example.txt
	This file has the knowledge base for multi-agent assignment problem.
2. example1.txt
	This file contains the knowledge base for small boolean problem.
3. example2.txt
	This file contains the knowledge base for abstract boolean problem given in the assignment.

Build and run the cpp file and wait for the instructions to pull up on the screen. 

* The program will ask you to enter the file name (Make sure the .txt files are in same folder as .cpp file)
* Enter the name only (Don't include ".txt") (It is assumed that the input file is of type .txt)
	e.g. 
		Enter the file name.
		example
* Next it asks if the file given as input has knowledge base for multi-agent problem or not.
	e.g.
		Is this the multi-agent knowledge base? (y/n)
		y
*If yes, it asks for the number and type of jobs you want the problem to perform.(put "n" for every other knowledge base)
	e.g.
		Enter the number of jobs
		4
		Enter the jobs
		p u w v
*Note that I have taken the jobs as alphabets which is as follows:
	Painter - p
	Stapler - q
	Recharger - r
	Welder - s
	Cutter - t
	Sander - u
	Joiner - v
	Gluer - w
* After this the results will pull up on the screen displaying if result found or not, number of nodes searched,
trace of the procedure followed i.e. when pure clause was found, when unit clause was found and when backtracking occurs,
assignments made and the true propositions.
* You can change the input by re-running the code and instead of multi agent problem giving abstract boolean knowledge
base as input and selecting "n" for is this the multi-agent knowledge base question.

* Line 405-419 are for finding pure clause; Line 422-448 are for finding Unit clause.
*You can comment out appropriate lines to get results for only backtracking and backtracking with unit clause only.

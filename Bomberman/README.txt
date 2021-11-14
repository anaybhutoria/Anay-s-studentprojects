#Bomberman

###Compiling
To first compile the document type "gcc Bomberman.c"

Now, from this you create a file named 'a.out' and this is the file you have compiled to now run.

To run this program with randomly generated numbersplease type the following:

	"./a.out <name> <number of Rows> <number of Columns>" and ofcourse replace the angle paranthesis with the numbers you wish to choose.



I chose to implement no maximum for the grid size

I used time.h to implement the duration of gameplay

The sorting algorithm I made was :
Firstly I made a variable of how large the the topscores the user had inputed, I made 2 variables
and one was named "largest" and one was named "current" and I set largest to -9999 to start and current would iterate through the struct array which
would compare 'current' with 'largest' if largest was smaller then it  would replace largest with current and once it did that it set 
that index of the temorary array to -10000 , and then print the largest score, then it would go to the next largest number and
keep iterationg through the struct array till it reaches the end



lastly please read the Rules of the Game to learn important information.


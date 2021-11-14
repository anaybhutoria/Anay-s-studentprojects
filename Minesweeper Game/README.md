# Minesweeper
### Running Minesweeper
In GitHub please open the folder Minesweeper Game in order to find the final iteration of the game. In addition to the application and the view packages the program contains the previous packages from the first iteration. In order to run the program in eclipse, first clone the repository from the desktop app so that it contains the latest version of the repository. In eclipse create a JAVA project and import the files retrived from the GitHub into the src folder. In the application package run the GameApp.java in order to run the game.   

## Getting Started
### Cloning Repository
If you're new to using GitHub and git, please refer to [Cloning a Repository](https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository) to learn how to create a local version of an existing repository on your computer. This can be done either using GitHub Desktop or command line/terminal.
### Collaboration
It's important NOT to make any changes directly to the master branch.  
Instead, we will use a shared repository model to collaborate effectively as a small team. In this model, we all work on the same repository (no forks) and each individual will create their own branches to work on.  
Here are some general guidelines to consider:
* You can create as many branches as you need to keep things organized, but branches should always have concise and meaningful names. 
* You may delete branches after they are merged successfully into another branch. This does not affect the git history and git will warn you if you have any unmerged changes. Please refer to [Learn Git Branching](https://learngitbranching.js.org) if you'd like a visual tutorial on git and branches.
* When you're satisfied with the code you've written, make a pull request for it to be reviewed. Do NOT make pull requests on code that does not compile.
* If you need help with your code, you can share the name of your current working branch, as well as a brief description of the problem you're facing, in Microsoft Teams for assistance.
## Coding Style
The following are examples of conventions that should be followed when using braces and white space.  
If-Statements
```
if (condition) {
  // code block
} else if {
  // code block
} else {
  // code block
}
```
While & For Loops
``` 
while (condition) {
  // code block
}
 
for (statement 1; statement 2; statement 3) {
  // code block
}
```
Arrays
```
String[] name = {"String1", "String2", "String3", "String4"};
```
Classes & Methods
```
public class MyClass {
  // instance variables
  
  static void myMethod() {
    // code block
  }

  public static void main(String[] args) {
    MyClass myObj = new MyClass();
    // code block
  }
}
```
As a general rule, put one space between operators and operands (e.g. x > 5) and no spaces between operators (e.g >=). 

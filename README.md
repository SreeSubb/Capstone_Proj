# CPPND: Capstone Snake Game Project Details

In the original Snake game, player navigates the snake to randomly placed food in the grid to let the snake the consume food, so that it grows in size and accelerates further. Player accumulates score if the snake grows and increase its speed. I extended this snake game with following additional features. 
1.	Added another snake and controller to launch two snakes using the threads functionality in C++ so that two players can compete simultaneously.
2.	Added predators randomly in the grid to make the game more challenging since the encounter with predator would lower the score and slow down the snakes. Created Threat objects on the grid for the predators to accomplish this.

Rubric Points:

1.	Project code is compiling successfully without errors and warnings in the Udacity workspace. 
2.	cmake and make is used for building the source code.

Loops, Functions, I/O:

1.	In the game.cpp file a new function PlaceThreat() with the “if loop” statement is used place the Threat objects in the grid. 
2.	In the “renderer.cpp” file RenderThreat() function is added with the switch statement to render the blocks as per enum values. 
3.	In the main.cpp source code, “std::ofstream” lib is used to get the user name and store the values in a text file and later the  score is appended in the same file once the game is over.

Object Oriented Programming:

1.	“class Threat” is added in the “game.h/cpp” that holds the threat member methods and variables. Objects of this class is placed randomly in the grid using PlaceThreat() in the game.cpp file. 
2.	“Predator” with type enum is used in this project to store various type of predators. This predator enum type is passed on to the Threat() method of the “class Threat” to construct the Threat objects. 
3.	Appropriate Class constructors, member initializations, getters/setters are used for “class Threat”.

Memory Management:

1.	“std::unique_ptr<Threat> threat” is declared in the “game.h” to use the unique_ptr type smart pointer to point to the memory addresses Threat objects.
2.	Memory is allocated for the “threat” smart pointer using “std::make_unique<Threat>” when object is constructed during the invocation of  PlaceThreat() function. This pointer will be out of scope when this function returns.
2.	References are passed in the “RenderThreat(std::unique_ptr<Threat> const &threat, SDL_Rect &block)” function in the renderer.cpp file, that prevents copying the values.

Concurrency:

1.	“std::thread” is used to launch two threads for two players. Join() is also used along the respective threads. Contructor and method HandleInput() of “class Controller” were modified to handle two sets (I/O) key inputs.
2.	“std::unique_lock<std::mutex>” is used in the RenderThreat() method of renderer.cpp to avoid data race when one thread is accessing it. 

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

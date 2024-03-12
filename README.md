# Pacman-Craft
craft your Pac-Man game's map yourself and play it
this pac-man game is different!

you can unleash your creativity and design the Pacman game of your dreams

👻 Customize Ghosts:
Choose any ghosts you want and place them wherever you like on the map. Give them unique behaviors and make the game as challenging as you wish!

🧱 Design Walls:
Create intricate mazes by placing walls on any map and game world you can imagine. 🏁

🍒 Food Galore:
Place various types of food items throughout the map to challenge Pacman's hunger. 🍎🍓🍌

🎨 Unlimited Creativity:
There are no limits to your imagination with this tool. Craft the perfect Pacman game and then dive in to play the unique game you've created! 🎮

🚀 Get started now and let the fun begin! Happy Gaming! 

<img src="https://github.com/salehsoleimani/Cpp-Pacman/blob/master/Screenshot%202023-03-14%20at%2011.54.12%20AM.png"  width="300"><img src="https://github.com/salehsoleimani/Cpp-Pacman/blob/master/Screenshot%202023-03-14%20at%2011.54.17%20AM.png"  width="300">

# Installation
## Prerequisites
- Make sure you have CMake installed on your system. You can download it from the official website (https://cmake.org/).
- C++ Compiler (GCC is recommended)

## Run the project
1. Open a terminal or command prompt and navigate to the root directory of the CMake project.

2. Create a new directory for the build output files. This can be done by running the following command in the terminal:
```
mkdir build
```
3. Change to the build directory by running:
```
cd build
```
4. Generate the build files by running the CMake command with the path to the root directory of the project:
```
cmake ..
```
5. Once the CMake command completes successfully, you can now build the project by running:
```
cmake --build .
```
This command will build the project according to the instructions specified in the CMakeLists.txt file.
6. Once the build process is complete, you can run the executable file generated by the build process. This file will typically be located in the build directory.
```
./executable_name
```
Replace "executable_name" with the name of the executable file generated by the build process.



## Preview

<img src="https://github.com/salehsoleimani/Cpp-Pacman/blob/master/Screenshot%202023-03-14%20at%2011.52.13%20AM.png"  width="300"><img src="https://github.com/salehsoleimani/Cpp-Pacman/blob/master/Screenshot%202023-03-14%20at%2011.51.55%20AM.png"  width="300"><img src="https://github.com/salehsoleimani/Cpp-Pacman/blob/master/Screenshot%202023-03-14%20at%2011.52.08%20AM.png"  width="300">

## Project Architecture

as a university C++ project, I had to use C++ and SFML and they don't offer a clean and maintainable architecture for building your apps.

I tried designing a clean architecture out of it with interfaces, classes, inheritance, designing, and implementing custom views.

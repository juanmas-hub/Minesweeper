
# 🕹️Minesweeper in c++ with SDL2

This is a clone of the classic Minesweeper game developed in C++ with a graphical interface using SDL2. The gameplay follows the traditional rules, offering a familiar and entertaining experience.

## Project Description

Minesweeper is a logic-based game where the objective is to clear a minefield without detonating any mines. This project replicates the classic game experience with a user-friendly and graphical interface.
## Installation

To run this project, you will need to install and configure SDL2 and a C++ compiler. Here are the basic steps:

1. **Install SDL2**:
   - Download SDL2 from the [official website](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.11).
   - You will also need to download SDL_ttf.
   - Follow the installation instructions for your operating system.

  
2. **Install MinGW**:
   - Download MinGW from the [official website](https://www.mingw-w64.org/).
   - Make sure you read the documentation on how to use this compiler.

4. **Configure the Project**:
   - Ensure the SDL2 headers and libraries are correctly set up in your development environment, such as the /include folders and the /lib/x64 folders. You must also include the main SDL folder to your environment variables.
   - Compile the project, making sure to link the SDL2 libraries.
   - using MinGW, you might run a command like:
```bash
   g++ -o my_project main.cpp -IC:/path/to/SDL2/include -LC:/path/to/SDL2/lib -lSDL2 -lSDL2_ttf
```
   - Add to your project folder the arial.ttf font.  


## 🎮 Controls

- **Left Click**: Reveal a cell.
- **Right Click**: Place or remove a flag.

## 📊 Current Status
Difficulty: Difficulty options enabled based on number of mines.

Rendering: Smooth rendering of game objects using SDL2.


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

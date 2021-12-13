# Conway's Game of Life #

The Game of Life is a cellular automata which updates according to the following rules:
- Any live cell with fewer than two live neighbours dies, as if by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

With just these simple rules, given certain simple enough looking initial
conditions, great complexity can arise.

## To build and run this project: ##


From a command prompt in the `game_of_life` directory, run the following commands:
1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make all`
5. `./game_of_life`

To build project using VS Code, navigate to the `game_of_life` directory:
1. From a command prompt, run `code .`
2. Press <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>X</kbd> to open the Extensions panel.
3. Ensure that CMake Tools by Microsoft is installed. (ms-vscode.cmake-tools)
4. Press <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd> and type `cmake build`

### Acknowledgements ###
- Ths project was started using the template found at https://github.com/juliettef/GLFW-CMake-starter.

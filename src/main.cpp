// Driver for the GUI.

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <iostream>
#include "grid.h"

// Define some global variables
Grid grid = Grid();

const int BUF_SIZE = 5; // Add a buffer of BUF_SIZE around the grid so the edges of the grid are off screen.

const double ROW_WIDTH = 2.0 / (NUM_ROWS-2*BUF_SIZE);
const double COL_WIDTH = 2.0 / (NUM_COLS-2*BUF_SIZE);

static double time_step = 0.1;
static bool play = false;

enum Color{BLACK, BLUE, GREY};
const Color ALIVE_COLOR = BLUE;
const Color DEAD_COLOR = BLACK;



// Set the current openGL color to the appropriate 
// color as specified by the color paramater.
void select_color(Color color) {
    switch (color) {
        case BLACK:
            glColor3f(0, 0, 0);
            break;
        case BLUE:
            glColor3f(0, .2, 1);
            break;
        case GREY:
            glColor3f(0.3, 0.3, 0.3);
            break;
    }
}


// Do the appropriate action when certain keys are pressed.
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if ((key == GLFW_KEY_UP || key == GLFW_KEY_W || key == GLFW_KEY_K) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        time_step /= 2;
    } else if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S || key == GLFW_KEY_J) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        time_step *= 2;
    } else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        play = !play;
    } else if (key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        grid.update();
    } else if (key == GLFW_KEY_P && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        grid.prev_state();
    } else if (key == GLFW_KEY_C && (action == GLFW_PRESS)) {
        grid.clear();
    } else if (key == GLFW_KEY_U && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        grid.incr_prob();
    } else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        grid.decr_prob();
	}
}



// Toggle the state of a cell when it is clicked.
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                int window_width, window_height;
        glfwGetWindowSize(window, &window_width, &window_height);
        int pixels_per_col = window_width /  (NUM_COLS-2*BUF_SIZE);
        int pixels_per_row = window_height / (NUM_ROWS-2*BUF_SIZE);

        // x_pos is the number of pixels from the left
        // y_pos is the number of pixels from the top
        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);

        int row = y_pos / pixels_per_row;
        int col = x_pos / pixels_per_col;
        bool prev_state = grid.get_cell(row+BUF_SIZE, col+BUF_SIZE);
        grid.set_cell(row+BUF_SIZE, col+BUF_SIZE, !prev_state);
    }
}


// Fill the cell at (row, col) with color.
void fill_cell(int row, int col, Color color) {
    double x_left = col * COL_WIDTH - 1;
    double x_right = (col + 1) * COL_WIDTH - 1;
    double y_top = - (row * ROW_WIDTH - 1);
    double y_bottom = - ((row + 1) * ROW_WIDTH - 1);
    select_color(color);
    glBegin(GL_POLYGON);
        glVertex2d(x_left, y_top);
        glVertex2d(x_left, y_bottom);
        glVertex2d(x_right, y_bottom);
        glVertex2d(x_right, y_top);
    glEnd();
}


// Draw the grid lines.
void draw_lines() {
    select_color(GREY);
        glBegin(GL_LINES);
        // Draw the vertical lines.
        for (double i = -1; i <= 1; i += COL_WIDTH) {
            glVertex2d(i, 1); glVertex2d(i, -1);
        }
        // Draw the horizontal lines.
        for (double j = -1; j <= 1; j += ROW_WIDTH) {
            glVertex2d(1, j); glVertex2d(-1, j);
        }
    glEnd();
}


// Display the grid.
void display_grid(Grid& grid) {
    Color color;
    bool is_alive;
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            is_alive = grid.get_cell(i+BUF_SIZE, j+BUF_SIZE);
            if (is_alive) { color = ALIVE_COLOR; }
            else { color = DEAD_COLOR; }
            fill_cell(i, j, color);
        }
    }
}


// Run the Game of Life.
int main() {
    // Initialize glfw.
    if (!glfwInit()) {
        std::cout << "Failed to initialize glfw. Program exiting." << std::endl;
        return -1;
    }
    int window_width = 2000;
    int window_height = 2000;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Game Of Life", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create window. Program exiting." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Make glfw listen to the appropriate keys.
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    double prev_time = 0;
    double cur_time;

    // Print instructions
    std::cout << "Welcome to Conway's Game of Life." << std::endl;
    std::cout << "Click on a square to toggle its state." << std::endl;
    std::cout << "Press the space bar to toggle the flow of time." << std::endl;
    std::cout << "Press the up arrow (or k or w) to double the rate of time." << std::endl;
    std::cout << "Press the down arrow (or j or s) to half the rate of time." << std::endl;
    std::cout << "Press the n key to increment the time step by one." << std::endl;
    std::cout << "Press the p key to decrement the time step by one." << std::endl;
    std::cout << "Press the c key to clear the grid." << std::endl;
	std::cout << "Press the u key to increase the probability of a cell randomly coming to life" << std::endl;
	std::cout << "Press the d key to decrease the probabiliyt of spontaneous birth." << std::endl;
    std::cout << "Press the escape key to exit the program." << std::endl;

    // Event loop
    while (!glfwWindowShouldClose(window)) {
        // Create the next frame
        glClear(GL_COLOR_BUFFER_BIT);
        cur_time = glfwGetTime();
        if (cur_time > prev_time + time_step) {
            prev_time = cur_time;
            if (play) { grid.update(); }
        }
        glfwPollEvents();
        display_grid(grid);
        draw_lines();

        // Display the next frame
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

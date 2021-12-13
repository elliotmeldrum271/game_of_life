// Driver for the GUI.

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include "grid.h"

const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 500;

const double ROW_WIDTH = 2.0 / NUM_ROWS;
const double COL_WIDTH = 2.0 / NUM_COLS;

static double time_step = 0.1;
static bool play = false;

static int row = 0;
static int col = 0;

enum Color{BLACK, RED, GREEN, BLUE, WHITE};

Color ALIVE_COLOR = BLUE;
Color DEAD_COLOR = BLACK;


void select_color(Color color) {
    switch (color) {
        case BLACK:
            glColor3f(0, 0, 0);
            break;
        case RED:
            glColor3f(1, 0, 0);
            break;
        case GREEN:
            glColor3f(0, 1, 0);
            break;
        case BLUE:
            glColor3f(0, 0, 1);
            break;
        case WHITE:
            glColor3f(1, 1, 1);
            break;
    }
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if ((key == GLFW_KEY_UP || key == GLFW_KEY_W || key == GLFW_KEY_K) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        time_step /= 2;
    }
    else if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S || key == GLFW_KEY_J) && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        time_step *= 2;
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        play = !play;
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


// Fill the cell at (row, col) using the color defined by the red, green and blue paramaters 
void fill_cell(int row, int col, double red, double green, double blue) {
    double x_left = col * COL_WIDTH - 1;
    double x_right = (col + 1) * COL_WIDTH - 1;
    double y_top = - (row * ROW_WIDTH - 1);
    double y_bottom = - ((row + 1) * ROW_WIDTH - 1);
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
        glVertex2d(x_left, y_top);
        glVertex2d(x_left, y_bottom);
        glVertex2d(x_right, y_bottom);
        glVertex2d(x_right, y_top);
    glEnd();
}


void draw_lines() {
    glColor3f(0.3, 0.3, 0.3);
        glBegin(GL_LINES);
        // vertical lines
        for (double i = -1; i <= 1; i += COL_WIDTH) { glVertex2d(i, 1); glVertex2d(i, -1); }
        // horizontal lines
        for (double j = -1; j <= 1; j += ROW_WIDTH) { glVertex2d(1, j); glVertex2d(-1, j); }
    glEnd();
}


// Display the grid.
void display_grid(Grid& grid) {
    // bool* bit_array = grid.get_bit_array();
    Color color;
    bool is_alive;
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            is_alive = grid.get_cell(i, j);
            if (is_alive) { color = ALIVE_COLOR; }
            else { color = DEAD_COLOR; }
            fill_cell(i, j, color);
        }
    }
}


int main() {
    // Initialize the window.
    if (!glfwInit()) { return -1; }
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Of Life", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT);

    double prev_time = 0;
    double cur_time;
    Grid grid = Grid();

    // game loop
    while (!glfwWindowShouldClose(window)) {

        // create the next frame
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        cur_time = glfwGetTime();
        if (cur_time > prev_time + time_step) {
            prev_time = cur_time;
            if (play) {
                grid.update();
            }
        }

        // render the next frame
        display_grid(grid);
        draw_lines();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

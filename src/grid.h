// Header file for the grid that conway's game of life takes place on
#ifndef __GRID_H
#define __GRID_H

const int NUM_ROWS = 100;
const int NUM_COLS = 100;

class Grid {
    private:
        bool* bit_array;
        void set_cell(int i, int j, bool is_alive);
    public:
        Grid();
        bool get_cell_at(int i, int j);
        void update();
        ~Grid();
};

#endif

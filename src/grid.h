// Header file for the grid that conway's game of life takes place on
#ifndef __GRID_H
#define __GRID_H

const int NUM_ROWS = 100;
const int NUM_COLS = 100;

class Grid {
    private:
        bool* bit_array;
<<<<<<< HEAD
        int count_neighbors(int i, int j);
=======
>>>>>>> 7aa6bcc07a99a42b1b93ea88c318d32b429160e7
    public:
        Grid();
        bool get_cell(int i, int j);
        void set_cell(int i, int j, bool is_alive);
        void update();
        ~Grid();
};

#endif

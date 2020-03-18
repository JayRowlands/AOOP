/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author YOUR_STUDENT_NUMBER
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
    
private:
    int width;
    int height;
    int totalCells;
    int numAliveCells;
    int numDeadCells;

public:

    Grid();
    Grid(int square_size);
    Grid(int width, int height);
    int get_width();
    int get_height();
    int get_total_cells();
    int get_alive_cells();
    int get_dead_cells();
    void resize(int square_size);
    void resize(int new_width, int new_height);
    int get_index(int x, int y);
};

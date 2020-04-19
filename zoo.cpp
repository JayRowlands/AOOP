/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 959133
 * @date March, 2020
 */
#include "zoo.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...
#include <fstream>
#include <bitset>
#include <algorithm>
#include <stdexcept>
/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider() {
    Grid glider(3);

    glider.set(1,0, Cell::ALIVE);
    glider.set(2,1, Cell::ALIVE);
    glider.set(0,2, Cell::ALIVE);
    glider.set(1,2, Cell::ALIVE);
    glider.set(2,2, Cell::ALIVE);
    
    return glider;
};

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
Grid Zoo::r_pentomino() {
    Grid r_pentomino(3);

    r_pentomino.set(1,0, Cell::ALIVE);
    r_pentomino.set(2,0, Cell::ALIVE);
    r_pentomino.set(0,1, Cell::ALIVE);
    r_pentomino.set(1,1, Cell::ALIVE);
    r_pentomino.set(1,2, Cell::ALIVE);
    
    return r_pentomino;
};

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship() {
    Grid light_weight_spaceship(5,4);

    light_weight_spaceship.set(1,0, Cell::ALIVE);
    light_weight_spaceship.set(4,0, Cell::ALIVE);
    light_weight_spaceship.set(0,1, Cell::ALIVE);
    light_weight_spaceship.set(0,2, Cell::ALIVE);
    light_weight_spaceship.set(4,2, Cell::ALIVE);
    light_weight_spaceship.set(0,3, Cell::ALIVE);
    light_weight_spaceship.set(1,3, Cell::ALIVE);
    light_weight_spaceship.set(2,3, Cell::ALIVE);
    light_weight_spaceship.set(3,3, Cell::ALIVE);

    return light_weight_spaceship;
};

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(std::string path){
    std::ifstream inputFile(path);
    if (!inputFile) {
        throw std::runtime_error("File not found");
    }

    if (!inputFile.is_open()) {
    return 1;
    }

    int readWidth;
    int readHeight;

    inputFile >> readWidth;
    inputFile >> readHeight;
    if (readWidth < 0 || readHeight < 0) {
        throw std::runtime_error("Incorrect height or width.");
    }
    Grid newGrid(readWidth, readHeight);
    char readCell;
    for (int y = 0; y < readHeight; y++) {
        for (int x = 0; x < readWidth; x++) {
            if(!inputFile.eof()) {
                inputFile.get (readCell);
                if (readCell == '\n') {
                    readCell = inputFile.get();
                }
                if (readCell == Cell::DEAD) {
                    newGrid.set(x,y, Cell::DEAD);
                } else if (readCell == Cell::ALIVE) { 
                    newGrid.set(x,y, Cell::ALIVE);
                } else {
                    throw std::runtime_error("Malformed");
                }
            }
        }
    }
    return newGrid;
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(std::string path, Grid grid) {
    std::ofstream outputFile (path, std::ofstream::out);
    if (!outputFile.is_open()) {
        throw std::runtime_error("File cannot be opened");
    }
    outputFile << grid.get_width();
    outputFile << " ";
    outputFile << grid.get_height();
    outputFile << "\n";

    for (int y = 0; y < grid.get_height(); y++) {
        for (int x = 0; x < grid.get_width(); x++) {
            char cell = grid.get(x,y);
            outputFile << cell;
        }
        outputFile << "\n";
    }
    outputFile.close();
}

/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(std::string path) {
    
    std::ifstream inputFile(path, std::ios_base::binary);
    
    Grid newGrid;
    int readWidth;
    int readHeight;

    inputFile.read((reinterpret_cast<char*>(&readWidth)),sizeof(int));
    inputFile.read((reinterpret_cast<char*>(&readHeight)),sizeof(int));
    newGrid.resize(readWidth,readHeight);
    newGrid.grid.clear();

    if (inputFile) {
        inputFile.seekg (0, inputFile.end);
        int length = inputFile.tellg();
        inputFile.seekg (0, inputFile.beg);

        char * buffer = new char [length];
        inputFile.read (buffer,length);
        int total = 0;
        for (int i=8;i < length; i++) {
            std::bitset<8> byte (buffer[i]);
            std::string newString = byte.to_string();
            for (int j = 7; j >= 0; j--){
                if (total <= newGrid.get_total_cells()) {
                    if(newString[j] == '1') {
                        newGrid.grid.push_back(Cell::ALIVE);
                    } else if (newString[j] == '0') {
                        newGrid.grid.push_back(Cell::DEAD);
                    }
                    total++;
                }
            }
        }
        
    delete[] buffer;
    inputFile.close();
    }
  
   
    for (int y = 0; y < readHeight; y++) {
        for (int x = 0; x < readWidth; x++) {
            Cell v = newGrid.get(x,y);
            if (v == 32) {
                std::cout << " ";
            } else if (v == 35) {
                std::cout << "#";
            }
        }
        std::cout << "|\n";
    }
    std::cout << "\n";
    
    return newGrid;
}

/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_binary(std::string path, Grid grid) {
    std::ofstream outputFile(path);
    
    int width = grid.get_width();
    int height = grid.get_height();
    
    outputFile.write((char*)&width, 4);
    outputFile.write((char*)&height, 4);

    int count = 0;
    int padSize = grid.get_total_cells() + (grid.get_total_cells()%8);
    std::bitset<8> byte;
    for (int i = 0; i < padSize; i++) {
        if (grid.grid[i] == Cell::ALIVE) {
            byte[count] = 1;
        } else {
            byte[count] = 0;
        }      
        
        count++;
        if (count == 8) {
            outputFile.write((char*)&byte,1);
            count = 0;
        }
        
    }

    outputFile.close();
}

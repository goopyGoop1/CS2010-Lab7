#include <iostream>  // Include the library for input/output stream operations
#include <fstream>   // Include the library for file stream operations
#include "diction.h" // Include the header file that defines DICTION and associated functions

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided
    // The program expects exactly one argument (the file name)
    if(argc != 2) {
        // Inform the user about the correct usage of the program
        std::cout << "Usage: " << argv[0] << " <filename>\n";
        return 1; // Exit the program with an error code
    }

    // Open the file provided as a command-line argument
    std::ifstream inputFile(argv[1]);
    // Check if the file was successfully opened
    if(!inputFile) {
        // Print an error message if the file cannot be opened
        std::cout << "Error opening file: " << argv[1] << "\n";
        return 1; // Exit the program with an error code
    }

    // Declare an instance of the DICTION structure to hold file analysis results
    DICTION d;

    // Process the input file and populate the DICTION structure
    processFile(d, inputFile);

    // Display the results of the file analysis
    displayResults(d);

    // Close the input file to release resources
    inputFile.close();

    // Exit the program with a success code
    return 0;
}

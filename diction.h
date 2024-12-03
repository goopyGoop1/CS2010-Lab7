#ifndef DICTION_H // Prevent multiple inclusions of this header file
#define DICTION_H // Define the DICTION_H macro if not already defined

#include <iostream>  // Include the standard input/output library
#include <fstream>   // Include the file input/output library
#include <string>    // Include the string library
#include <set>       // Include the set container for unique collections
#include <map>       // Include the map container for key-value pairs
#include <queue>     // Include the queue and priority queue containers
#include <tuple>     // Include the tuple library for grouping multiple values
#include <cctype>    // Include character handling functions
#include <iomanip>   // Include library for input/output manipulators
#include <algorithm> // Include algorithms for operations like sorting

// Type definitions for better code readability and easier maintenance
using WORD = std::string; // Define WORD as an alias for std::string
using WORD_LIST = std::set<WORD>; // Define WORD_LIST as a set of WORDs (unique words)
using WORD_FREQ_LIST = std::map<char, int>; // Define WORD_FREQ_LIST as a map of characters and their frequencies
using FREQ_WORD_LIST = std::multimap<int, WORD>; // Define FREQ_WORD_LIST as a multimap of frequencies and WORDs
using COUNTER = std::tuple<int, int, int>; // Define COUNTER as a tuple to store counts (letters, words, lines)
using LONGEST = std::priority_queue<WORD>; // Define LONGEST as a priority queue of WORDs (to track longest words)

// Struct to hold all dictionary-related data
struct DICTION {
    COUNTER stats; // Tuple to store the total count of letters, words, and lines
    WORD_LIST words; // Set to store unique words from the file
    WORD_FREQ_LIST wordFreq; // Map to store the frequency of each letter
    FREQ_WORD_LIST freqWord; // Multimap to associate word frequencies with their respective words
    LONGEST longWord; // Priority queue to store words sorted by their length
};

// Function prototypes to be implemented elsewhere in the program
WORD getNextWord(std::ifstream &file); // Function to extract the next word from a file
void processFile(DICTION &d, std::ifstream &file); // Function to process a file and populate a DICTION structure
void displayResults(const DICTION &d); // Function to display the results of file processing
void displayLetterFreq(const DICTION &d); // Function to display letter frequency
void displayHistogram(const DICTION &d); // Function to display a histogram of word frequencies

#endif // DICTION_H // End of include guard to prevent multiple inclusions


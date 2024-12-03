# CS2010-Lab7 Chad 

### README: Text File Analysis Tool

---

#### **Overview**
This project is a text analysis tool that reads a file, processes its contents, and generates insights, including letter frequencies, word frequencies, and a histogram of word lengths. The tool is modular and organized across three main files:

1. **`textAnalysis.cpp`**: The entry point containing the `main()` function.
2. **`textFunctions.cpp`**: The implementation of helper functions for file processing and data analysis.
3. **`diction.h`**: The header file that defines types, structures, and function prototypes.

---

#### **Files**

1. **`diction.h`**
   - Contains type definitions for `WORD`, `WORD_LIST`, and other useful abstractions.
   - Defines the `DICTION` structure, which holds analysis results such as:
     - Word list
     - Letter frequencies
     - Word frequencies
     - Longest words
     - File statistics (letters, words, lines).
   - Declares the functions used in the program, ensuring modularity.

2. **`textFunctions.cpp`**
   - Implements all the helper functions:
     - **`getNextWord`**: Extracts the next valid word from the file.
     - **`processFile`**: Processes the file to populate the `DICTION` structure.
     - **`displayLetterFreq`**: Displays the frequency of each letter (case-sensitive).
     - **`displayHistogram`**: Generates a histogram showing word frequencies.
     - **`displayResults`**: Combines all output and displays the analysis results.

3. **`textAnalysis.cpp`**
   - Contains the `main()` function:
     - Validates command-line arguments.
     - Opens the specified file for analysis.
     - Calls `processFile` to extract information.
     - Uses `displayResults` to display the analysis results.
     - Closes the file after processing.

4. **`Text_File.txt`**
   - Example input file for testing the tool. Users can replace this file with their own text files for analysis.

---

#### **How to Compile**

Use the following command to compile the program:

```bash
g++ textAnalysis.cpp textFunctions.cpp -o textAnalyzer
```

---

#### **How to Run**

Execute the program with the following command:

```bash
./textAnalyzer <filename>
```

Example:

```bash
./textAnalyzer Text_File.txt
```

Replace `Text_File.txt` with the path to your file.

---

#### **Output**

The program provides:
1. **Letter Frequency**: Counts of each letter (case-sensitive).
2. **Word Frequency**: Frequencies of words in the text.
3. **Histogram**: Visual representation of word lengths and their counts.
4. **Statistics**: Total number of letters, words, and lines in the file.

---

#### **Features**

- **Modularity**: Functions are implemented separately in `textFunctions.cpp`, enabling clean code organization.
- **Flexibility**: Accepts any text file as input.
- **Visual Representation**: Includes histograms for better data understanding.

---

#### **Dependencies**

- Standard C++ libraries:
  - `<iostream>`, `<fstream>`: For file and console I/O.
  - `<string>`, `<map>`, `<set>`: For managing word data.
  - `<tuple>`, `<queue>`: For storing and prioritizing data.
  - `<algorithm>`, `<cctype>`, `<iomanip>`: For data manipulation and formatting.

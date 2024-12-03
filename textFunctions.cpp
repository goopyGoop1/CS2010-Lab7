#include "diction.h" // Include the header file for DICTION structure and function prototypes

// Function definitions

// Function to extract the next word from a file
WORD getNextWord(std::ifstream &file) {
    WORD w; // Initialize an empty word
    char ch; // Variable to store each character
    bool inWord = false; // Flag to check if we are inside a word
    
    file.get(ch); // Read the first character
    while(!file.eof()) { // Loop until the end of the file
        if(isalpha(ch)) { // Check if the character is alphabetic
            w.push_back(ch); // Add the character to the current word
            inWord = true; // Mark that we are inside a word
        }
        else if(inWord) return w; // If we reach a non-alphabetic character, return the word
        file.get(ch); // Read the next character
    }
    return w; // Return the last word if any
}

// Function to process the file and populate the DICTION structure
void processFile(DICTION &d, std::ifstream &file) {
    char ch; // Character to read from the file
    int letters = 0, words = 0, lines = 1; // Counters for letters, words, and lines
    std::map<WORD, int> wordCount; // Map to count word frequencies

    // First pass: Count letters, lines, and letter frequencies
    while(file.get(ch)) { // Read each character from the file
        letters++; // Increment letter count
        if(ch == '\n') lines++; // Increment line count if newline is encountered
        if(isalpha(ch)) { // If the character is alphabetic
            d.wordFreq[ch]++; // Increment the frequency of the letter
        }
    }

    file.clear(); // Clear file state
    file.seekg(0); // Reset file pointer to the beginning

    // Second pass: Extract words and update word-related data
    WORD word; // Variable to store each word
    while(!(word = getNextWord(file)).empty()) { // Extract words until the end of the file
        words++; // Increment word count
        d.words.insert(word); // Insert the word into the set of unique words
        wordCount[word]++; // Increment the frequency of the word
        d.longWord.push(word); // Add the word to the priority queue of long words
    }

    // Populate the freqWord multimap with word frequencies
    for(const auto &pair : wordCount) {
        d.freqWord.insert({pair.second, pair.first}); // Insert frequency and word into the multimap
    }

    // Update the stats tuple with letter, word, and line counts
    d.stats = std::make_tuple(letters, words, lines);
}

// Function to display letter frequencies
void displayLetterFreq(const DICTION &d) {
    std::cout << "/--------------\\\n";
    std::cout << "| Letter Freq  |\n";
    std::cout << "\\--------------/\n";

    // Display frequencies for uppercase letters
    for(char c = 'A'; c <= 'Z'; c++) {
        auto it = d.wordFreq.find(c); // Find the frequency of the letter
        int freq = (it != d.wordFreq.end()) ? it->second : 0; // Get the frequency or 0 if not found
        std::cout << c << " |" << std::string(std::min(freq, 10), '*'); // Display the letter and asterisks
        if(freq > 10) std::cout << " (" << freq - 10 << ")"; // Display overflow count if frequency > 10
        std::cout << '\n';
    }

    // Display frequencies for lowercase letters
    for(char c = 'a'; c <= 'z'; c++) {
        auto it = d.wordFreq.find(c);
        int freq = (it != d.wordFreq.end()) ? it->second : 0;
        std::cout << c << " |" << std::string(std::min(freq, 10), '*');
        if(freq > 10) std::cout << " (" << freq - 10 << ")";
        std::cout << '\n';
    }
}

// Function to display a histogram of word frequencies
void displayHistogram(const DICTION &d) {
    std::cout << "/-----------\\\n";
    std::cout << "| Histogram |\n";
    std::cout << "\\-----------/\n\n";

    // Priority queue to sort words by length
    std::priority_queue<std::pair<int, std::string>, 
                      std::vector<std::pair<int, std::string>>,
                      std::greater<std::pair<int, std::string>>> wordQueue;

    for (const auto &word : d.words) { // Loop through unique words
        wordQueue.push({(int)word.length(), word}); // Push word length and word into the queue
    }

    std::vector<std::string> sortedWords; // Vector to store sorted words
    std::vector<int> frequencies; // Vector to store word frequencies

    // Extract words from the queue and calculate frequencies
    while (!wordQueue.empty()) {
        auto word = wordQueue.top().second; // Get the shortest word
        sortedWords.push_back(word); // Add it to the sortedWords vector

        int freq = 0;
        for (const auto &pair : d.freqWord) { // Find the frequency of the word
            if (pair.second == word) {
                freq = pair.first;
                break;
            }
        }
        frequencies.push_back(freq); // Add the frequency to the frequencies vector
        wordQueue.pop(); // Remove the processed word from the queue
    }

    int maxFreq = *std::max_element(frequencies.begin(), frequencies.end()); // Find the maximum frequency
    int longestWordLength = 0; // Initialize the length of the longest word
    for (const auto &word : sortedWords) {
        if (word.length() > longestWordLength) {
            longestWordLength = word.length(); // Update the longest word length
        }
    }

    // Display the histogram vertically
    for (int i = maxFreq; i > 0; i--) {
        std::cout << std::string((longestWordLength + 3), ' '); // Align with the longest word
        for (int freq : frequencies) {
            std::cout << (freq >= i ? "*" : "  "); // Print asterisks or spaces based on frequency
        }
        std::cout << "\n";
    }
    std::cout << std::string(sortedWords.size() * 4, '-') << " \n"; // Print horizontal separator

    for (int i = 0; i < sortedWords.size(); i++) {
        std::cout << std::left << std::setw(longestWordLength + 2) << sortedWords[i]; // Print words
        std::cout << std::string(i + 1, '-') << "/" << std::string(sortedWords.size() - i - 1, '|') << "\n"; // Print histogram indicators
    }
}

// Function to display results
void displayResults(const DICTION &d) {
    // Display words in the dictionary
    std::cout << "Words in dictionary: ";
    for(const auto &word : d.words) {
        std::cout << word; // Print each word
        if(word != *d.words.rbegin()) std::cout << ", "; // Add a comma unless it's the last word
    }
    std::cout << "\n\n";

    // Display statistics
    std::cout << "Number of Letters : " << std::get<0>(d.stats) << '\n'; // Total letters
    std::cout << "Number of Words   : " << std::get<1>(d.stats) << '\n'; // Total words
    std::cout << "Number of Lines   : " << std::get<2>(d.stats) << '\n'; // Total lines
    std::cout << '\n';

    displayLetterFreq(d); // Display letter frequencies
    std::cout << '\n';
    displayHistogram(d); // Display histogram
}


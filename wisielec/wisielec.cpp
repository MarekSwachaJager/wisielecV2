#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <filesystem> // Do sprawdzania œcie¿ki

using namespace std;

// Function to load words from file with categories
map<string, vector<string>> loadWords(const string& filename) {
    map<string, vector<string>> categories;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filename << endl;
        return {};
    }

    string line, currentCategory;
    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line.front() == '[' && line.back() == ']') {
            // New category
            currentCategory = line.substr(1, line.length() - 2);
            categories[currentCategory] = {};
        }
        else if (!currentCategory.empty()) {
            // Add word to current category
            categories[currentCategory].push_back(line);
        }
    }

    file.close();
    return categories;
}

// Function to load high scores
vector<pair<string, int>> loadHighScores(const string& filename) {
    vector<pair<string, int>> scores;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "High scores file not found. A new one will be created." << endl;
        return scores;
    }
    string name;
    int score;
    while (file >> name >> score) {
        scores.emplace_back(name, score);
    }
    file.close();
    return scores;
}

// Function to save high scores
void saveHighScores(const string& filename, const vector<pair<string, int>>& scores) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not save high scores to file: " << filename << endl;
        return;
    }
    for (const auto& entry : scores) {
        file << entry.first << " " << entry.second << endl;
    }
    file.close();
}

// Function to get a random word
string getRandomWord(const vector<string>& words) {
    srand(static_cast<unsigned>(time(0)));
    return words[rand() % words.size()];
}

// Function to calculate the score
int calculateScore(int attemptsLeft, double timeTaken) {
    return attemptsLeft * 100 - static_cast<int>(timeTaken * 10);
}

// Main gameplay function
void playGame(const vector<string>& words, vector<pair<string, int>>& scores) {
    string word = getRandomWord(words);
    string guessed(word.length(), '_');
    int attempts = 6;
    bool won = false;
    clock_t start = clock();

    while (attempts > 0 && !won) {
        cout << "Word: " << guessed << endl;
        cout << "Remaining attempts: " << attempts << endl;
        cout << "Enter a letter: ";
        char guess;
        cin >> guess;

        bool found = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess && guessed[i] != guess) {
                guessed[i] = guess;
                found = true;
            }
        }

        if (!found) {
            attempts--;
            cout << "Incorrect guess! Attempts left: " << attempts << endl;
        }
        else {
            cout << "Correct guess!" << endl;
        }

        if (guessed == word) {
            won = true;
            cout << "Congratulations! You guessed the word: " << word << endl;
        }
    }

    if (!won) {
        cout << "You lost! The correct word was: " << word << endl;
    }

    clock_t end = clock();
    double timeTaken = double(end - start) / CLOCKS_PER_SEC;
    int score = calculateScore(attempts, timeTaken);

    cout << "Your score: " << score << endl;
    cout << "Enter your name: ";
    string playerName;
    cin >> playerName;

    scores.emplace_back(playerName, score);
    sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return b.second > a.second;
        });

    saveHighScores("high_scores.txt", scores);
}

int main() {
    // Pe³na œcie¿ka do pliku words.txt
    string wordFile = "C:\\Users\\Marek\\source\\repos\\wisielec\\x64\\Debug\\words.txt";
    cout << "Looking for words file at: " << wordFile << endl;

    auto categories = loadWords(wordFile);
    if (categories.empty()) {
        cerr << "Error: Word file is empty or does not exist!" << endl;
        return 1;
    }

    // Wyœwietlenie dostêpnych kategorii
    cout << "Available categories:" << endl;
    for (const auto& category : categories) {
        cout << "- " << category.first << endl;
    }

    // Wybór kategorii przez gracza
    string chosenCategory;
    cout << "Choose a category: ";
    cin >> chosenCategory;

    if (categories.find(chosenCategory) == categories.end()) {
        cerr << "Error: Invalid category!" << endl;
        return 1;
    }

    // Pobranie s³ów z wybranej kategorii
    vector<string> words = categories[chosenCategory];

    // High scores file (mo¿esz zmieniæ œcie¿kê, jeœli potrzebne)
    vector<pair<string, int>> scores = loadHighScores("high_scores.txt");

    playGame(words, scores);
    return 0;
}

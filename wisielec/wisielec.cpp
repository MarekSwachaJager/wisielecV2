
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

// Funkcja do wczytywania s³ów z pliku
std::vector<std::string> loadWords(const std::string & filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "B³¹d: Nie mo¿na otworzyæ pliku z list¹ s³ów: " << filename << std::endl;
        return words;
    }
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    return words;
}

// Funkcja do wczytywania listy najlepszych wyników
std::vector<std::pair<std::string, int>> loadHighScores(const std::string& filename) {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Brak pliku z wynikami: " << filename << " - wyniki zostan¹ utworzone po grze.\n";
        return scores;
    }
    std::string name;
    int score;
    while (file >> name >> score) {
        scores.emplace_back(name, score);
    }
    file.close();
    return scores;
}

// Funkcja do zapisywania najlepszych wyników do pliku
void saveHighScores(const std::string& filename, const std::vector<std::pair<std::string, int>>& scores) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "B³¹d: Nie mo¿na zapisaæ wyników do pliku: " << filename << std::endl;
        return;
    }
    for (const auto& entry : scores) {
        file << entry.first << " " << entry.second << std::endl;
    }
    file.close();
}

// Funkcja losuj¹ca s³owo z listy
std::string getRandomWord(const std::vector<std::string>& words) {
    srand(static_cast<unsigned>(time(0)));
    return words[rand() % words.size()];
}

// Funkcja do obliczania punktów
int calculateScore(int attemptsLeft, double timeTaken) {
    return attemptsLeft * 100 - static_cast<int>(timeTaken * 10);
}

// Funkcja obs³uguj¹ca rozgrywkê
void playGame(const std::vector<std::string>& words, std::vector<std::pair<std::string, int>>& scores) {
    std::string word = getRandomWord(words);
    std::string guessed(word.length(), '_');
    int attempts = 6;
    bool won = false;
    clock_t start = clock();

    while (attempts > 0 && !won) {
        std::cout << "Has³o: " << guessed << "\n";
        std::cout << "Pozosta³e próby: " << attempts << "\n";
        std::cout << "Podaj literê: ";
        char guess;
        std::cin >> guess;

        bool found = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess && guessed[i] != guess) {
                guessed[i] = guess;
                found = true;
            }
        }

        if (!found) {
            attempts--;
            std::cout << "B³êdna litera! Straci³eœ próbê.\n";
        }
        else {
            std::cout << "Trafiona litera!\n";
        }

        if (guessed == word) {
            won = true;
            std::cout << "Brawo! Odgad³eœ s³owo: " << word << "\n";
        }
    }

    if (!won) {
        std::cout << "Przegra³eœ! Szukane s³owo to: " << word << "\n";
    }

    clock_t end = clock();
    double timeTaken = double(end - start) / CLOCKS_PER_SEC;
    int score = calculateScore(attempts, timeTaken);

    std::cout << "Twoje punkty: " << score << "\nPodaj swoje imiê: ";
    std::string playerName;
    std::cin >> playerName;

    scores.emplace_back(playerName, score);
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return b.second > a.second;
        });

    saveHighScores("high_scores.txt", scores);
}

// G³ówna funkcja programu
int main() {
    std::vector<std::string> words = loadWords("words.txt");
    if (words.empty()) {
        std::cerr << "B³¹d: Plik z list¹ s³ów jest pusty lub nie istnieje!\n";
        return 1;
    }

    std::vector<std::pair<std::string, int>> scores = loadHighScores("high_scores.txt");

    playGame(words, scores);
    return 0;
}
"""

# Zapisanie kodu do pliku
file_path_corrected = '/mnt/data/hangman_game_corrected.cpp'
with open(file_path_corrected, 'w') as file :
file.write(corrected_code)

file_path_corrected

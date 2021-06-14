#include <iostream>
#include <fstream>


using namespace std;

void display(string word, const bool openLetters[], size_t n) {
    cout << "What is it?" << endl;
    for (int i = 0; i < n; i++) {
        if (openLetters[i]) {
            cout << word.at(i);
        } else {
            cout << "_";
        }
        cout << " ";
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));
    char number = rand() % 10;

    string word;
    ifstream file("/home/vladimir/ClionProjects/words.txt");
    for (int i = 0; i < number; i++) {
        getline(file, word);
    }
    file.close();

    size_t n = word.length();
    bool openLetters[n];

    // открываем 2 буквы
    char a = word[rand() % n];
    char b = word[rand() % n];
    while (b == a) {
        b = word[rand() % n];
    }
    for (int i = 0; i < n; i++) {
        openLetters[i] = word[i] == a || word[i] == b;
    }

    // игра
    int countClosedLetters = 0;
    for (int i = 0; i < n; i++) {
        if (!openLetters[i]) {
            countClosedLetters++;
        }
    }
    display(word, openLetters, n);
    int countLives = 6;
    while (countLives && countClosedLetters) {
        cout << "Input letter (" << countLives << "): ";
        char letter;
        cin >> letter;
        bool newLetter = false;
        for (int i = 0; i < n; i++) {
            if (word[i] == letter && !openLetters[i]) {
                openLetters[i] = true;
                newLetter = true;
            }
        }
        display(word, openLetters, n);
        if (!newLetter) {
            countLives--;
        }
        countClosedLetters = 0;
        for (int i = 0; i < n; i++) {
            if (!openLetters[i]) {
                countClosedLetters++;
            }
        }
    }

    if (countLives) {
        cout << "Win!" << endl;
    } else {
        cout << "Loss!" << endl;
    }

    return 0;
}

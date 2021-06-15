#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

class Word {

public:
    explicit Word(const string &word) {
        this->str = word;
        this->n = int(word.length());
        for (int i = 0; i < n; i++) {
            this->openLetters.push_back(false);
        }
    }

    int n;
    vector<bool> openLetters;
    string str;
};

int randomInt(int n) {
    return rand() % n;
}

string selectWordFromFile() {
    int number = randomInt(10);
    string str;
    ifstream file("/home/vladimir/ClionProjects/words.txt");
    for (int i = 0; i < number; i++) {
        getline(file, str);
    }
    file.close();
    return str;
}

int calcCountClosedLetters(const Word &w) {
    int countClosedLetters = 0;
    for (int i = 0; i < w.n; i++) {
        if (!w.openLetters[i]) {
            countClosedLetters++;
        }
    }
    return countClosedLetters;
}

bool runGame(int countLives, int countClosedLetters) {
    return countLives && countClosedLetters;
}

bool step(char letter, Word w) {
    bool newLetter = false;
    for (int i = 0; i < w.n; i++) {
        if (w.str[i] == letter && !w.openLetters[i]) {
            w.openLetters[i] = true;
            newLetter = true;
        }
    }
    return newLetter;
}

void displayGame(Word w) {
    cout << "What is it?" << endl;
    for (int i = 0; i < w.n; i++) {
        if (w.openLetters[i]) {
            cout << w.str.at(i);
        } else {
            cout << "_";
        }
        cout << " ";
    }
    cout << endl;
}

void displayEnd(int countLives) {
    if (countLives) {
        cout << "Win!" << endl;
    } else {
        cout << "Loss!" << endl;
    }
}

char inputLetter() {
    char letter;
    cout << "Input letter: ";
    cin >> letter;
    return letter;
}

int main() {
    srand(time(nullptr));
    string str = selectWordFromFile();
    Word w(str);
    int countLives = 6;

    char a = w.str[randomInt(w.n)];
    char b = w.str[randomInt(w.n)];
    while (b == a) {
        b = w.str[randomInt(w.n)];
    }
    for (int i = 0; i < w.n; i++) {
        w.openLetters[i] = w.str[i] == a || w.str[i] == b;
    }

    int countClosedLetters = calcCountClosedLetters(w);
    displayGame(w);
    while (runGame(countLives, countClosedLetters)) {
        char letter = inputLetter();
        bool newLetter = step(letter, w);
        if (!newLetter) {
            countLives--;
        }
        countClosedLetters = calcCountClosedLetters(w);
        displayGame(w);
    }
    displayEnd(countLives);

    return 0;
}

#include <iostream>
#include <fstream>


using namespace std;

class Word {

public:
    explicit Word(const string &word) {
        this->str = word;
        this->n = word.length();
        this->openLetters = new bool[n]();
    }

    size_t n;
    bool *openLetters;
    string str;
};

void display(Word w) {
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

int calcCountClosedLetters(const Word &w) {
    int countClosedLetters = 0;
    for (int i = 0; i < w.n; i++) {
        if (!w.openLetters[i]) {
            countClosedLetters++;
        }
    }
    return countClosedLetters;
}

string selectWordFromFile() {
    int number = rand() % 10;
    string str;
    ifstream file("/home/vladimir/ClionProjects/words.txt");
    for (int i = 0; i < number; i++) {
        getline(file, str);
    }
    file.close();
    return str;
}

int main() {
    srand(time(nullptr));
    string str = selectWordFromFile();
    Word w(str);

    // открываем 2 буквы
    char a = w.str[rand() % w.n];
    char b = w.str[rand() % w.n];
    while (b == a) {
        b = w.str[rand() % w.n];
    }
    for (int i = 0; i < w.n; i++) {
        w.openLetters[i] = w.str[i] == a || w.str[i] == b;
    }

    // игра
    int countClosedLetters = calcCountClosedLetters(w);
    display(w);
    int countLives = 6;
    while (countLives && countClosedLetters) {
        cout << "Input letter (" << countLives << "): ";
        char letter;
        cin >> letter;
        bool newLetter = false;
        for (int i = 0; i < w.n; i++) {
            if (w.str[i] == letter && !w.openLetters[i]) {
                w.openLetters[i] = true;
                newLetter = true;
            }
        }
        display(w);
        if (!newLetter) {
            countLives--;
        }
        countClosedLetters = calcCountClosedLetters(w);
    }

    if (countLives) {
        cout << "Win!" << endl;
    } else {
        cout << "Loss!" << endl;
    }

    return 0;
}

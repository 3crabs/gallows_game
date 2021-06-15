#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

/**
 * слово для игры
 */
class Word {

public:
    /**
     * конструктор слова
     * @param word слово для игры
     */
    explicit Word(const string &word) {
        this->str = word;
        this->n = int(word.length());
        for (int i = 0; i < n; i++) {
            this->openLetters.push_back(false);
        }
    }

    /**
     * количество букв в слове
     */
    int n;

    /**
     * вектор для хранения признаков открытости букв
     */
    vector<bool> openLetters;

    /**
     * загаданное слово
     */
    string str;
};

/**
 * создание случайного целого числа от 0 до n
 * @param n верхняя граница требуемого числа, целое число больше 0
 * @return целое число от 0 до n
 */
int randomInt(int n) {
    return rand() % n;
}

/**
 * выбор слова из файла-словаря words.txt
 * @return строка - слово
 */
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

/**
 * подсчет количества закрытых букв
 * @param w слово типа Word
 * @return количества закрытых букв в слове
 */
int calcCountClosedLetters(const Word &w) {
    int countClosedLetters = 0;
    for (int i = 0; i < w.n; i++) {
        if (!w.openLetters[i]) {
            countClosedLetters++;
        }
    }
    return countClosedLetters;
}

/**
 * проверка продолжения игры
 * @param countLives количество оставшихся жизней, число от 0 до 6
 * @param countClosedLetters количество закрытых букв в слове
 * @return признак продолжения игры
 */
bool runGame(int countLives, int countClosedLetters) {
    return countLives && countClosedLetters;
}

/**
 * ход игры
 * @param letter буква которую ввел пользователь
 * @param w слово типа Word
 * @return признак успеха игрока
 */
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

/**
 * вывод текущего состояния игры
 * @param w слово типа Word
 */
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

/**
 * вывод окончания игры
 * @param countLives количество оставшихся жизней игрока
 */
void displayEnd(int countLives) {
    if (countLives) {
        cout << "Win!" << endl;
    } else {
        cout << "Loss!" << endl;
    }
}

/**
 * ввод буквы
 * @return буква которую ввел пользователь
 */
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

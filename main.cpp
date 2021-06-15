#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

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
bool step(char letter, Word &w) {
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
string createDisplayString(Word w) {
    string s;
    for (int i = 0; i < w.n; i++) {
        if (w.openLetters[i]) {
            s += w.str.at(i);
        } else {
            s += "_";
        }
        s += " ";
    }
    return s;
}

/**
 * тестируем
 */
void test() {
    assert(runGame(0, 0) == false);
    assert(runGame(1, 0) == false);
    assert(runGame(0, 1) == false);
    assert(runGame(1, 1) == true);
    cout << "tests runGame ok" << endl;

    Word w1("toy");
    assert(calcCountClosedLetters(w1) == 3);
    w1.openLetters[0] = true;
    assert(calcCountClosedLetters(w1) == 2);
    w1.openLetters[1] = true;
    assert(calcCountClosedLetters(w1) == 1);
    w1.openLetters[2] = true;
    assert(calcCountClosedLetters(w1) == 0);
    cout << "tests calcCountClosedLetters ok" << endl;

    Word w2("toy");
    assert(calcCountClosedLetters(w2) == 3);
    assert(step('t', w2) == true);
    assert(calcCountClosedLetters(w2) == 2);
    assert(step('t', w2) == false);
    assert(calcCountClosedLetters(w2) == 2);
    assert(step('o', w2) == true);
    assert(calcCountClosedLetters(w2) == 1);
    assert(step('y', w2) == true);
    assert(calcCountClosedLetters(w2) == 0);
    cout << "tests step ok" << endl;

    Word w3("toy");
    assert(createDisplayString(w3) == "_ _ _ ");
    w3.openLetters[1] = true;
    assert(createDisplayString(w3) == "_ o _ ");
    w3.openLetters[2] = true;
    assert(createDisplayString(w3) == "_ o y ");
    w3.openLetters[0] = true;
    assert(createDisplayString(w3) == "t o y ");
    cout << "tests createDisplayString ok" << endl;
}

/**
 * играем
 */
void game() {
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

    RenderWindow window(VideoMode(400, 300), "gallows_game");

    Font font;
    if (!font.loadFromFile("/home/vladimir/ClionProjects/arial.ttf")) {
        exit(1);
    }

    Text livesText;
    livesText.setFont(font);
    livesText.setFillColor(sf::Color::Black);
    livesText.setString("lives: " + to_string(countLives));
    livesText.setPosition(Vector2f(10, 10));

    Text textQuestion;
    textQuestion.setFont(font);
    textQuestion.setFillColor(sf::Color::Black);
    textQuestion.setString("What is it?");
    FloatRect textRect = textQuestion.getLocalBounds();
    textQuestion.setOrigin(textRect.width / 2, textRect.height / 2);
    textQuestion.setPosition(Vector2f(float(window.getSize().x) / 2.0f, float(window.getSize().y) / 4.0f));

    Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString(createDisplayString(w));
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2, textRect.height / 2);
    text.setPosition(Vector2f(float(window.getSize().x) / 2.0f, float(window.getSize().y) / 2.0f));

    Text textTab;
    textTab.setFont(font);
    textTab.setFillColor(sf::Color::Black);
    textTab.setString("tab any letter");
    textRect = textTab.getLocalBounds();
    textTab.setOrigin(textRect.width / 2, textRect.height / 2);
    textTab.setPosition(Vector2f(float(window.getSize().x) / 2.0f, float(window.getSize().y) / 4.0f * 3.0f));

    int countClosedLetters = calcCountClosedLetters(w);
    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyReleased) {
                Keyboard::Key keycode = event.key.code;
                if (keycode >= Keyboard::A && keycode <= Keyboard::Z) {
                    char letter = static_cast<char>(keycode - Keyboard::A + 'a');
                    bool newLetter = step(letter, w);
                    text.setString(createDisplayString(w));
                    textRect = text.getLocalBounds();
                    text.setOrigin(textRect.width / 2, textRect.height / 2);
                    text.setPosition(Vector2f(float(window.getSize().x) / 2.0f, float(window.getSize().y) / 2.0f));
                    if (!newLetter) {
                        countLives--;
                    }
                    countClosedLetters = calcCountClosedLetters(w);
                    if (!runGame(countLives, countClosedLetters)) {
                        if (countLives) {
                            textTab.setString("WIN!!!");
                        } else {
                            textTab.setString("LOSE!!!");
                        }
                        textRect = textTab.getLocalBounds();
                        textTab.setOrigin(textRect.width / 2, textRect.height / 2);
                        textTab.setPosition(
                                Vector2f(float(window.getSize().x) / 2.0f, float(window.getSize().y) / 4.0f * 3.0f));
                    }
                    livesText.setString("lives: " + to_string(countLives));
                }
            }
        }

        window.clear(Color::White);
        window.draw(livesText);
        window.draw(textQuestion);
        window.draw(text);
        window.draw(textTab);
        window.display();
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2 && string(argv[1]) == "test") {
        test();
    } else {
        game();
    }
    return 0;
}

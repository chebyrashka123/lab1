#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

// ============================================================
// ВЫБОР РЕАЛИЗАЦИИ:
// Раскомментируйте ОДНУ из строк ниже:
// ============================================================
//#define USE_PUBLIC_VERSION
#define USE_PRIVATE_VERSION
// ============================================================

#ifdef USE_PUBLIC_VERSION
// ----------- Прямой доступ к полям (public) -----------
struct Book {
    string author;
    string title;
    string publisher;
    int year;
    int pages;

    // Метод подсчёта возраста книги
    int getAge() const {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        int currentYear = now->tm_year + 1900;
        return currentYear - year;
    }
};

// Функция загрузки из файла
bool loadBooks(const string& filename, vector<Book>& books) {
    ifstream fin(filename);
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        Book b;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        if (p1 == string::npos || p2 == string::npos || p3 == string::npos || p4 == string::npos)
            continue;
        b.author = line.substr(0, p1);
        b.title = line.substr(p1 + 1, p2 - p1 - 1);
        b.publisher = line.substr(p2 + 1, p3 - p2 - 1);
        b.year = stoi(line.substr(p3 + 1, p4 - p3 - 1));
        b.pages = stoi(line.substr(p4 + 1));
        books.push_back(b);
    }
    fin.close();
    return true;
}

// Функции вывода
void printByAuthor(const vector<Book>& books, const string& author) {
    cout << "\nКниги автора " << author << ":\n";
    bool found = false;
    for (const auto& b : books)
        if (b.author == author) {
            cout << "  " << b.title << ", " << b.publisher << ", " << b.year << ", " << b.pages << " стр., возраст " << b.getAge() << " лет\n";
            found = true;
        }
    if (!found) cout << "  Нет книг этого автора.\n";
}

void printByPublisher(const vector<Book>& books, const string& publisher) {
    cout << "\nКниги издательства " << publisher << ":\n";
    bool found = false;
    for (const auto& b : books)
        if (b.publisher == publisher) {
            cout << "  " << b.author << " - \"" << b.title << "\", " << b.year << "\n";
            found = true;
        }
    if (!found) cout << "  Нет книг этого издательства.\n";
}

void printAfterYear(const vector<Book>& books, int year) {
    cout << "\nКниги, выпущенные после " << year << " года:\n";
    bool found = false;
    for (const auto& b : books)
        if (b.year > year) {
            cout << "  \"" << b.title << "\" (" << b.year << "), " << b.author << "\n";
            found = true;
        }
    if (!found) cout << "  Нет таких книг.\n";
}

#endif // USE_PUBLIC_VERSION

// ============================================================

#ifdef USE_PRIVATE_VERSION
// ----------- Закрытые поля + методы get/set/show -----------
class Book {
private:
    string author;
    string title;
    string publisher;
    int year;
    int pages;

public:
    // Конструктор по умолчанию
    Book() : author(""), title(""), publisher(""), year(0), pages(0) {}

    // Сеттеры
    void setAuthor(const string& a) { author = a; }
    void setTitle(const string& t) { title = t; }
    void setPublisher(const string& p) { publisher = p; }
    void setYear(int y) { year = y; }
    void setPages(int p) { pages = p; }

    // Геттеры
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    string getPublisher() const { return publisher; }
    int getYear() const { return year; }
    int getPages() const { return pages; }

    // Метод подсчёта возраста
    int getAge() const {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        int currentYear = now->tm_year + 1900;
        return currentYear - year;
    }

    // Метод show для вывода информации об объекте
    void show() const {
        cout << "Книга: \"" << title << "\" (" << year << "), автор " << author
            << ", изд. " << publisher << ", " << pages << " стр., возраст " << getAge() << " лет";
    }
};

// Функция загрузки из файла
bool loadBooks(const string& filename, vector<Book>& books) {
    ifstream fin(filename);
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        Book b;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        if (p1 == string::npos || p2 == string::npos || p3 == string::npos || p4 == string::npos)
            continue;
        b.setAuthor(line.substr(0, p1));
        b.setTitle(line.substr(p1 + 1, p2 - p1 - 1));
        b.setPublisher(line.substr(p2 + 1, p3 - p2 - 1));
        b.setYear(stoi(line.substr(p3 + 1, p4 - p3 - 1)));
        b.setPages(stoi(line.substr(p4 + 1)));
        books.push_back(b);
    }
    fin.close();
    return true;
}

// Функции вывода (используют get-методы)
void printByAuthor(const vector<Book>& books, const string& author) {
    cout << "\nКниги автора " << author << ":\n";
    bool found = false;
    for (const auto& b : books)
        if (b.getAuthor() == author) {
            cout << "  ";
            b.show();
            cout << endl;
            found = true;
        }
    if (!found) cout << "  Нет книг этого автора.\n";
}

void printByPublisher(const vector<Book>& books, const string& publisher) {
    cout << "\nКниги издательства " << publisher << ":\n";
    bool found = false;
    for (const auto& b : books)
        if (b.getPublisher() == publisher) {
            cout << "  ";
            b.show();
            cout << endl;
            found = true;
        }
    if (!found) cout << "  Нет книг этого издательства.\n";
}

void printAfterYear(const vector<Book>& books, int year) {
    cout << "\nКниги, выпущенные после " << year << " года:\n";
    bool found = false;
    for (const auto& b : books)
        if (b.getYear() > year) {
            cout << "  \"" << b.getTitle() << "\" (" << b.getYear() << "), " << b.getAuthor() << "\n";
            found = true;
        }
    if (!found) cout << "  Нет таких книг.\n";
}

#endif // USE_PRIVATE_VERSION

// ============================================================
// Главная функция
// ============================================================
int main() {
    // Устанавливаем кодировку консоли для правильного отображения русского текста
    system("chcp 1251 > nul");

    vector<Book> books;
    if (!loadBooks("books.txt", books)) {
        cerr << "Ошибка: файл books.txt не найден или не удалось загрузить данные.\n";
        cerr << "Пожалуйста, создайте файл books.txt в папке с программой.\n";
        cerr << "Формат строки: автор|название|издательство|год|страницы\n";
        cerr << "Пример:\n";
        cerr << "Оруэлл|1984|Секкер и Варбург|1949|328\n";
        return 1;
    }

    cout << "Загружено книг: " << books.size() << "\n";

    // Вывод трёх списков согласно заданию
    printByAuthor(books, "Оруэлл");
    printByPublisher(books, "Блумсбери");
    printAfterYear(books, 1950);

    return 0;
}
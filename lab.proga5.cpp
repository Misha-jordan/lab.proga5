
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Header.h"


void add_func();
void view_func();
void delete_func();
void search_func(std::string key);
void edit_func();
void menu();

int main()
{
    setlocale(LC_ALL, "rus");
    std::string word, line;
    unsigned cnt{};
    std::cout << "Введите слово, кол-во которого вы хотите посчитать: " << "\n";
    std::cin >> word;
    std::ifstream file("file1.txt");

    if (file.is_open()) {
        std::getline(file, line);
        for (unsigned i{}; i <= line.length() - word.length(); ++i) {
            size_t position = line.find(word, i);
            if (position == std::string::npos) break;
            ++cnt;
            i = position + word.length() - 1;
        }
    }

    std::cout << cnt << "\n";
    file.close();

    matrix<float> mat(3, 3);
    mat.random();

    std::ofstream f("file2.txt");

    if (f.is_open()) {
        f << mat;
        std::cout << "Запись матрицы в файл завершена" << "\n";
    }

    f.close();

    menu();
}


void menu() {
    unsigned choice = 0;
    while (choice != 6) {
        std::cout << "Выберите для дальнейшего действия: " << "\n";
        std::cout << "1 - Добавить новую запись в файл" << "\n";
        std::cout << "2 - Просмотр всех существующих записей в файле" << "\n";
        std::cout << "3 - Удаление записи из файла" << "\n";
        std::cout << "4 - Поиск записи в файле" << "\n";
        std::cout << "5 - Редактирование записи в файле" << "\n";
        std::cout << "6 - Выход из меню" << "\n";
        std::cin >> choice;

        std::string key;
        switch (choice)
        {
        case 1:
            add_func();
            break;
        case 2:
            view_func();
            break;
        case 3:
            delete_func();
            break;
        case 4:
            std::cout << "Введите номер искомой записи: " << "\n";
            std::cin >> key;
            search_func(key);
            break;
        case 5:
            edit_func();
            break;
        case 6:
            break;
        }
    }
}

void add_func() {
    std::ofstream file("file3.txt", std::ios_base::app);
    std::string new_entry;
    std::cout << "Введите новую запись: ";
    std::cin >> new_entry;
    file << new_entry << "\n";
    std::cout << "Новая запись добавлена в файл." << "\n";
    file.close();
}

void view_func() {
    std::ifstream file("file3.txt");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
    }

    file.close();
}

void delete_func() {
    std::ifstream inFile("file3.txt");
    std::ofstream outFile("temp.txt");
    std::string line, key;
    std::cout << "Введите номер записи для удаления: " << "\n";
    std::cin >> key;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            if (line.find(key) == std::string::npos) {
                outFile << line << std::endl;
            }
        }
    }

    inFile.close();
    outFile.close();

    std::remove("file3.txt");
    std::rename("temp.txt", "file3.txt");

    std::cout << "" << "\n";
}

void search_func(std::string key) {
    std::ifstream file("file3.txt");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            size_t pos = line.find(key);
            if (pos != std::string::npos) {
                std::cout << line << "\n";
            }
        }
    }

    file.close();
}

void edit_func() {
    std::string key;
    std::cout << "Введите номер записи для изменения: ";
    std::cin >> key;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::ifstream inFile("file3.txt");
    std::ofstream outFile("temp.txt");

    if (!inFile || !outFile) {
        std::cerr << "Ошибка открытия файлов." << std::endl;
        return;
    }

    std::string line;
    int currentPos = 0;
    while (std::getline(inFile, line)) {
        if (currentPos == std::stoi(key)) {
            std::string new_entry;
            std::cout << "Введите новое значение для записи: ";
            std::getline(std::cin, new_entry);
            outFile << new_entry << std::endl;
        }
        else {
            outFile << line << std::endl;
        }
        currentPos++;
    }

    inFile.close();
    outFile.close();

    std::remove("file3.txt");
    std::rename("temp.txt", "file3.txt");

    std::cout << "Запись успешно отредактирована." << "\n";
}
    


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
void add_func();
void view_func();
void delete_func();
void search_func(std::string key);
void edit_func();
void menu();

int main() {
    setlocale(LC_ALL, "Russian");
    // Пример использования функций
    string word, line;
    unsigned cnt {};
    cout<<"Введите слово, число которого вы хотите посчитать" <<"\n";
    cin>>word;
    ifstream file("laba.txt");

     if (file.is_open()) {
            getline(file, line);
        for (unsigned i {}; i <= line.length() - word.length(); ++i) {
            size_t position = line.find(word, i);
            if (position == std::string::npos) break;
            ++cnt;
            i = position + word.length() - 1;
        }


    cout << cnt << "\n ";
         file.close();

     matrix<float> mat(3, 3);
    mat.random();

    std::ofstream f("laba(1).txt");

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
        cout << "Выберите для дальнейшего действия: " << "\n";
        cout << "1 - Добавить новую запись в файл" << "\n";
        cout << "2 - Просмотр всех существующих записей в файле" << "\n";
        cout << "3 - Удаление записи из файла" << "\n";
        cout << "4 - Поиск записи в файле" << "\n";
        cout << "5 - Редактирование записи в файле" << "\n";
        cout << "6 - Выход из меню" << "\n";
        cin >> choice;

        string key;
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
            cout << "Введите номер искомой записи: " << "\n";
            cin >> key;
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
    ofstream file("laba(2).txt", std::ios_base::app);
    string new_entry;
    cout << "Введите новую запись: ";
    cin >> new_entry;
    file << new_entry << "\n";
    cout << "Новая запись добавлена в файл." << "\n";
    file.close();
}

void view_func() {
    ifstream file("laba(2).txt");
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << "\n";
        }
    }

    file.close();
}

void delete_func() {
    ifstream inFile("laba(2).txt");
    ofstream outFile("temp.txt");
    string line, key;
    cout << "Введите номер записи для удаления: " << "\n";
    cin >> key;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (line.find(key) == string::npos) {
                outFile << line << endl;
            }
        }
    }

    inFile.close();
    outFile.close();

    remove("laba(2).txt");
    rename("temp.txt", "laba(2).txt");

    cout << "" << "\n";
}

void search_func(string key) {
    ifstream file("laba(2).txt");
    string line;

    if (file.is_open()) {
        while (getline(file, line)) { 
            size_t pos = line.find(key); 
            if (pos != string::npos) {
                std::cout << line << "\n";
            }
        }
    }

    file.close();
}

void edit_func() {
    string key;
    cout << "Введите номер записи для изменения: ";
    cin >> key;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    ifstream inFile("laba(2).txt");
    ofstream outFile("temp.txt");

    if (!inFile || !outFile) {
        cerr << "Ошибка открытия файлов." << endl;
        return;
    }

    string line;
    int currentPos = 0;
    while (getline(inFile, line)) {
        if (currentPos == stoi(key)) {
            string new_entry;
            cout << "Введите новое значение для записи: ";
            getline(cin, new_entry);
            outFile << new_entry << endl;
        }
        else {
            outFile << line << endl;
        }
        currentPos++;
    }

    inFile.close();
    outFile.close();

    remove("laba(2).txt");
    rename("temp.txt", "laba(2).txt");

    cout << "Запись успешно отредактирована." << "\n";
}
    
    // Заполнение матриц данными
    matrices[0].data = { {1, 2}, {3, 4} };
    matrices[1].data = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    // Запись и чтение из текстового файла
    writeMatricesToTextFile("matrices.txt", matrices);
    vector<Matrix> matricesFromText = readMatricesFromTextFile("matrices.txt");

    // Запись и чтение из бинарного файла
    writeMatricesToBinaryFile("matrices.bin", matrices);
    vector<Matrix> matricesFromBinary = readMatricesFromBinaryFile("matrices.bin");

    return 0;
}




// Структура для представления матрицы
struct Matrix {
    int rows;
    int cols;
    vector<vector<double>> data;
    // Конструктор
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<double>(c)) {}
};

// Функция для подсчета слов в файле
int countWords(const string& filename, const string& word) {
    ifstream file(filename);
    string currentWord;
    int count = 0;

    while (file >> currentWord) {
        if (currentWord == word) {
            count++;
        }
    }

    return count;
}

// Функция для записи матриц в текстовый файл
void writeMatricesToTextFile(const string& filename, const vector<Matrix>& matrices) {
    ofstream file(filename);

    for (const Matrix& matrix : matrices) {
        file << matrix.rows << " " << matrix.cols << endl;
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                file << matrix.data[i][j] << " ";
            }
            file << endl;
        }
        file << endl;
    }
}

// Функция для чтения матриц из текстового файла
vector<Matrix> readMatricesFromTextFile(const string& filename) {
    ifstream file(filename);
    vector<Matrix> matrices;

    int rows, cols;
    while (file >> rows >> cols) {
        Matrix matrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> matrix.data[i][j];
            }
        }
        matrices.push_back(matrix);
    }

    return matrices;
}

// Функция для записи матриц в бинарный файл
void writeMatricesToBinaryFile(const string& filename, const vector<Matrix>& matrices) {
    ofstream file(filename, ios::binary);

    for (const Matrix& matrix : matrices) {
        file.write(reinterpret_cast<const char*>(&matrix.rows), sizeof(matrix.rows));
        file.write(reinterpret_cast<const char*>(&matrix.cols), sizeof(matrix.cols));
        for (int i = 0; i < matrix.rows; ++i) {
            file.write(reinterpret_cast<const char*>(matrix.data[i].data()), matrix.cols * sizeof(double));
        }
    }
}

// Функция для чтения матриц из бинарного файла
vector<Matrix> readMatricesFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    vector<Matrix> matrices;

    int rows, cols;
    while (file.read(reinterpret_cast<char*>(&rows), sizeof(rows)) &&
        file.read(reinterpret_cast<char*>(&cols), sizeof(cols))) {
        Matrix matrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
            file.read(reinterpret_cast<char*>(matrix.data[i].data()), cols * sizeof(double));
        }
        matrices.push_back(matrix);
    }

    return matrices;
}


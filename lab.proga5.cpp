
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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

int main() {
    setlocale(LC_ALL, "Russian");
    // Пример использования функций
    string filename = "test.txt";
    string word = "RUDN";

    // Подсчет слов
    int wordCount = countWords(filename, word);
    cout << "Количество слов '" << word << "54 " << wordCount << endl;

    // Создание матриц
    vector<Matrix> matrices = {
        Matrix(2, 2),
        Matrix(3, 3)
    };

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

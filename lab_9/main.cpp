#include <cstddef>
#include <iostream>
#include <stdexcept>

class Matrix {
private:
    static const size_t maxSize = 100;

    size_t rows;
    size_t columns;
    int data[maxSize][maxSize]{};

public:

    explicit Matrix(size_t n = 0, size_t m = 0) : rows(n), columns(m) {
    }

    size_t getRows() const { return rows; }
    size_t getColumns() const { return columns; }

    int &operator()(size_t i, size_t j) {
        return data[i][j];
    }

    const int &operator()(size_t i, size_t j) const {
        return data[i][j];
    }

    int* operator()(size_t i) {
        return data[i];
    }

    const int* operator()(size_t i) const {
        return data[i];
    }

    void matrixInput();

    void matrixOutput() const;

    Matrix transpose() const;
};

void Matrix::matrixInput() {
    for (size_t i = 0; i < getRows(); ++i)
        for (size_t j = 0; j < getColumns(); ++j)
            std::cin >> (*this)(i, j);
}

void Matrix::matrixOutput() const {
    for (size_t i = 0; i < getRows(); ++i) {
        for (size_t j = 0; j < getColumns(); ++j)
            std::cout << (*this)(i, j) << " ";
        std::cout << std::endl;
    }
}

Matrix Matrix::transpose() const {
    Matrix res(this->getRows(), this->getColumns());

    for (size_t i = 0; i < this->getRows(); ++i)
        for (size_t j = 0; j < this->getColumns(); ++j)
            res(j, i) = (*this)(i, j);

    return res;
}

Matrix matrixMultASM(const Matrix &mat1, const Matrix &mat2) {
    if (mat1.getColumns() != mat2.getRows()) throw std::invalid_argument("Incorrect sizes for matrix multiplication");

    Matrix result(mat1.getRows(), mat2.getColumns());
    Matrix transposeMatrix2 = mat2.transpose();

    for (size_t i = 0; i < result.getRows(); ++i) {
        for (size_t k = 0; k < result.getColumns(); ++k) {
            int multSum = 0;
            for (size_t j = 0; j < mat1.getColumns(); j += 4) {
                if (mat1.getColumns() - j >= 4) {
                    __asm__ (
                            "movdqu (%[first]), %%xmm0   \n" // Загружаем 4 элемента из строки mat1 в xmm0
                            "movdqu (%[second]), %%xmm1  \n" // Загружаем 4 элемента из строки transposeMatrix2 в xmm1
                            "pmullw  %%xmm1, %%xmm0      \n" // Перемножаем элементы (попарно) из xmm0 и xmm1
                            "phaddd %%xmm0, %%xmm0       \n" // Складываем пары элементов в xmm0 (горизонтально)
                            "phaddd %%xmm0, %%xmm0       \n" // Складываем оставшиеся элементы в xmm0 (горизонтально)

                            "movd %%xmm0, %%edx          \n" // Перемещаем результат из xmm0 в edx
                            "addl %%edx, %[sum_el]       \n" // Добавляем результат к multSum
                            : [sum_el]"+m"(multSum)
                    : [first]"r"(mat1(i) + j), [second]"r"(transposeMatrix2(k) + j)
                    : "%rdi", "%rsi"
                    );
                } else {
                    for (size_t _j = j; _j < mat1.getColumns(); ++_j) {
                        __asm__ (
                                "movl   %[first_el], %%eax \n"
                                "movl   %[second_el], %%ebx \n"
                                "imull  %%eax, %%ebx     \n"
                                "addl   %%ebx, %[sum_el] \n"
                                : [sum_el]"+r"(multSum)
                        : [first_el]"r"(mat1(i, _j)), [second_el]"r"(transposeMatrix2(k, _j))
                        : "%rax", "%rbx"
                        );
                    }
                }
            }
            result(i, k) = multSum;
        }
    }

    return result;
}

int main() {
    size_t n, m;
    std::cout << "Введите размеры первой матрицы: ";
    std::cin >> n >> m;
    Matrix matrix1(n, m);
    std::cout << "Введите матрицу:\n";
    matrix1.matrixInput();

    std::cout << "Введите размеры второй матрицы: ";
    std::cin >> n >> m;
    Matrix matrix2(n, m);
    std::cout << "Введите матрицу:\n";
    matrix2.matrixInput();

    try {
        Matrix multResult = matrixMultASM(matrix1, matrix2);
        std::cout << "Результат умножения:\n";
        multResult.matrixOutput();
    } catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

#include <vector>
#include <iostream>
#include <random>
#include <limits>

void sosedi(size_t row, int cols, std::vector<int>& puti, const std::vector<std::vector<int>>& matrix) {
    for (size_t i = 0; i < cols; i++) {
        if (matrix[row][i] != 0 && puti[row] + matrix[row][i] < puti[i]) {
            puti[i] = puti[row] + matrix[row][i];
        }
    }
}

void dijkstra(int start, int end, const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    std::vector<int> puti(n, std::numeric_limits<int>::max());
    std::vector<bool> visit(n, false);

    puti[start] = 0;

    for (int i = 0; i < n; i++) {
        int k = -1;
        for (int j = 0; j < n; j++) {
            if (!visit[j] && (k == -1 || puti[k] > puti[j])) {
                k = j;
            }
        }
        if (k == -1 || puti[k] == std::numeric_limits<int>::max()) {
            break;
        }
        visit[k] = true;
        sosedi(k, n, puti, matrix);
    }

    if (puti[end] == std::numeric_limits<int>::max()) {
        std::cout << "Путь из " << start << " в " << end << " не найден." << std::endl;
    }
    else {
        std::cout << "Кратчайшее расстояние из " << start << " в " << end << " равно " << puti[end] << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 20);

    int n;
    std::cout << "Введите размер матрицы: ";
    std::cin >> n;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            matrix[i][j] = matrix[j][i] = dist(gen);
        }
    }

    std::cout << "Сгенерированная матрица смежности:" << std::endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    int start, end;
    std::cout << "Введите начальную точку (от 0 до " << n - 1 << "): ";
    std::cin >> start;
    std::cout << "Введите конечную точку (от 0 до " << n - 1 << "): ";
    std::cin >> end;



    dijkstra(start, end, matrix);

    return 0;
}
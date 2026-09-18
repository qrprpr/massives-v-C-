#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MIN_DIM 2
#define MAX_DIM 50

void print_matrix(size_t rows, size_t cols, const int matrix[rows][cols])
{
    for (size_t i = 0; i < rows; ++i) {
        const int *row = *(matrix + i);
        for (size_t j = 0; j < cols; ++j) {
            if (j != 0) {
                printf(" ");
            }
            printf("%d", *(row + j));
        }
        printf("\n");
    }
}


const int *find_matrix_max(size_t rows, size_t cols,
                            const int matrix[rows][cols],
                            size_t *max_row, size_t *max_col)
{
    const int *best = *(matrix + 0);
    *max_row = 0;
    *max_col = 0;

    for (size_t i = 0; i < rows; ++i) {
        const int *row = *(matrix + i);
        const int *p = row;
        for (p = row; p != row + cols; ++p) {
            if (*p > *best) {
                best = p;
                *max_row = i;
                *max_col = (size_t)(p - row);
            }
        }
    }

    return best;
}

double matrix_average(size_t rows, size_t cols, const int matrix[rows][cols])
{
    long long sum = 0;

    for (size_t i = 0; i < rows; ++i) {
        const int *row = *(matrix + i);
        const int *p = row;
        for (p = row; p != row + cols; ++p) {
            sum += *p;
        }
    }

    return (double)sum / (double)(rows * cols);
}

size_t count_above_average(size_t rows, size_t cols,
                            const int matrix[rows][cols], double average)
{
    size_t count = 0;

    for (size_t i = 0; i < rows; ++i) {
        const int *row = *(matrix + i);
        const int *p = row;
        for (p = row; p != row + cols; ++p) {
            if ((double)*p > average) {
                ++count;
            }
        }
    }

    return count;
}

double row_average(size_t cols, const int *row)
{
    long long sum = 0;
    const int *p = row;
    for (p = row; p != row + cols; ++p) {
        sum += *p;
    }
    return (double)sum / (double)cols;
}

size_t hottest_row(size_t rows, size_t cols, const int matrix[rows][cols])
{
    size_t best_row = 0;
    double best_avg = row_average(cols, *(matrix + 0));

    for (size_t i = 1; i < rows; ++i) {
        double avg = row_average(cols, *(matrix + i));
        if (avg > best_avg) {
            best_avg = avg;
            best_row = i;
        }
    }

    return best_row;
}

void fill_row_with_average(size_t cols, int *row)
{
    double avg = row_average(cols, row);
    int value = (int)avg;

    int *p = row;
    for (p = row; p != row + cols; ++p) {
        *p = value;
    }
}

int max_neighbor_difference(size_t rows, size_t cols,
                             const int matrix[rows][cols])
{
    int best_diff = 0;

    for (size_t i = 0; i < rows; ++i) {
        const int *row = *(matrix + i);
        const int *p = row;
        for (p = row; p != row + cols - 1; ++p) {
            int diff = *p - *(p + 1);
            if (diff < 0) {
                diff = -diff;
            }
            if (diff > best_diff) {
                best_diff = diff;
            }
        }
    }

    return best_diff;
}

int main(void)
{
    size_t rows, cols;

    if (scanf("%zu %zu", &rows, &cols) != 2) {
        fprintf(stderr, "Ошибка: не удалось считать размеры матрицы.\n");
        return EXIT_FAILURE;
    }

    if (rows < MIN_DIM || rows > MAX_DIM || cols < MIN_DIM || cols > MAX_DIM) {
        fprintf(stderr, "Ошибка: R и C должны быть в диапазоне [%d, %d].\n",
                MIN_DIM, MAX_DIM);
        return EXIT_FAILURE;
    }

    int matrix[rows][cols];
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Ошибка: не удалось считать элемент матрицы.\n");
                return EXIT_FAILURE;
            }
        }
    }

    printf("Исходная карта:\n");
    print_matrix(rows, cols, (const int (*)[cols])matrix);
    printf("\n");

    size_t max_row = 0, max_col = 0;
    const int *max_ptr = find_matrix_max(rows, cols, (const int (*)[cols])matrix, &max_row, &max_col);

    double average = matrix_average(rows, cols, (const int (*)[cols])matrix);
    size_t above_count = count_above_average(rows, cols, (const int (*)[cols])matrix, average);

    size_t hot_row = hottest_row(rows, cols, (const int (*)[cols])matrix);
    double hot_row_avg_before = row_average(cols, matrix[hot_row]);

    printf("Максимальная температура: %d\n", *max_ptr);
    printf("Строка: %zu\n", max_row);
    printf("Столбец: %zu\n", max_col);
    printf("Средняя температура карты: %.2f\n", average);
    printf("Количество значений выше среднего: %zu\n", above_count);
    printf("Строка с максимальным средним: %zu\n", hot_row);
    printf("Среднее выбранной строки: %.2f\n", hot_row_avg_before);
    printf("\n");

    fill_row_with_average(cols, matrix[hot_row]);

    int max_diff = max_neighbor_difference(rows, cols, (const int (*)[cols])matrix);

    printf("Карта после замены выбранной строки:\n");
    print_matrix(rows, cols, (const int (*)[cols])matrix);
    printf("\n");

    printf("Максимальная разница соседних температур: %d\n", max_diff);

    return EXIT_SUCCESS;
}

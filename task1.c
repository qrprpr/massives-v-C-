#include <stdio.h>
#include <stddef.h>

int *find_min(int *begin, int *end) {
    int *min = begin;
    for (int *ptr = begin; ptr < end; ptr++)
        if (*ptr < *min) min = ptr;
    return min;
}

int *find_max(int *begin, int *end) {
    int *max = begin;
    for (int *ptr = begin; ptr < end; ptr++)
        if (*ptr > *max) max = ptr;
    return max;
}

long long sum_between(const int *first, const int *second) {
    long long total = 0;
    if (first > second) {
        for (const int *ptr = second + 1; ptr < first; ptr++)
            total += *ptr;
    } else {
        for (const int *ptr = first + 1; ptr < second; ptr++)
            total += *ptr;
    }
    return total;
}

size_t find_longest_increasing(int *begin, int *end, int **sequence_begin) {
    size_t max_len = 1;
    size_t curr_len = 1;
    *sequence_begin = begin;

    for (int *ptr = begin; ptr + 1 < end; ptr++) {
        if (*ptr < *(ptr + 1))
            curr_len++;
        else
            curr_len = 1;

        if (curr_len > max_len) {
            max_len = curr_len;
            *sequence_begin = ptr - (int)curr_len + 2;
        }
    }
    return max_len;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse_range(int *begin, int *end) {
    int *begin_ptr = begin, *end_ptr = end - 1;
    while (begin_ptr < end_ptr) {
        swap(begin_ptr, end_ptr);
        begin_ptr++;
        end_ptr--;
    }
}

void print_array(const int *begin, const int *end) {
    for (const int *ptr = begin; ptr < end; ptr++)
        printf("%d ", *ptr);
    printf("\n");
}

int main(void) {
    int arr[1000], n, written = 0;
    if (scanf("%d", &n) != 1 || n < 2 || n > 1000) {
        printf("Некорректное количество элементов\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        written += scanf("%d", arr + i);

    if (written != n) {
        printf("Ошибка ввода элементов массива\n");
        return 1;
    }

    int *min_ptr = find_min(arr, arr + n);
    int *max_ptr = find_max(arr, arr + n);
    long long sum_min_max = sum_between(min_ptr, max_ptr);

    int len_between;
    if (min_ptr > max_ptr)
        len_between = (int)(min_ptr - max_ptr);
    else
        len_between = (int)(max_ptr - min_ptr);

    int *sequence_begin;
    size_t max_len = find_longest_increasing(arr, arr + n, &sequence_begin);

    printf("Исходный массив:\n");
    print_array(arr, arr + n);
    printf("Минимум: %d\n", *min_ptr);
    printf("Позиция минимума: %d\n", (int)(min_ptr - arr));
    printf("Максимум: %d\n", *max_ptr);
    printf("Позиция максимума: %d\n", (int)(max_ptr - arr));
    printf("Расстояние между минимумом и максимумом: %d\n", len_between);
    printf("Сумма элементов между минимумом и максимумом: %lld\n", sum_min_max);
    printf("\n");

    printf("Самый длинный возрастающий участок:\n");
    print_array(sequence_begin, sequence_begin + max_len);
    printf("Длина: %zu\n", max_len);
    printf("\n");

    reverse_range(sequence_begin, sequence_begin + max_len);
    printf("Массив после разворота выбранного участка:\n");
    print_array(arr, arr + n);

    return 0;
}
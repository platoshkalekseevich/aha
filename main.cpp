#include <iostream>
#include <stdio.h>

int closeStepen(int value) {
    int cnt = 1;
    bool is_stepen = true;
    while (value > 1) {
        if (value % 2 == 1) is_stepen = false;
        cnt++;
        value /= 2;
    }
    if (is_stepen) return cnt;
    else return cnt + 1;
}

int pow2(int stepen) {
    return 1<<stepen;
}

void changeTree(int* mas, int position) {
    while (position != 1) {
        if (position % 2 == 0) {
            mas[position/2] = mas[position] + mas[position + 1];
            position /= 2;
        } else {
            mas[position/2] = mas[position] + mas[position - 1];
            position /= 2;
        }
    }
}

int findSum(int* mas, int current, const int search_left, const int search_right, int left, int right) {
    if (left >= search_left && right <= search_right) {
        return mas[current];
    }
    if (right < search_left || search_right < left) {
        return 0;
    }
    int mid = (left + right) / 2;
    return findSum(mas, current*2, search_left, search_right, left, mid) + findSum(mas, current*2+1, search_left, search_right, mid+1, right);
}

int main() {
    int cats, events;
    std::cin >> cats >> events;
    int size = pow2(closeStepen(cats));
    std::cout << cats << ' ' << size << '\n';
    int *mas = new int[size*2];
    for (int i = 0; i < size*2; i ++){
        mas[i] = 0;
    }


    int id, value;
    char operation_type;
    for (int i = 0; i < events; i++) {
        std::cin >> operation_type;
        if (operation_type == '+') {
            std::cin >> id >> value;
            mas[size - 1 + id] += value;
            changeTree(mas, size - 1 + id);
        } else if (operation_type == '-') {
            std::cin >> id >> value;
            mas[size - 1 + id] -= std::min(value, mas[size - 1 + id]);
            changeTree(mas, size - 1 + id);
        } else {
            int left, right;
            std::cin >> left >> right;
            std::cout << findSum(mas, 1, left, right, 1, cats) << '\n';
        }
        for(int i = 0; i < size*2; i++) {
            std::cout << mas[i] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
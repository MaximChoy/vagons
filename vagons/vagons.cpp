#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <chrono>

using namespace std;

void sortTrains(vector<char>& initial, vector<char> & final, stack<char>& buffer, int& countMimo, int& countV, int& countIz) {
    if (initial.empty()) return;

    char expected = initial.front();

    for (char train : initial) {
        if (train == expected) {
            final.push_back(train);
            cout << "МИМО: " << train << "\n";
            countMimo++;
            expected = (expected == 'A') ? 'B' : 'A';
        }
        else {
            buffer.push(train);
            cout << "В: " << train << "\n";
            countV++;
        }

        while (!buffer.empty() && buffer.top() == expected) {
            final.push_back(buffer.top());
            buffer.pop();
            cout << "ИЗ: " << final.back() << "\n";
            countIz++;
            expected = (expected == 'A') ? 'B' : 'A'; 
        }
    }

    while (!buffer.empty()) {
        final.push_back(buffer.top());
        buffer.pop();
        cout << "ИЗ: " << final.back() << "\n";
        countIz++;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;

    cout << "Введите количество операций :";
    cin >> n;

    vector<char> initial;
    for (int i = 0; i < n; ++i) {
        initial.push_back('A');
        initial.push_back('B');
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(initial.begin(), initial.end(), default_random_engine(seed));

    cout << "Начальное расположение вагонов: ";
    for (char train : initial) {
        cout << train;
    }
    cout << endl;

    vector<char> final;
    stack<char> buffer;

    int countMimo = 0, countV = 0, countIz = 0;
    sortTrains(initial, final, buffer, countMimo, countV, countIz);

    cout << "Конечное расположение вагонов: ";
    for (char train : final) {
        cout << train;
    }
    cout << "\nКоличество операций 'МИМО': " << countMimo << "\nКоличество операций 'В': " << countV << "\nКоличество операций 'ИЗ': " << countIz << endl;
    cout << "Всего операций :" << countMimo + countV + countIz;
    return 0;
}

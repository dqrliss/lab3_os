#include <iostream>
#include <thread>
#include <chrono>
#include <pthread.h>
std::mutex m;

void first (int i, std::vector<int>& v, int c, std::vector<int>& quantity) {
    m.lock();
    srand(i);
    while (true) {
        int temp = rand() % v.size();
        if (v[temp] == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            v[temp] = i;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            c++;
            continue;
        }
        else {
            std::cout << "\nserial number: " << i << ", quantity of marked elements: " << c << ", index of array element that cannot be marked: " << temp;
            break;
        }
    }
    quantity[i] = c;
    m.unlock();
}

void second (int k_, std::vector<int>& v, int c) {
    m.lock();
    int i = 0;
    while (i != v.size() && c) {
        if (v[i] == k_) v[i] = 0;
        c--;
        i++;
    }
    m.unlock();
}

int main() {
    int n;
    std::cout << "array size: "; std::cin >> n;
    std::vector<int> v(n);
    int k;
    std::cout << "quantity of 'marker' threads: "; std::cin >> k;
    std::thread** marker = new std::thread *[k];
    std::vector<int> quantity (k);
    for (int i = 0; i < k; i++) marker[i] = new std::thread(first, i, std::ref(v), 0, std::ref(quantity));
    for (int i = 0; i < k; i++) marker[i]->join();
    int k_, p = 0;
    std::vector<int> deleted (k);
    while (true) {
        std::cout << "\n";
        for (int i = 0; i < n; i++) std::cout << v[i] << " ";
        std::cout << "\nthe serial number of thread* marker: "; std::cin >> k_;
        if (deleted[k_] != 1) {
            if (quantity[k_] == 0) {
                deleted[k_] = 1;
                p++;
            }
            else {
                marker[k_] = new std::thread (second, k_, std::ref(v), quantity[k_]);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                deleted[k_] = 1;
                quantity[k_] = 0;
                p++;
            }
            for (int i = 0; i < n; i++) std::cout << v[i] << " ";
            for (int i = 0; i < k; i++) {
                if (i == k_) continue;
                if (deleted[i] == 1) continue;
                else marker[i] = new std::thread (first, i, std::ref(v), 0, std::ref(quantity));
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
        if (p == k) break;
    }
    return 0;
}
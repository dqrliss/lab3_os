#include <iostream>
#include <thread>
#include <chrono>
std::mutex m;

void first (int i, std::vector<int>& v) {
    srand(i);
    int c = 0;
    while (true) {
        int temp = rand() % v.size();
        if (v[temp] == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            v[temp] = i;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            c++;
        }
        else {
            m.lock();
            std::cout << "\nserial number: " << i << ", quantity of marked elements: " << c << ", index of array element that cannot be marked: " << temp;
            m.unlock();
            break;
        }
    }
}

void second (int k_, std::vector<int>& v) {
    int i = 0;
    while (i != v.size()) {
        if (v[i] == k_) v[i] = 0;
        i++;
    }
}

int main() {
    int n, k;
    std::cout << "array size: "; std::cin >> n;
    std::vector<int> v(n);
    std::cout << "quantity of 'marker' threads: "; std::cin >> k;
    std::thread** marker = new std::thread *[k + 1];
    for (int i = 1; i < k + 1; i++) marker[i] = new std::thread(first, i, std::ref(v));
    for (int i = 1; i < k + 1; i++) marker[i]->join();
    int k_, p = 0;
    std::vector<int> deleted (k + 1);
    while (true) {
        std::cout << "\n";
        for (int i = 0; i < n; i++) std::cout << v[i] << " ";
        std::cout << "\nthe serial number of thread* marker: "; std::cin >> k_;
        if (k_ > k || k_ < 1) continue;
        else if (deleted[k_] != 1) {
            marker[k_] = new std::thread(second, k_, std::ref(v));
            marker[k_]->join();
            deleted[k_] = 1;
            p++;
            for (int i = 0; i < n; i++) std::cout << v[i] << " ";
            for (int i = 1; i < k + 1; i++) {
                if (deleted[i] == 1) continue;
                else marker[i] = new std::thread(first, i, std::ref(v));
            }
            for (int i = 1; i < k + 1; i++) {
                if (deleted[i] == 1) continue;
                else marker[i]->join();
            }
        }
        else continue;
        if (p == k) break;
    }
    return 0;
}
#include <iostream>
#include <thread>
#include <chrono>
std::mutex m;

class semaphore
{
    unsigned int count_;
    std::mutex mutex_;
    std::condition_variable condition_;

public:
    explicit semaphore(unsigned int initial_count) : count_(initial_count), mutex_(), condition_() {}

    void signal() //aka release
    {
        std::unique_lock<std::mutex> lock(mutex_);

        ++count_;
        condition_.notify_one();
    }

    void wait() //aka acquire
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ == 0) condition_.wait(lock);
        --count_;
    }

    semaphore() {
        count_ = 0;
    }
};

semaphore pause_sem(0);
semaphore* marker_sems;

void first (int i, std::vector<int>& v, std::vector<bool>& marked) {
    marker_sems[i].wait();
    srand(i);
    int c = 0;
    while (true) {
        int temp = rand() % v.size();
        m.lock();
        if (v[temp] == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            v[temp] = i;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            c++;
            m.unlock();
        }
        else {
            std::cout << "\nserial number: " << i << ", quantity of marked elements: " << c << ", index of array element that cannot be marked: " << temp;
            m.unlock();
            pause_sem.signal();
            marker_sems[i].wait();
            if (marked[i]) {
                m.lock();
                for (int j = 0; j < v.size(); j++) if (v[j] == i) v[j] = 0;
                m.unlock();
                marker_sems[i].signal();
                break;
            }
        }
    }
}

int main() {
    int n, k, p = 0;
    std::cout << "array size: "; std::cin >> n;
    std::vector<int> v(n);
    std::cout << "quantity of 'marker' threads: "; std::cin >> k;
    int kn = k;
    std::thread** marker = new std::thread* [k + 1];
    std::vector<bool> marked(k + 1);
    marked[0] = true;
    marker_sems = new semaphore[k + 1];
    for (int i = 1; i < k + 1; i++) {
        marker[i] = new std::thread(first, i, std::ref(v), std::ref(marked));
        marker[i]->detach();
        marker_sems[i].signal();
    }
    while(true) {
        for (int i = 1; i < kn + 1; i++) pause_sem.wait();
        std::cout << "\n";
        m.lock();
        for (int i = 0; i < n; i++) std::cout << v[i] << " ";
        m.unlock();
        std::cout << "\n";
        int k_;
        std::cout << "marker to delete: "; std::cin >> k_;
        marked[k_] = true;
        p++;
        marker_sems[k_].signal();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        marker_sems[k_].wait();
        kn--;
        for (int i = 0; i < n; i++) std::cout << v[i] << " ";
        for (int i = 1; i < k + 1; i++) marker_sems[i].signal();
        if (p == k) break;
    }
    return 0;
}
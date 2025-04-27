/*
 *  Made by UltimateSheep, sℏερ.
 *  Written on Clion,
 *  04/27/2025
 */

#include <chrono>
#include <iostream>
#include <map>
#include <thread>
#include <cmath>

// Alias
using hr_clock = std::chrono::high_resolution_clock;

// Simple timer lol
class Timer {
    hr_clock::time_point _start;
    hr_clock::time_point _end;

public:
    // This will run once the class is constructed
    Timer() {
        this->_start = hr_clock::now();
    }

    // This will run when the class is deconstructed.
    ~Timer() {
        this->_end = hr_clock::now();
        const std::chrono::duration<float> delta_t = (this->_end - this->_start)*100;

        std::cout << "Code finished in " << delta_t.count() << "ms" << std::endl;
    }
};

/*
 * Throw error if provided n arg will overflow the uint64_t limit
 *  @param n {int&} reference the number
 */
void isFibOverflow(const int &n) {
    // The most optimized way is to just hardcode it LOL
    if (n >= 49)
        throw std::overflow_error("The Fibonacci calculation has overflowed the limit of uint64_t limit.");
}

/*
 * Doing the god(Fibonacci)'s work
 * @param n {std::string&} reference to the number to be calculated
 * @param cache {std::pmr::map<int, int>&} reference to the cache map
 */
uint64_t fib(const int &n, std::pmr::map<int, int> &cache) {
    if (n == 1 || n == 0) return n; // If n is [0,1] return that value || Fib(0) = 0, Fib(1) = 1
    if (cache[n]) return cache[n]; // If there is n in cache, return cache

    isFibOverflow(n);
    const uint64_t _val = fib(n - 2, cache) + fib(n - 1, cache); // Fib(n) = Fib(n-2) + Fib(n-1)

    cache[n] = _val; // Insert to cache

    return _val; // Return value
}

/*
 * @param question {std::string&} reference to the question
 * @param in {int&} reference to the number input
 */
void listen_for_input(const std::string &question, int &in) {
    // Continuously asking the user until the input is valid
    while (true) {
        std::cout << question;
        std::cin >> in;

        if (!std::cin.fail()) // If the answer is valid then break
            break;

        // If the input is invalid, clear the std::cin and loop
        std::cout << "Invalid input, try again." << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
}

int main() {
    static std::pmr::map<int, int> cache{}; // Map of cache stored in static memory

    // Loop the program until user inputted: y
    while (true) {
        int in;
        listen_for_input("Input your number:", in);

        {
            // ReSharper disable once CppUseAuto
            std::unique_ptr<Timer> t = std::make_unique<Timer>();

            const uint64_t fib_out = fib(in, cache);

            std::cout << "Your result is: " << fib_out << std::endl;
            // Timer t will be destroyed after this scope
        }

        // Sleep for 500ms
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::string exit;
        std::cout << "Exit? (y/n):";

        std::cin >> exit;
        if (exit == "y") break;
    }

    return 0;
}
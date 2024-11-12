#include <iostream>

bool searchAttempt() {
    // Simulate search operation - in reality, replace this with actual search code
    static int attempt = 0;
    ++attempt;
    return attempt >= 5; // Simulate success on the 5th attempt
}

void searchWithExponentialBackoff(int maxRetries) {
    int attempt = 0;
    int baseDelay = 1; // initial delay

    while (attempt < maxRetries) {
        if (searchAttempt()) {
            std::cout << "Searching is successful on attempt " << attempt + 1 << std::endl;
            return;
        }

        int delay = baseDelay * (1 << attempt); 
        
        std::cout << "Attempt " << attempt + 1 << " failed. Retrying in " << delay << " units of time\n";
      
        for (int i = 0; i < delay * 1000000; ++i); 

        ++attempt;
    }
    std::cout << "Search failed after " << maxRetries << " attempts.\n";
}

int main() {
    int maxRetries = 10;
    searchWithExponentialBackoff(maxRetries);
    return 0;
}
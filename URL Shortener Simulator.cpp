

#include <iostream>
#include <unordered_map>
#include <string>
#include <random>
#include <ctime>

class URLShortener {
private:
    std::unordered_map<std::string, std::string> urlMap;
    std::unordered_map<std::string, std::string> reverseMap;
    const std::string BASE62 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const std::string BASE_URL = "https://short.ly/";
    
public:
    URLShortener() {
        srand(time(0));
    }
    
    std::string generateShortCode() {
        std::string shortCode;
        for (int i = 0; i < 6; i++) {
            shortCode += BASE62[rand() % 62];
        }
        return shortCode;
    }
    
    std::string shorten(const std::string& longURL) {
        // Check if URL already shortened
        if (reverseMap.find(longURL) != reverseMap.end()) {
            return BASE_URL + reverseMap[longURL];
        }
        
        // Generate unique short code
        std::string shortCode;
        do {
            shortCode = generateShortCode();
        } while (urlMap.find(shortCode) != urlMap.end());
        
        // Store mapping
        urlMap[shortCode] = longURL;
        reverseMap[longURL] = shortCode;
        
        return BASE_URL + shortCode;
    }
    
    std::string expand(const std::string& shortURL) {
        // Extract short code
        size_t pos = shortURL.find_last_of('/');
        if (pos == std::string::npos) return "Invalid URL";
        
        std::string shortCode = shortURL.substr(pos + 1);
        
        if (urlMap.find(shortCode) != urlMap.end()) {
            return urlMap[shortCode];
        }
        return "URL not found";
    }
    
    void listURLs() {
        std::cout << "\n--- Shortened URLs ---\n";
        for (const auto& pair : urlMap) {
            std::cout << BASE_URL + pair.first << " -> " << pair.second << "\n";
        }
    }
};

int main() {
    URLShortener shortener;
    int choice;
    
    do {
        std::cout << "\n=== URL Shortener ===\n";
        std::cout << "1. Shorten URL\n";
        std::cout << "2. Expand URL\n";
        std::cout << "3. List All URLs\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 1) {
            std::string longURL;
            std::cout << "Enter URL to shorten: ";
            std::getline(std::cin, longURL);
            std::string shortURL = shortener.shorten(longURL);
            std::cout << "Shortened URL: " << shortURL << std::endl;
        } else if (choice == 2) {
            std::string shortURL;
            std::cout << "Enter short URL: ";
            std::getline(std::cin, shortURL);
            std::string original = shortener.expand(shortURL);
            std::cout << "Original URL: " << original << std::endl;
        } else if (choice == 3) {
            shortener.listURLs();
        }
    } while (choice != 4);
    
    return 0;
}

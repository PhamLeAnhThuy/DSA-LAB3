#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// Product structure to hold product data
struct Product {
    string name;
    string category;
    string brand;
    double price;
    string description;
};

// Helper function to convert a string to lowercase
string toLowerCase(const string &str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Function to check if query keywords are in product name or description
bool matchProduct(const Product &product, const string &query) {
    string lowerQuery = toLowerCase(query);
    return (toLowerCase(product.name).find(lowerQuery) != string::npos ||
            toLowerCase(product.description).find(lowerQuery) != string::npos);
}

// Function to filter products by price range, category, and brand
vector<Product> filterProducts(const vector<Product> &products, double minPrice, double maxPrice,
                               const string &category, const string &brand) {
    vector<Product> filtered;
    for (const auto &product : products) {
        if ((minPrice <= product.price && product.price <= maxPrice) &&
            (category.empty() || product.category == category) &&
            (brand.empty() || product.brand == brand)) {
            filtered.push_back(product);
        }
    }
    return filtered;
}

// Function to search products with optional filters for faceted search
vector<Product> searchProducts(const vector<Product> &products, const string &query,
                               double minPrice = 0.0, double maxPrice = 1e9,
                               const string &category = "", const string &brand = "") {
    vector<Product> results;
    for (const auto &product : products) {
        if (matchProduct(product, query)) {
            results.push_back(product);
        }
    }

    // Apply filters
    results = filterProducts(results, minPrice, maxPrice, category, brand);
    return results;
}

// Function to display search results
void displayResults(const vector<Product> &results) {
    if (results.empty()) {
        cout << "No products found.\n";
    } else {
        for (const auto &product : results) {
            cout << "Name: " << product.name << "\n"
                 << "Category: " << product.category << "\n"
                 << "Brand: " << product.brand << "\n"
                 << "Price: $" << product.price << "\n"
                 << "Description: " << product.description << "\n\n";
        }
    }
}

int main() {
    // Sample product dataset
    vector<Product> products = {
        {"Laptop", "Electronics", "Dell", 799.99, "High performance laptop with 16GB RAM."},
        {"Smartphone", "Electronics", "Samsung", 999.99, "Latest smartphone with great camera."},
        {"Coffee Maker", "Appliances", "Breville", 249.99, "Automatic coffee maker with timer."},
        {"Running Shoes", "Footwear", "Nike", 129.99, "Comfortable running shoes with great support."},
        {"Blender", "Appliances", "Oster", 89.99, "Powerful blender with multiple speeds."}
    };

    // User query and filter parameters
    string query;
    double minPrice, maxPrice;
    string category, brand;

    cout << "Enter search query: ";
    getline(cin, query);
    cout << "Enter minimum price (or 0 for no minimum): ";
    cin >> minPrice;
    cout << "Enter maximum price (or 0 for no maximum): ";
    cin >> maxPrice;
    cin.ignore(); // Ignore leftover newline
    cout << "Enter category (or leave blank for all): ";
    getline(cin, category);
    cout << "Enter brand (or leave blank for all): ";
    getline(cin, brand);

    // Search and display results
    vector<Product> results = searchProducts(products, query, minPrice, maxPrice, category, brand);
    displayResults(results);

    return 0;
}

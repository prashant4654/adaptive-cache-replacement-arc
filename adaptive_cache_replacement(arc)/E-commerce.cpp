#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <limits>
using namespace std;

struct Product {
    int productID;
    string name;
    string company;
    string category;
    double price;
    int views;

    Product(int id, string n, string comp, string cat, double p, int v)
        : productID(id), name(n), company(comp), category(cat), price(p), views(v) {}

    bool operator<(const Product& other) const {
        return price < other.price;
    }
};


class ProductBST {
    struct TreeNode {
        Product product;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const Product& p) : product(p), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    void insert(TreeNode*& node, const Product& product) {
        if (!node) {
            node = new TreeNode(product);
        } else if (product.price < node->product.price) {
            insert(node->left, product);
        } else {
            insert(node->right, product);
        }
    }

    void inOrderTraversal(TreeNode* node, vector<Product>& products) const {
        if (!node) return;
        inOrderTraversal(node->left, products);
        products.push_back(node->product);
        inOrderTraversal(node->right, products);
    }

    void recommendInRange(TreeNode* node, double low, double high, vector<Product>& results) const {
        if (!node) return;
        if (low < node->product.price) recommendInRange(node->left, low, high, results);
        if (node->product.price >= low && node->product.price <= high) {
            results.push_back(node->product);
        }
        if (high > node->product.price) recommendInRange(node->right, low, high, results);
    }

public:
    ProductBST() : root(nullptr) {}

    void insert(const Product& product) {
        insert(root, product);
    }

    vector<Product> getAllProducts() const {
        vector<Product> products;
        inOrderTraversal(root, products);
        return products;
    }

    vector<Product> recommendInRange(double low, double high) const {
        vector<Product> results;
        recommendInRange(root, low, high, results);
        return results;
    }
};

vector<Product> loadProducts(const string& filename) {
    vector<Product> products;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return products;
    }

    getline(file, line);
    int lineNumber = 2;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, company, category, price, views;

        try {
            
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, company, ',');
            getline(ss, category, ',');
            getline(ss, price, ',');
            getline(ss, views, ',');

            if (id.empty() || name.empty() || company.empty() || category.empty() || price.empty() || views.empty()) {
                throw invalid_argument("Missing data in row " + to_string(lineNumber));
            }

            int productID = stoi(id);
            double productPrice = stod(price);
            int productViews = stoi(views);

            products.emplace_back(productID, name, company, category, productPrice, productViews);
        } catch (const invalid_argument& e) {
            cerr << "Warning: Skipping line " << lineNumber << " due to invalid data: " << e.what() << " [" << line << "]" << endl;
        } catch (const out_of_range& e) {
            cerr << "Warning: Skipping line " << lineNumber << " due to out of range error: " << e.what() << " [" << line << "]" << endl;
        } catch (const exception& e) {
            cerr << "Warning: Skipping line " << lineNumber << " due to unknown error: " << e.what() << " [" << line << "]" << endl;
        }

        lineNumber++;
    }
    return products;
}

void displayProducts(const vector<Product>& products) {
    cout << left << setw(12) << "Product ID"
         << setw(30) << "Name"
         << setw(20) << "Company"
         << setw(20) << "Category"
         << setw(10) << "Price"
         << setw(10) << "Views" 
         <<endl;

    cout << string(100, '-') << endl; 

    
    for (const auto& product : products) {
        cout << left << setw(12) << product.productID 
             << setw(30) << product.name
             << setw(20) << product.company
             << setw(20) << product.category 
             << setw(10) << fixed << setprecision(2) << product.price 
             << setw(10) << product.views << endl;
    }
}


void showTopKProducts(const vector<Product>& products, int k, const string& filterBy = "views") {
    auto comparator = [&](const Product& a, const Product& b) {
        if (filterBy == "views") return a.views < b.views;
        if (filterBy == "price") return a.price < b.price;
        return a.views < b.views;
    };

    priority_queue<Product, vector<Product>, decltype(comparator)> pq(comparator);
    for (const auto& product : products) {
        pq.push(product);
    }

    cout << "Top " << k << " Products based on " << filterBy << ": " << endl;
    cout << left <<setw(10)<<"S.no"
         << setw(12) << "Product ID"
         << setw(30) << "Name"
         << setw(20) << "Company"
         << setw(20) << "Category"
         << setw(10) << "Price"
         << setw(10) << "Views" 
         <<endl;
    for (int i = 0; i < k && !pq.empty(); ++i) {
        auto top = pq.top();
        cout << left <<setw(10)<< i + 1
             << setw(12) << top.productID
             << setw(30) << top.name
             << setw(20) << top.company
             << setw(20) << top.category 
             << setw(10) << fixed << setprecision(2) << top.price 
             << setw(10) << top.views << endl;

        pq.pop();
    }
}

void filterProductsByCategory(const vector<Product>& products) {
    string category;
    cout << "Enter category to filter by: ";
    cin.ignore(); 
    getline(cin, category);
    vector<Product> filteredProducts;
    for (const auto& product : products) {
        if (product.category == category) {
            filteredProducts.push_back(product);
        }
    }
    if (filteredProducts.empty()) {
        cout << "No products found in category: " << category << endl;
    } else {
        displayProducts(filteredProducts);
    }
}

void filterProductsByCompany(const vector<Product>& products) {
    string company;
    cout << "Enter company to filter by: ";
    cin.ignore();
    getline(cin, company);
    vector<Product> filteredProducts;
    for (const auto& product : products) {
        if (product.company == company) {
            filteredProducts.push_back(product);
        }
    }
    if (filteredProducts.empty()) {
        cout << "No products found for company: " << company << endl;
    } else {
        displayProducts(filteredProducts);
    }
}

void sortProducts(const vector<Product>& products) {
    vector<Product> sortedProducts = products;
    int sortChoice;
    cout << "Sort by:\n1. Price Ascending\n2. Price Descending\n3. Views Ascending\n4. Views Descending\nEnter choice: ";
    cin >> sortChoice;
    if (cin.fail() || sortChoice < 1 || sortChoice > 4) {
        cout << "Invalid choice. Returning to main menu." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    switch (sortChoice) {
        case 1:
            sort(sortedProducts.begin(), sortedProducts.end(), [](const Product& a, const Product& b) {
                return a.price < b.price;
            });
            break;
        case 2:
            sort(sortedProducts.begin(), sortedProducts.end(), [](const Product& a, const Product& b) {
                return a.price > b.price;
            });
            break;
        case 3:
            sort(sortedProducts.begin(), sortedProducts.end(), [](const Product& a, const Product& b) {
                return a.views < b.views;
            });
            break;
        case 4:
            sort(sortedProducts.begin(), sortedProducts.end(), [](const Product& a, const Product& b) {
                return a.views > b.views;
            });
            break;
    }
    displayProducts(sortedProducts);
}

int main() {
    string filename = "E-commerce(data).csv";
    vector<Product> products = loadProducts(filename);

    if (products.empty()) {
        cerr << "Error: No valid products loaded from the file. Please check the input file for errors." << endl;
        cout << "Press Enter to exit...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return 1;
    }

    ProductBST bst;
    for (const auto& product : products) {
        bst.insert(product);
    }

    int choice;
    do {
        cout <<"***************** E-Commerce Recommendation System **************************"
             <<"\n1. Show All Products"
             << "\n2. Show Top K Products by Views"
             << "\n3. Show Top K Products by Price"
             << "\n4. Recommend Products in Price Range"
             << "\n5. Filter Products by Category"
             << "\n6. Filter Products by Company"
             << "\n7. Sort Products"
             << "\n8. Exit\n"
             <<"*****************************************************************************"
             << "\nEnter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 9." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                displayProducts(products);
                break;
            }
            case 2: {
                int k;
                cout << "Enter value of K: ";
                cin >> k;
                if (cin.fail() || k <= 0) {
                    cout << "Invalid value for K. Please enter a positive integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                showTopKProducts(products, k, "views");
                break;
            }
            case 3: {
                int k;
                cout << "Enter value of K: ";
                cin >> k;
                if (cin.fail() || k <= 0) {
                    cout << "Invalid value for K. Please enter a positive integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                showTopKProducts(products, k, "price");
                break;
            }
            case 4: {
                double low, high;
                cout << "Enter low price: ";
                cin >> low;
                cout << "Enter high price: ";
                cin >> high;
                if (cin.fail() || low < 0 || high < 0 || low > high) {
                    cout << "Invalid price range. Please enter valid positive numbers with low <= high." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                vector<Product> recommended = bst.recommendInRange(low, high);
                cout << "Recommended Products in Price Range [" << low << ", " << high << "]:\n";
                displayProducts(recommended);
                break;
            }
            case 5: {
                filterProductsByCategory(products);
                break;
            }
            case 6: {
                filterProductsByCompany(products);
                break;
            }
            case 7: {
                sortProducts(products);
                break;
            }
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}

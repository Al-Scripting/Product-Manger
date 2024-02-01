//Product manager by Al Muqshith Mohammed Shifan
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Basic Information for each Product in the Array
struct Product {
    int ID{};
    string P_Name;
    float Price{};
    string P_Category;
};

// Class that stores the product in either a bubble sort or insertion sort
class Product_Manager {
private:
    vector<Product> products;

    // Bubble sort function
    void BubbleSort() {
        int i, j; // Counters
        bool itemsSwapped; // Temp variable to switch placement of Items

        for (i = 0; i < products.size() - 1; i++) {
            itemsSwapped = false;
            for (j = 0; j < products.size() - i - 1; j++) {
                if (products[j].Price > products[j + 1].Price) {
                    swap(products[j], products[j + 1]);
                    itemsSwapped = true;
                }
            }
            // If no two elements were swapped
            // by the inner loop, then break
            if (!itemsSwapped)
                break;
        }
    }

    // Insertion sort function
    void InsertionSort() {
        int i, j; // Counters
        Product key;

        for (i = 1; i < products.size(); i++) {
            key = products[i];
            j = i - 1;
            while (j >= 0 && products[j].Price > key.Price) {
                products[j + 1] = products[j];
                j = j - 1;
            }
            products[j + 1] = key;
        }
    }

public:
    // Load the data from the text file to read

    // function to read the data file
    void readData(string filename) {
        ifstream file(filename);
        string line, word;
        Product item;

        while (getline(file, line)) {
            stringstream s(line); // reads each line

            // reads the product ID
            getline(s, word, ',');
            item.ID = stoi(word);

            // reads the products Name
            getline(s, item.P_Name, ',');

            // reads the products Price
            getline(s, word, ',');
            item.Price = stof(word);

            // reads the products Category
            getline(s, item.P_Category, ',');

            // insert new data into the back of the array
            products.push_back(item);
        }
    }

    // Adds a new product to the array
    void Add(Product item) {
        products.push_back(item);
    }

    // Updates an already existing product using the product ID
    void Update(int ID, Product item) {
        // auto automatically detects and assigns a data type to the variable with which it is used
        // prod is a reference to the elements in the products collection.
        for (auto &prod : products) {
            if (prod.ID == ID) {
                prod = item;
                break;
            }
        }
    }

    // Deletes a product
    void Delete(int ID) {
        // begin() function is used to return an iterator pointing to the first element of the vector container.
        // end() function is used to get an iterator to past the last element.
        for (auto x = products.begin(); x != products.end(); x++) {
            if (x->ID == ID) {
                // erase() function is used to remove elements from a container from the specified range.
                products.erase(x);
                break;
            }

        }
    }

    // Search a product by ID
    Product Search(string key) {
        for (auto &prod : products) {
            if (to_string(prod.ID) == key) {
                cout << "ID: " << prod.ID << ", Name: " << prod.P_Name << ", Price: " << prod.Price << ", Category: " << prod.P_Category << endl;
            }
        }
        return {-1, "", -1, ""}; // Return a default product if not found
    }

    // Sort products by price based on either bubble or insertion sorting algorithms
    void Sort(string method) {
        if (method == "bubble") {
            BubbleSort();
        } else if (method == "insertion") {
            InsertionSort();
        }
    }

    // Display all products
    void Display() {
        for (auto &prod : products) {
            cout << "ID: " << prod.ID << ", Name: " << prod.P_Name << ", Price: " << prod.Price << ", Category: " << prod.P_Category << endl;
        }
    }
};

int main() {
    Product_Manager manager;
    manager.readData("product_data.txt");

    cout << "Original Data: " << endl;
    manager.Display();

// Demonstrate Insert, Update, Delete, Search
    cout << "\nOriginal Data with New Items: " << endl;
    manager.Add({99999, "Micro Cutter", 29.99, "Electronics"});
    manager.Add({88888, "laser Pointer", 9.99, "Electronics"});
    manager.Display();



    cout << "\nOriginal Data with Updated Items: " << endl;
    manager.Update(99999, {99991, "Nano Cutter", 39.99, "Home & Kitchen"});
    manager.Display();


    cout << "\nDeleting Function Demo: " << endl;
    manager.Delete(99991);
    manager.Delete(88888);
    manager.Display();

    cout << "\nSearching Function Demo:" << endl;
    cout << "Searching by ID:" << endl;
    Product foundID = manager.Search("69525");


    cout << "\nItems sorted by price with Bubble Sort: " << endl;
    // Sorting and displaying products
    manager.Sort("bubble");
    manager.Display();

    cout << "\nItems sorted by price with insertion Sort: " << endl;
    // Sorting and displaying products
    manager.Sort("insertion");
    manager.Display();

    cout << "\nEND OF PROGRAM" << endl;
    return 0;
}

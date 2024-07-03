
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class MenuItem {
public:
    string name;
    float price;
    int quantity;
    MenuItem* next;

    MenuItem(string n, float p, int q) : name(n), price(p), quantity(q), next(nullptr) {}
};

class Sale {
public:
    string name;
    float price;
    int quantity;

    Sale(string n, float p, int q) : name(n), price(p), quantity(q) {}
};

class CoffeeShop {
private:
    MenuItem* menu;
    vector<Sale> sales;

    void loadMenu() {
        ifstream file("menu.txt");
        if (file.is_open()) {
            string name;
            float price;
            int quantity;
            while (file >> name >> price >> quantity) {
                MenuItem* newItem = new MenuItem(name, price, quantity);
                newItem->next = menu;
                menu = newItem;
            }
            file.close();
        }
    }

    void saveMenu() {
        ofstream file("menu.txt");
        MenuItem* current = menu;
        while (current != nullptr) {
            file << current->name << " " << current->price << " " << current->quantity << endl;
            current = current->next;
        }
        file.close();
    }

    void loadSales() {
        ifstream file("sales.txt");
        if (file.is_open()) {
            string name;
            float price;
            int quantity;
            while (file >> name >> price >> quantity) {
                sales.push_back(Sale(name, price, quantity));
            }
            file.close();
        }
    }

    void saveSales() {
        ofstream file("sales.txt");
        for (const Sale& sale : sales) {
            file << sale.name << " " << sale.price << " " << sale.quantity << endl;
        }
        file.close();
    }

public:
    CoffeeShop() : menu(nullptr) {
        loadMenu();
        loadSales();
    }

    ~CoffeeShop() {
        saveMenu();
        saveSales();
        MenuItem* current = menu;
        while (current != nullptr) {
            MenuItem* next = current->next;
            delete current;
            current = next;
        }
    }

    void adminLogin() {
        string username, password;

        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;
    }

    void showMenu() {
        MenuItem* current = menu;

        cout << "Menu:" << endl;

        while (current != nullptr) {
            cout << current->name << " - $" << current->price << " - Quantity: " << current->quantity << endl;
            current = current->next;
        }
    }

    void addItem() {
        string name;
        float price;
        int quantity;

        cout << "Enter item name: ";
        cin >> name;

        cout << "Enter price: ";
        cin >> price;

        cout << "Enter quantity: ";
        cin >> quantity;

        MenuItem* newItem = new MenuItem(name, price, quantity);
        newItem->next = menu;
        menu = newItem;

        cout << "Item added to menu." << endl;
    }

    void deleteItem() {
        string name;

        cout << "Enter item to delete: ";
        cin >> name;

        MenuItem* current = menu;
        MenuItem* prev = nullptr;

        while (current != nullptr) {
            if (current->name == name) {
                if (prev == nullptr) {
                    menu = current->next;
                } else {
                    prev->next = current->next;
                }

                delete current;
                cout << "Item deleted." << endl;
                return;
            }

            prev = current;
            current = current->next;
        }

        cout << "Item not found." << endl;
    }

    void sellItem() {
        int numItems;
        cout << "Number of items to sell: ";
        cin >> numItems;

        for (int i = 0; i < numItems; i++) {
            string name;
            int sellQuantity;

            showMenu();

            cout << "Item name for menu " << i + 1 << ": ";
            cin >> name;

            MenuItem* current = menu;

            while (current != nullptr) {
                if (current->name == name) {
                    cout << "Enter the quantity to sell for " << name << ": ";
                    cin >> sellQuantity;

                    if (current->quantity >= sellQuantity) {
                        current->quantity -= sellQuantity;
                        sales.push_back(Sale(name, current->price, sellQuantity));
                        cout << name << " - Quantity " << sellQuantity << " sold" << endl;
                    } else {
                        cout << "Not available" << endl;
                    }
                }
                current = current->next;
            }
        }
    }

    void salesReport() {
        cout << "Sales Report" << endl;
        float totalSales = 0;

        for (const Sale& sale : sales) {
            cout << "Product: " << sale.name << " - Price: $" << sale.price << " - Quantity Sold: " << sale.quantity << " - Total Sales: $" << sale.price * sale.quantity << endl;
            totalSales += sale.price * sale.quantity;
        }

        cout << "Total Sales: $" << totalSales << endl;
    }

    void run() {
        cout << "Coffee Shop Management System" << endl;

        adminLogin();

        while (true) {
            int choice;

            cout << "\n1. Display Menu\n";
            cout << "2. Add New Item\n";
            cout << "3. Delete Item\n";
            cout << "4. Sell Item\n";
            cout << "5. Sales Report\n";
            cout << "6. Exit\n";

            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    showMenu();
                    break;
                case 2:
                    addItem();
                    break;
                case 3:
                    deleteItem();
                    break;
                case 4:
                    sellItem();
                    break;
                case 5:
                    salesReport();
                    break;
                case 6:
                    return;
                default:
                    cout << "Invalid" << endl;
            }
        }
    }
};

int main() {
    CoffeeShop shop;
    shop.run();
    return 0;
}

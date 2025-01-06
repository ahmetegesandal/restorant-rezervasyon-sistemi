#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Terminal color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

struct Reservation {
    string customerName;
    int tableNumber;
    string reservationTime;
};

struct MenuItem {
    string name;
    double price;
};

class Restaurant {
private:
    vector<Reservation> reservations;
    vector<MenuItem> menu;
    int totalTables = 30; 

    void saveReservationsToFile() {
        ofstream file("reservations.txt");
        if (!file) {
            cerr << RED << "Error: Unable to open file for saving reservations!" << RESET << "\n";
            return;
        }

        for (const auto& res : reservations) {
            file << res.customerName << "," << res.tableNumber << "," << res.reservationTime << "\n";
        }
        file.close();
    }

    void loadReservationsFromFile() {
        ifstream file("reservations.txt");
        if (!file) {
            cerr << RED << "Error: Unable to open file for loading reservations!" << RESET << "\n";
            return;
        }

        reservations.clear();
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.rfind(",");

            if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
                Reservation res;
                res.customerName = line.substr(0, pos1);
                res.tableNumber = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                res.reservationTime = line.substr(pos2 + 1);
                reservations.push_back(res);
            }
        }
        file.close();
    }

    void printHeader(const string& title) {
        cout << CYAN << "\n+" << string(40, '-') << "+\n";
        cout << "| " << setw(38) << left << title << " |\n";
        cout << "+" << string(40, '-') << "+\n" << RESET;
    }

    void loadMenu() {
        menu = {
            {"Makarna", 12.50},
            {"Et", 25.00},
            {"Salata", 8.75},
            {"Pizza", 15.00},
            {"Çorba", 6.50},
            {"Dondurma", 5.25}
        };
    }

    void viewMenu() {
        printHeader("Restaurant Menu");
        cout << left << setw(20) << "Item" << setw(10) << "Fiyat ($)" << "\n";
        cout << string(30, '-') << "\n";

        for (const auto& item : menu) {
            cout << left << setw(20) << item.name << fixed << setprecision(2) << setw(10) << item.price << "\n";
        }
    }

    void addMenuItem() {
        MenuItem newItem;
        cout << YELLOW << "\nEnter item name: " << RESET;
        cin.ignore();
        getline(cin, newItem.name);
        cout << YELLOW << "Enter item price: " << RESET;
        cin >> newItem.price;
        menu.push_back(newItem);
        cout << GREEN << "\nItem added successfully!" << RESET << "\n";
    }

    void removeMenuItem() {
        string itemName;
        cout << YELLOW << "\nEnter the name of the item to remove: " << RESET;
        cin.ignore();
        getline(cin, itemName);

        for (auto it = menu.begin(); it != menu.end(); ++it) {
            if (it->name == itemName) {
                menu.erase(it);
                cout << GREEN << "\nItem removed successfully!" << RESET << "\n";
                return;
            }
        }

        cout << RED << "\nItem not found!" << RESET << "\n";
    }

    void updateMenuItem() {
        string itemName;
        cout << YELLOW << "\nEnter the name of the item to update: " << RESET;
        cin.ignore();
        getline(cin, itemName);

        for (auto& item : menu) {
            if (item.name == itemName) {
                cout << YELLOW << "Enter new price: " << RESET;
                cin >> item.price;
                cout << GREEN << "\nItem updated successfully!" << RESET << "\n";
                return;
            }
        }

        cout << RED << "\nItem not found!" << RESET << "\n";
    }

    bool adminLogin() {
        string username, password;
        cout << YELLOW << "\nEnter admin username: " << RESET;
        cin >> username;
        cout << YELLOW << "Enter admin password: " << RESET;
        cin >> password;

        if (username == "admin" && password == "12345") {
            cout << GREEN << "\nLogin successful!" << RESET << "\n";
            return true;
        }
        else {
            cout << RED << "\nInvalid credentials!" << RESET << "\n";
            return false;
        }
    }

    void adminPanel() {
        if (!adminLogin()) return;

        int choice;
        do {
            printHeader("Admin Panel");
            cout << "1. Add Menu Item\n";
            cout << "2. Remove Menu Item\n";
            cout << "3. Update Menu Item\n";
            cout << "4. View Menu\n";
            cout << "5. Back to Main Menu\n";
            cout << YELLOW << "Enter your choice: " << RESET;
            cin >> choice;

            switch (choice) {
            case 1:
                addMenuItem();
                break;
            case 2:
                removeMenuItem();
                break;
            case 3:
                updateMenuItem();
                break;
            case 4:
                viewMenu();
                break;
            case 5:
                cout << GREEN << "\nReturning to Main Menu." << RESET << "\n";
                break;
            default:
                cout << RED << "\nInvalid choice! Please try again." << RESET << "\n";
            }
        } while (choice != 5);
    }

    void showAvailableTables() {
        cout << YELLOW << "\nAvailable Tables:" << RESET << "\n";
        bool allTablesReserved = true;

        for (int i = 1; i <= totalTables; ++i) {
            bool tableAvailable = true;
            for (const auto& res : reservations) {
                if (res.tableNumber == i) {
                    tableAvailable = false;
                    break;
                }
            }

            if (tableAvailable) {
                cout << GREEN << "Table " << i << RESET << "\n";
                allTablesReserved = false;
            }
        }

        if (allTablesReserved) {
            cout << RED << "\nAll tables are reserved!" << RESET << "\n";
        }
    }

public:
    Restaurant() {
        loadReservationsFromFile();
        loadMenu();
    }

    ~Restaurant() {
        saveReservationsToFile();
    }

    void makeReservation() {
        if (reservations.size() >= totalTables) {
            cout << RED << "\nNo available tables for reservation!" << RESET << "\n";
            return;
        }

        showAvailableTables();

        Reservation newReservation;
        cout << YELLOW << "\nEnter customer name: " << RESET;
        cin.ignore();
        getline(cin, newReservation.customerName);

        cout << YELLOW << "Enter reservation time (e.g., 19:00): " << RESET;
        cin >> newReservation.reservationTime;

        for (int i = 1; i <= totalTables; ++i) {
            bool tableAvailable = true;
            for (const auto& res : reservations) {
                if (res.tableNumber == i) {
                    tableAvailable = false;
                    break;
                }
            }

            if (tableAvailable) {
                newReservation.tableNumber = i;
                reservations.push_back(newReservation);
                cout << GREEN << "\nReservation confirmed! Table number: " << i << RESET << "\n";
                saveReservationsToFile();
                return;
            }
        }
    }

    void viewReservations() {
        if (reservations.empty()) {
            cout << RED << "\nNo reservations found!" << RESET << "\n";
            return;
        }

        printHeader("Current Reservations");
        cout << left << setw(20) << "Customer" << setw(10) << "Table" << setw(10) << "Time" << "\n";
        cout << string(40, '-') << "\n";

        for (const auto& res : reservations) {
            cout << left << setw(20) << res.customerName << setw(10) << res.tableNumber << setw(10) << res.reservationTime << "\n";
        }
    }

    void cancelReservation() {
        string name;
        cout << YELLOW << "\nEnter the customer name to cancel reservation: " << RESET;
        cin.ignore();
        getline(cin, name);

        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if (it->customerName == name) {
                cout << GREEN << "\nReservation for " << it->customerName << " has been canceled." << RESET << "\n";
                reservations.erase(it);
                saveReservationsToFile();
                return;
            }
        }

        cout << RED << "\nNo reservation found for the given name!" << RESET << "\n";
    }

    void manageReservationsMenu() {
        int subChoice;
        do {
            printHeader("Reservation Management Menu");
            cout << "1. Make a Reservation\n";
            cout << "2. View Reservations\n";
            cout << "3. Cancel a Reservation\n";
            cout << "4. Back to Main Menu\n";
            cout << YELLOW << "Enter your choice: " << RESET;
            cin >> subChoice;

            switch (subChoice) {
            case 1:
                makeReservation();
                break;
            case 2:
                viewReservations();
                break;
            case 3:
                cancelReservation();
                break;
            case 4:
                cout << GREEN << "\nReturning to Main Menu." << RESET << "\n";
                break;
            default:
                cout << RED << "\nInvalid choice! Please try again." << RESET << "\n";
            }
        } while (subChoice != 4);
    }

    void mainMenu() {
        int choice;
        do {
            cout << CYAN << "\n+" << string(40, '-') << "+\n";
            cout << "| " << setw(38) << left << "Restaurant Management System" << " |\n";
            cout << "+" << string(40, '-') << "+\n";
            cout << RESET;

            cout << "1. Manage Reservations\n";
            cout << "2. View Menu\n";
            cout << "3. Admin Panel\n";
            cout << "4. Exit\n";
            cout << YELLOW << "Enter your choice: " << RESET;
            cin >> choice;

            switch (choice) {
            case 1:
                manageReservationsMenu();
                break;
            case 2:
                viewMenu();
                break;
            case 3:
                adminPanel();
                break;
            case 4:
                cout << GREEN << "\nExiting system. Goodbye!" << RESET << "\n";
                break;
            default:
                cout << RED << "\nInvalid choice! Please try again." << RESET << "\n";
            }
        } while (choice != 4);
    }
};

int main() {
    setlocale(LC_ALL, "Turkish"); 
    Restaurant restaurant;
    restaurant.mainMenu();
    return 0;
}

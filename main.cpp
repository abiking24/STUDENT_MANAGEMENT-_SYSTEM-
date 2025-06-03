#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
public:
    int roll_no;
    string name, course, quali, phone_no, address;
    Node* next;
    Node* prev;
};

class LinkedList {
private:
    Node* head;
    Node* tail;

    void saveToFile() {
        ofstream file("Students.txt");
        Node* temp = head;
        while (temp != NULL) {
            file << temp->roll_no << "\n"
                 << temp->name << "\n"
                 << temp->course << "\n"
                 << temp->quali << "\n"
                 << temp->phone_no << "\n"
                 << temp->address << "\n\n";
            temp = temp->next;
        }
        file.close();
    }

    bool validatePhone(const string& phone) {
        if (phone.length() < 10) return false;
        for (char c : phone) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

public:
    LinkedList() : head(NULL), tail(NULL) {
        loadFromFile();
    }

    ~LinkedList() {
        Node* current = head;
        while (current != NULL) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void loadFromFile() {
        ifstream file("Students.txt");
        if (!file) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            Node* new_node = new Node();
            try { new_node->roll_no = stoi(line); }
            catch (...) { delete new_node; continue; }

            getline(file, new_node->name);
            getline(file, new_node->course);
            getline(file, new_node->quali);
            getline(file, new_node->phone_no);
            getline(file, new_node->address);

            while (file.peek() == '\n') file.ignore();

            new_node->next = NULL;
            new_node->prev = tail;

            if (head == NULL) {
                head = tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
        }
        file.close();
    }

    bool isIDUnique(int id) {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->roll_no == id) return false;
            temp = temp->next;
        }
        return true;
    }
    


    void insert() {
        Node* new_node = new Node();
        int id;

        while (true) {
            cout << "\nEnter Student ID (0 to cancel): ";
            while (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid numeric ID: ";
            }

            if (id == 0) {
                delete new_node;
                cout << "Insertion cancelled.\n";
                return;
            }

            if (!isIDUnique(id)) {
                cout << "This ID already exists. Please enter a unique ID.\n";
            } else {
                break;
            }
        }

        new_node->roll_no = id;

        cout << "Enter Student Name (0 to cancel): ";
        cin.ignore();
        getline(cin, new_node->name);
        if (new_node->name == "0") {
            delete new_node;
            cout << "Insertion cancelled.\n";
            return;
        }

        cout << "Enter Course (0 to cancel): ";
        getline(cin, new_node->course);
        if (new_node->course == "0") {
            delete new_node;
            cout << "Insertion cancelled.\n";
            return;
        }

        cout << "Enter Qualification (0 to cancel): ";
        getline(cin, new_node->quali);
        if (new_node->quali == "0") {
            delete new_node;
            cout << "Insertion cancelled.\n";
            return;
        }

while (true) {
            cout << "Enter Phone No (10+ digits, 0 to cancel): ";
            getline(cin, new_node->phone_no);
            if (new_node->phone_no == "0") {
                delete new_node;
                cout << "Insertion cancelled.\n";
                return;
            }
            if (validatePhone(new_node->phone_no)) break;
            cout << "Invalid phone number. Must be digits only and at least 10 digits.\n";
        }

        cout << "Enter Address (0 to cancel): ";
        getline(cin, new_node->address);
        if (new_node->address == "0") {
            delete new_node;
            cout << "Insertion cancelled.\n";
            return;
        }

        new_node->next = NULL;
        new_node->prev = tail;

        if (head == NULL) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        saveToFile();
        cout << "\nRecord Inserted Successfully!\n";
    }
     

   

    void search() {
        if (head == NULL) {
            cout << "\nList is Empty!\n";
            return;
        }

        int choice;
        cout << "\nSearch by:\n";
        cout << "1. Student ID\n";
        cout << "2. Name\n";
        cout << "3. Course\n";
        cout << "4. Qualification\n";
        cout << "0. Cancel\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Search cancelled.\n";
            return;
        }

        cin.ignore();
        string searchTerm;
        vector<Node*> results;

        switch (choice) {
            case 1: {
                int id;
                cout << "Enter Student ID: ";
                cin >> id;
                cin.ignore();
                Node* temp = head;
                while (temp != NULL) {
                    if (temp->roll_no == id) {
                        results.push_back(temp);
                        break;
                    }
                    temp = temp->next;
                }
                break;
            }
            case 2: {
                cout << "Enter Name: ";
                getline(cin, searchTerm);
                Node* temp = head;
                while (temp != NULL) {
                    if (temp->name.find(searchTerm) != string::npos) {
                        results.push_back(temp);
                    }
                    temp = temp->next;
                }
                break;
            }
            case 3: {
                cout << "Enter Course: ";
                getline(cin, searchTerm);
                Node* temp = head;
                while (temp != NULL) {
                    if (temp->course.find(searchTerm) != string::npos) {
                        results.push_back(temp);
                    }
                    temp = temp->next;
                }
                break;
            }
            case 4: {
                cout << "Enter Qualification: ";
                getline(cin, searchTerm);
                Node* temp = head;
                while (temp != NULL) {
                    if (temp->quali.find(searchTerm) != string::npos) {
                        results.push_back(temp);
                    }
                    temp = temp->next;
                }
                break;
            }
            default:
                cout << "Invalid choice!\n";
                return;
        }

        if (results.empty()) {
            cout << "\nNo matching records found!\n";
            return;
        }

        cout << "\nFound " << results.size() << " matching record(s):\n";
        cout << "----------------------------------------\n";
        for (Node* node : results) {
            cout << "ID: " << node->roll_no << endl
                 << "Name: " << node->name << endl

<< "Course: " << node->course << endl
                 << "Qualification: " << node->quali << endl
                 << "Phone: " << node->phone_no << endl
                 << "Address: " << node->address << endl
                 << "----------------------------------------\n";
        }
    }


    
    void count() {
        int count = 0;
        Node* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        cout << "\nTotal Records: " << count << endl;
    }

    void update() {
        if (head == NULL) {
            cout << "\nList is Empty!\n";
            return;
        }

        int id;
        cout << "\nEnter Student ID to Update (0 to cancel): ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid numeric ID: ";
        }

        if (id == 0) {
            cout << "Update cancelled.\n";
            return;
        }

        Node* temp = head;
        while (temp != NULL) {
            if (temp->roll_no == id) {
                string input;
                cout << "\nEnter New Details (press Enter to keep current value, 0 to cancel):\n";

                cout << "Name [" << temp->name << "]: ";
                cin.ignore();
                getline(cin, input);
                if (input == "0") {
                    cout << "Update cancelled.\n";
                    return;
                }
                if (!input.empty()) temp->name = input;

                cout << "Course [" << temp->course << "]: ";
                getline(cin, input);
                if (input == "0") {
                    cout << "Update cancelled.\n";
                    return;
                }
                if (!input.empty()) temp->course = input;

                cout << "Qualification [" << temp->quali << "]: ";
                getline(cin, input);
                if (input == "0") {
                    cout << "Update cancelled.\n";
                    return;
                }
                if (!input.empty()) temp->quali = input;

                while (true) {
                    cout << "Phone No [" << temp->phone_no << "]: ";
                    getline(cin, input);
                    if (input == "0") {
                        cout << "Update cancelled.\n";
                        return;
                    }
                    if (input.empty()) break;
                    if (validatePhone(input)) {
                        temp->phone_no = input;
                        break;
                    }
                    cout << "Invalid phone number. Must be digits only and at least 10 digits.\n";
                }

                cout << "Address [" << temp->address << "]: ";
                getline(cin, input);
                if (input == "0") {
                    cout << "Update cancelled.\n";
                    return;
                }
                if (!input.empty()) temp->address = input;

                saveToFile();
                cout << "\nRecord Updated Successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "\nStudent Not Found!\n";
    }
    


    void deleteRecord() {
        if (head == NULL) {
            cout << "\nList is Empty!\n";
            return;
        }

        int id;
        cout << "\nEnter Student ID to Delete (0 to cancel): ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid numeric ID: ";
        }

        if (id == 0) {
            cout << "Deletion cancelled.\n";
            return;
        }
Node* temp = head;
        while (temp != NULL) {
            if (temp->roll_no == id) {
                if (temp == head) {
                    head = head->next;
                    if (head) head->prev = NULL;
                    else tail = NULL;
                } else if (temp == tail) {
                    tail = tail->prev;
                    tail->next = NULL;
                } else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }
                delete temp;
                saveToFile();
                cout << "\nRecord Deleted Successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "\nStudent Not Found!\n";
    }

    

   void showAll() {
        if (head == NULL) {
            cout << "\nList is Empty!\n";
            return;
        }

        int sortChoice;
        cout << "\nSort by:\n";
        cout << "1. ID (Ascending)\n";
        cout << "2. ID (Descending)\n";
        cout << "3. Name (A-Z)\n";
        cout << "4. Name (Z-A)\n";
        cout << "0. Cancel\n";
        cout << "Enter choice: ";
        cin >> sortChoice;

        if (sortChoice == 0) {
            cout << "Operation cancelled.\n";
            return;
        }

        // Collect all nodes
        vector<Node*> nodes;
        Node* temp = head;
        while (temp != NULL) {
            nodes.push_back(temp);
            temp = temp->next;
        }

        // Sort based on choice
        switch (sortChoice) {
            case 1:
                sort(nodes.begin(), nodes.end(),
                    [](Node* a, Node* b) { return a->roll_no < b->roll_no; });
                break;
            case 2:
                sort(nodes.begin(), nodes.end(),
                    [](Node* a, Node* b) { return a->roll_no > b->roll_no; });
                break;
            case 3:
                sort(nodes.begin(), nodes.end(),
                    [](Node* a, Node* b) { return a->name < b->name; });
                break;
            case 4:
                sort(nodes.begin(), nodes.end(),
                    [](Node* a, Node* b) { return a->name > b->name; });
                break;
            default:
                cout << "Invalid choice. Showing unsorted list.\n";
        }

        cout << "\nAll Student Records (" << nodes.size() << " records):\n";
        cout << "----------------------------------------\n";
        for (Node* node : nodes) {
            cout << "ID: " << node->roll_no << endl
                 << "Name: " << node->name << endl
                 << "Course: " << node->course << endl
                 << "Qualification: " << node->quali << endl
                 << "Phone: " << node->phone_no << endl
                 << "Address: " << node->address << endl
                 << "----------------------------------------\n";
        }
    }
};


int main() {
    LinkedList list;
    int choice;

    do {
        system("cls");
        cout << "\nSTUDENT MANAGEMENT SYSTEM";
        cout << "\n1. Insert Record";
        cout << "\n2. Search Record";
        cout << "\n3. Count Records";
        cout << "\n4. Update Record";
        cout << "\n5. Delete Record";
        cout << "\n6. Show All Records";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";

        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 7: ";
        }

        switch (choice) {
            case 1: list.insert(); break;
            case 2: list.search(); break;
            case 3: list.count(); break;
            case 4: list.update(); break;
            case 5: list.deleteRecord(); break;
            case 6: list.showAll(); break;
            case 7: exit(0);
            default: cout << "\nInvalid Choice!";
        }

        cout << "\nPress any key to continue...";
        getch();
    } while (true);

    return 0;
}
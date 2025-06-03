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
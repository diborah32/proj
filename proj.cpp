#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Define a structure for Contact
struct Contact {
    string name;
    long long phone;
    string email;
};

// Function Prototypes
void addContact();
void viewContacts();
void deleteContacts();
void editContact();
void deleteSingleContact();
void clearInput();

// Function to add a new contact
void addContact() {
    ofstream file("contacts.txt", ios::app);
    if (!file) {
        cout << "Error opening the file! Make sure the file path is correct.\n";
        return;
    }

    Contact contact;
    cout << "\nEnter the contact details below:\n";

    cin.ignore();
    cout << "Name: ";
    getline(cin, contact.name);
    cout << "Phone: ";
    cin >> contact.phone;
    cin.ignore();
    cout << "Email: ";
    getline(cin, contact.email);

    file << contact.name << "," << contact.phone << "," << contact.email << endl;
    cout << "\nContact added successfully!\n";

    file.close();
}

// Function to view all contacts
void viewContacts() {
    ifstream file("contacts.txt");
    if (!file) {
        cout << "Error: Contacts file not found!\n";
        return;
    }
    if (file.peek() == EOF) {
        cout << "No contacts to display.\n";
        return;
    }

    string line;
    cout << "\n--- Your Contacts ---\n";
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');

        if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) {
            continue;
        }

        Contact contact;
        contact.name = line.substr(0, pos1);
        contact.phone = stoll(line.substr(pos1 + 1, pos2 - pos1 - 1));
        contact.email = line.substr(pos2 + 1);

        cout << "Name: " << contact.name
             << "\nPhone: " << contact.phone
             << "\nEmail: " << contact.email
             << "\n-----------------\n";
    }

    file.close();
}

// Function to delete all contacts
void deleteContacts() {
    ofstream file("contacts.txt", ios::trunc);
    if (!file) {
        cout << "Error clearing contacts!\n";
        return;
    }

    cout << "All contacts have been deleted!\n";
    file.close();
}

// Function to edit a contact using email as an identifier
void editContact() {
    ifstream file("contacts.txt");
    if (!file) {
        cout << "Error: Contacts file not found!\n";
        return;
    }
    if (file.peek() == EOF) {
        cout << "No contacts available to edit.\n";
        file.close();
        return;
    }

    vector<Contact> contacts;
    string line, emailToEdit;
    bool found = false;

    cout << "\nEnter the email of the contact to edit: ";
    cin.ignore();
    getline(cin, emailToEdit);

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');

        if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) {
            continue;
        }

        Contact contact;
        contact.name = line.substr(0, pos1);
        contact.phone = stoll(line.substr(pos1 + 1, pos2 - pos1 - 1));
        contact.email = line.substr(pos2 + 1);

        if (contact.email == emailToEdit) {
            found = true;
            cout << "\nEditing Contact: " << contact.name << endl;
            cout << "New Name: ";
            getline(cin, contact.name);
            cout << "New Phone: ";
            cin >> contact.phone;
            cin.ignore();
            cout << "New Email: ";
            getline(cin, contact.email);
        }

        contacts.push_back(contact);
    }

    file.close();

    if (!found) {
        cout << "Contact not found!\n";
        return;
    }

    ofstream outFile("contacts.txt", ios::trunc);
    if (!outFile) {
        cout << "Error updating contacts!\n";
        return;
    }

    for (const auto &contact : contacts) {
        outFile << contact.name << "," << contact.phone << "," << contact.email << endl;
    }
    outFile.close();
    cout << "Contact updated successfully!\n";
}

// Function to delete a single contact using email
void deleteSingleContact() {
    ifstream file("contacts.txt");
    if (!file) {
        cout << "Error: Contacts file not found!\n";
        return;
    }
    if (file.peek() == EOF) {
        cout << "No contacts available to delete.\n";
        file.close();
        return;
    }

    vector<Contact> contacts;
    string line, emailToDelete;
    bool found = false;

    cout << "\nEnter the email of the contact to delete: ";
    cin.ignore();
    getline(cin, emailToDelete);

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');

        if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) {
            continue;
        }

        Contact contact;
        contact.name = line.substr(0, pos1);
        contact.phone = stoll(line.substr(pos1 + 1, pos2 - pos1 - 1));
        contact.email = line.substr(pos2 + 1);

        if (contact.email == emailToDelete) {
            found = true;
            cout << "Contact '" << contact.name << "' deleted successfully!\n";
        } else {
            contacts.push_back(contact);
        }
    }

    file.close();

    if (!found) {
        cout << "Contact not found!\n";
        return;
    }

    ofstream outFile("contacts.txt", ios::trunc);
    if (!outFile) {
        cout << "Error updating contacts!\n";
        return;
    }

    for (const auto &contact : contacts) {
        outFile << contact.name << "," << contact.phone << "," << contact.email << endl;
    }
    outFile.close();
}

// Function to handle invalid inputs
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Main function
int main() {
    int choice;

    do {
        cout << "\n--- Contact Management System ---\n";
        cout << "1. Adding New Contact\n";
        cout << "2. View All Contacts\n";
        cout << "3. Edit a Contact\n";
        cout << "4. Delete a Contact\n";
        cout << "5. Delete All Contacts\n";
        cout << "6. Exit\n";
        cout << "Please select an option (1-6): ";

        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input! Please enter a number between 1 and 6.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteSingleContact();
                break;
            case 5:
                deleteContacts();
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 6.\n";
        }

    } while (choice != 6);

    return 0;
}
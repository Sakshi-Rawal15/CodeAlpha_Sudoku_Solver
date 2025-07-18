#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// Function to check if a username already exists
bool usernameExists(const string &username)
{
    ifstream file("users.txt");
    string line;
    while (getline(file, line))
    {
        if (line.substr(0, line.find(':')) == username)
        {
            return true;
        }
    }
    return false;
}

// Function to register a new user
void registerUser()
{
    string username, password;

    cout << "\n===== Registration =====" << endl;
    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists
    if (usernameExists(username))
    {
        cout << "Username already exists! Please choose another." << endl;
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Save to file
    ofstream file("users.txt", ios::app);
    if (file.is_open())
    {
        file << username << ":" << password << endl;
        cout << "Registration successful!" << endl;
    }
    else
    {
        cout << "Error saving user data!" << endl;
    }
}

// Function to login existing user
void loginUser()
{
    string username, password;

    cout << "\n===== Login =====" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t pos = line.find(':');
        string storedUser = line.substr(0, pos);
        string storedPass = line.substr(pos + 1);

        if (storedUser == username && storedPass == password)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        cout << "\nLogin successful! Welcome, " << username << "!" << endl;
    }
    else
    {
        cout << "\nInvalid username or password!" << endl;
    }
}

int main()
{
    int choice;

    while (true)
    {
        cout << "\n===== User System =====";
        cout << "\n1. Register";
        cout << "\n2. Login";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";

        // Handle invalid input
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}
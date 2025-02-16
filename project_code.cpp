#include <iostream>
#include <fstream>
#include <string>
#include <limits> // Required for numeric_limits

using namespace std;

bool registerUser();
bool signIn();

int main()
{
    int choice;

    while (true)
    {
        cout << "------ Welcome to the Bus Reservation System------\n\n";
        cout << "1. Register\n2. Log In\n3. Exit\n\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == 1)
        {
            if (registerUser())
            {
                cout << "Registration successful! You can now log in." << endl;
            }
        }
        else if (choice == 2)
        {
            if (signIn())
            {
                cout << "Login successful! Welcome! Now You can book your tickets." << endl;
            }
            else
            {
                cout << "Invalid username or password." << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Thank you for using the Bus Reservation System! Goodbye!" << endl;
            return 0; // Exit the program
        }
        else
        {
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}

bool registerUser()
{
    string username, password;

    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    ifstream infile("users.txt");
    string u, p;
    while (infile >> u >> p)
    {
        if (u == username)
        {
            cout << "Username already exists. Try a different one." << endl;
            infile.close();
            return false;
        }
    }
    infile.close();

    ofstream outfile("users.txt", ios::app);
    outfile << username << " " << password << endl;
    outfile.close();

    return true;
}

bool signIn()
{
    string username, password;

    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    ifstream infile("users.txt");
    string u, p;
    while (infile >> u >> p)
    {
        if (u == username && p == password)
        {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}
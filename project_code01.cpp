#include <chrono>
#include <iostream>
#include <regex> // For email validation
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_map<string, string> userCredentials; // Store email and password
unordered_set<string> registeredContacts;

// Structure to hold ticket information
struct Ticket {
  string type;     // "Bus", "Train", or "Plane"
  string details;  // Event details
  int availableSeats;
};

// Vector to store available tickets
vector<Ticket> availableTickets = {
    {"Bus", "Dhaka to Chittagong - 10:00 AM", 45},
    {"Bus", "Dhaka to Jashore - 10:00 AM", 45},
    {"Bus", "Dhaka to Khulna - 11:00 PM", 20},
    {"Plane", "Dhaka to Jashore - 10:00 AM", 15},
    {"Plane", "Dhaka to Cox's Bazar - 1:00 PM", 15},
    {"Train", "Dhaka to Rajshahi - 8:30 PM", 30},
    {"Train", "Dhaka to Jashore - 10:00 AM", 55},
    {"Train", "Dhaka to Sylhet - 6:00 AM", 55},
};

bool isPasswordValid(const string &password, const string &confirmPassword) {
  return password == confirmPassword;
}

bool isUniqueRegistration(const string &email, const string &contact) {
  return userCredentials.find(email) == userCredentials.end() &&
         registeredContacts.find(contact) == registeredContacts.end();
}

bool isValidEmail(const string &email) {
  const regex pattern(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
  return regex_match(email, pattern);
}

void showTicketOptions() {
  cout << "\nWelcome to Swift Book! Now choose your desired options:\n";
  cout << "1. View Available Tickets\n";
  cout << "2. Book Ticket\n";
  cout << "3. Logout\n";
  cout << "4. Exit\n";
  cout << "Enter your choice: ";
}

void displayAvailableTickets() {
  cout << "\nAvailable Tickets:\n";
  cout << "1. Bus\n";
  cout << "2. Train\n";
  cout << "3. Plane\n";
  cout << "Enter your choice (or 0 to go back): ";

  int choice;
  cin >> choice;
  cin.ignore(); // To handle newline character

  if (choice == 0) {
    return; // Go back to the main menu
  }

  string selectedType;
  switch (choice) {
  case 1:
    selectedType = "Bus";
    break;
  case 2:
    selectedType = "Train";
    break;
  case 3:
    selectedType = "Plane";
    break;
  default:
    cout << "\nInvalid choice. Please try again.\n";
    return;
  }

  cout << "\nAvailable " << selectedType << " Tickets:\n";
  bool ticketsFound = false;
  for (size_t i = 0; i < availableTickets.size(); ++i) {
    if (availableTickets[i].type == selectedType) {
      cout << i + 1 << ". Details: " << availableTickets[i].details
           << ", Available Seats: " << availableTickets[i].availableSeats
           << endl;
      ticketsFound = true;
    }
  }

  if (!ticketsFound) {
    cout << "No " << selectedType << " tickets available at the moment.\n";
  }
}

void bookTicket() {
  cout << "\nBook Ticket:\n";
  cout << "1. Bus\n";
  cout << "2. Train\n";
  cout << "3. Plane\n";
  cout << "Enter your choice (or 0 to go back): ";

  int choice;
  cin >> choice;
  cin.ignore(); // To handle newline character

  if (choice == 0) {
    return; // Go back to the main menu
  }

  string selectedType;
  switch (choice) {
  case 1:
    selectedType = "Bus";
    break;
  case 2:
    selectedType = "Train";
    break;
  case 3:
    selectedType = "Plane";
    break;
  default:
    cout << "\nInvalid choice. Please try again.\n";
    return;
  }

  cout << "\nAvailable " << selectedType << " Tickets:\n";
  vector<int> validTicketIndices;
  for (size_t i = 0; i < availableTickets.size(); ++i) {
    if (availableTickets[i].type == selectedType) {
      cout << i + 1 << ". Details: " << availableTickets[i].details
           << ", Available Seats: " << availableTickets[i].availableSeats
           << endl;
      validTicketIndices.push_back(i);
    }
  }

  if (validTicketIndices.empty()) {
    cout << "No " << selectedType << " tickets available at the moment.\n";
    return;
  }

  cout << "\nEnter the number of the ticket you want to book: ";
  cin >> choice;
  cin.ignore(); // To handle newline character

  if (choice > 0 && choice <= validTicketIndices.size()) {
    int ticketIndex = validTicketIndices[choice - 1];
    cout << "\nYou have chosen to book the following ticket:\n";
    cout << "Type: " << availableTickets[ticketIndex].type
         << ", Details: " << availableTickets[ticketIndex].details
         << ", Available Seats: "
         << availableTickets[ticketIndex].availableSeats << endl;

    // Add ticket booking logic here (e.g., reduce available seats, etc.)
    cout << "Ticket booked successfully!\n";
  } else {
    cout << "\nInvalid choice. Please try again.\n";
  }
}

void login() {
  string email, password;
  int attempts = 0;

  while (attempts < 3) {
    cout << "\nEnter Email: ";
    getline(cin, email);
    cout << "Enter Password: ";
    getline(cin, password);

    if (userCredentials.find(email) != userCredentials.end() &&
        userCredentials[email] == password) {
      cout << "\nLogin Successful!\n";

      while (true) {
        showTicketOptions();
        int choice;
        cin >> choice;
        cin.ignore(); // To handle newline character

        switch (choice) {
        case 1:
          displayAvailableTickets();
          break;
        case 2:
          bookTicket();
          break;
        case 3:
          cout << "\nLogging out...\n";
          return; // Exit the ticket options to return to the main menu
        case 4:
          cout << "\nThank you for using Swift Book. Goodbye!\n";
          exit(0); // Exit the program
        default:
          cout << "\nInvalid choice. Please try again.\n";
        }
      }
    } else {
      cout << "\nIncorrect Email or Password. Try again.\n";
      attempts++;
    }
  }
  cout << "\nToo many failed attempts. Please try again later.\n";
}

void registerUser() {
  string name, email, contact, address, nid, password, confirmPassword;

  cout << "Enter your Name: ";
  getline(cin, name);

  cout << "Enter your Email: ";
  getline(cin, email);
  if (!isValidEmail(email)) {
    cout << "\nInvalid email format. Please try again.\n";
    return;
  }

  cout << "Enter your Contact Number: ";
  getline(cin, contact);

  if (!isUniqueRegistration(email, contact)) {
    cout << "\nThis email or contact number is already registered. Please use a "
            "different one.\n";
    return;
  }

  cout << "Enter your Address: ";
  getline(cin, address);

  cout << "Enter your National ID (NID): ";
  getline(cin, nid);

  cout << "Enter your Password: ";
  getline(cin, password);

  cout << "Confirm your Password: ";
  getline(cin, confirmPassword);

  if (isPasswordValid(password, confirmPassword)) {
    userCredentials[email] = password;
    registeredContacts.insert(contact);
    cout << "\nRegistration Successful\n";
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Contact: " << contact << endl;
    cout << "Address: " << address << endl;
    cout << "NID: " << nid << endl;
  } else {
    cout << "\nPassword mismatch! Please try again.\n";
  }
}

int main() {
  cout << "\nWelcome to Swift Book. Fastest Online Ticket Reservation "
          "System\n";

  while (true) {
    cout << "\nChoose an option:\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore(); // To handle newline character

    switch (choice) {
    case 1:
      registerUser();
      break;
    case 2:
      login();
      break;
    case 3:
      cout << "\nThank you for using Swift Book. Goodbye!\n";
      return 0;
    default:
      cout << "\nInvalid choice. Please try again.\n";
    }
  }
}
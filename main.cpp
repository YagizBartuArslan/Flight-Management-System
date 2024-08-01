#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <climits> // For INT_MAX
#include <functional> // For std::function


// Author: Yaðýz Bartu Arslan - Junior Computer Engineer Student at Sabanci University
// Written in 29.12.2023
using namespace std;

struct flight {
    string from;
    string to;
    int hour;
    int min;
    int price;
    int ID;

    flight* next;
    flight* prev;

    flight();
    flight(string from, string to, int hour, int min, int price, int ID);
};

// Flight struct constructors
flight::flight() {
    this->from = "";
    this->to = "";
    this->hour = 0;
    this->min = 0;
    this->price = 0;
    this->ID = 0;
    this->next = nullptr;
    this->prev = nullptr;
}

flight::flight(string from, string to, int hour, int min, int price, int ID) {
    this->from = from;
    this->to = to;
    this->hour = hour;
    this->min = min;
    this->price = price;
    this->ID = ID;
    this->next = nullptr;
    this->prev = nullptr;
}

struct airline {
    string name;
    int ID;
    airline* next;
    flight* flights;

    airline();
    airline(string name, int ID);
};

// Airline struct constructors
airline::airline() {
    this->name = "";
    this->ID = 0;
    this->next = nullptr;
    this->flights = nullptr;
}

airline::airline(string name, int ID) {
    this->name = name;
    this->ID = ID;
    this->next = nullptr;
    this->flights = nullptr;
}

bool input_done = false;
airline* head = nullptr;

pair<vector<string>, vector<vector<flight>>> read_files() {
    vector<string> airlines;
    vector<vector<flight>> flights(100);

    while (!input_done) {
        string airline_name;
        string filename;
        cout << "Enter the name of airline: ";
        cin >> airline_name;
        cout << "Enter the name of airline file: ";
        cin >> filename;
        ifstream input(filename);

        if (filename == "done") {
            input_done = true;
            return make_pair(airlines, flights);
        }

        while (input.fail()) {
            cout << "Could not open file: " << filename << endl;
            cout << "Enter the name of airline: ";
            cin >> airline_name;
            cout << "Enter the name of airline file: ";
            cin >> filename;
            input.open(filename);

            if (filename == "done") {
                input_done = true;
                return make_pair(airlines, flights);
            }
        }

        airlines.push_back(airline_name);
        cout << "Processing input file: " << filename << endl;

        int line_no = 0;
        vector<string> lines;
        string line;
        int vector_location = airlines.size() - 1;
        while (getline(input, line)) {
            lines.push_back(line);
            line_no += 1;
            if (line_no % 5 == 0) {
                flight a_flight(lines[line_no - 5], lines[line_no - 4], stoi(lines[line_no - 3]), stoi(lines[line_no - 2]), stoi(lines[line_no - 1]), line_no / 5);
                flights[vector_location].push_back(a_flight);
            }
        }
    }
    if (input_done) {
        cout << "Input files are already read, however you can do manual changes.." << endl;
    }

    return make_pair(airlines, flights);
}

// Function to create linked list structure
airline* make_linked_list_structure(vector<string> airlines, vector<vector<flight>> flights) {
    airline* head = nullptr;
    airline* last = nullptr;

    for (int i = 0; i < airlines.size(); i++) {
        airline* newAirline = new airline(airlines[i], i);

        if (head == nullptr) {
            head = newAirline;
            last = newAirline;
        }
        else {
            last->next = newAirline;
            last = newAirline;
        }

        flight* lastFlight = nullptr;

        for (int j = 0; j < flights[i].size(); j++) {
            flight* newFlight = new flight(flights[i][j].from, flights[i][j].to, flights[i][j].hour, flights[i][j].min, flights[i][j].price, flights[i][j].ID);

            if (newAirline->flights == nullptr) {
                newAirline->flights = newFlight;
                lastFlight = newFlight;
            }
            else {
                lastFlight->next = newFlight;
                newFlight->prev = lastFlight;
                lastFlight = newFlight;
            }
        }
    }

    return head;
}

void print_all(airline* head) {
    airline* currentAirline = head;
    while (currentAirline != nullptr) {
        cout << "AIRLINE ID: " << currentAirline->ID << endl;
        cout << "NAME: " << currentAirline->name << endl;
        cout << "FLIGHTS: ";
        flight* currentFlight = currentAirline->flights;
        while (currentFlight != nullptr) {
            cout << "#" << currentFlight->ID << "|" << currentFlight->from << "->" << currentFlight->to << "|"
                << currentFlight->hour << ":" << currentFlight->min << "|" << currentFlight->price << "TRY ";
            currentFlight = currentFlight->next;
        }
        cout << "#" << endl;
        currentAirline = currentAirline->next;
    }
}

void add_flight_with_input(airline*& head) {
    string airlineName, from, to;
    int hour, min, price;

    cout << "Adding manual entry:" << endl;
    cout << "AIRLINE: ";
    cin >> airlineName;
    cout << "FROM: ";
    cin >> from;
    cout << "TO: ";
    cin >> to;
    cout << "HOUR: ";
    cin >> hour;
    cout << "MIN: ";
    cin >> min;
    cout << "PRICE: ";
    cin >> price;

    // Find the airline
    airline* currentAirline = head;
    while (currentAirline != nullptr && currentAirline->name != airlineName) {
        currentAirline = currentAirline->next;
    }

    // if no airline -> create one
    if (currentAirline == nullptr) {
        currentAirline = new airline(airlineName, 0); // -> unique ID
        // Add the new airline to the list
        if (head == nullptr) {
            head = currentAirline;
        }
        else {
            airline* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            last->next = currentAirline;
        }
        cout << "New airline " << airlineName << endl;
    }

    // Create a new flight
    flight* newFlight = new flight(from, to, hour, min, price, 0);

    if (currentAirline->flights == nullptr || (currentAirline->flights->hour > hour || (currentAirline->flights->hour == hour && currentAirline->flights->min > min))) {
        // Add at the beginning
        newFlight->next = currentAirline->flights;
        if (currentAirline->flights != nullptr) {
            currentAirline->flights->prev = newFlight;
        }
        currentAirline->flights = newFlight;
    }
    else {
        // Add in the middle or at the end
        flight* currentFlight = currentAirline->flights;
        while (currentFlight->next != nullptr && (currentFlight->next->hour < hour || (currentFlight->next->hour == hour && currentFlight->next->min < min))) {
            currentFlight = currentFlight->next;
        }
        newFlight->next = currentFlight->next;
        newFlight->prev = currentFlight;
        if (currentFlight->next != nullptr) {
            currentFlight->next->prev = newFlight;
        }
        currentFlight->next = newFlight;
    }
}

void remove_flight_with_input(airline*& head) {
    int id;

    cout << "Flight id to remove: ";
    cin >> id;

    // Find and remove the flight
    airline* prevAirline = nullptr;
    airline* currentAirline = head;

    while (currentAirline != nullptr) {
        flight* prevFlight = nullptr;
        flight* currentFlight = currentAirline->flights;

        while (currentFlight != nullptr) {
            if (currentFlight->ID == id) {  // Found the flight to remove
                if (prevFlight == nullptr) {  // The flight is at the beginning of the list
                    if (currentFlight->next == nullptr) {  // The flight is also at the end of the list
                        delete(currentFlight);
                        if (prevAirline == nullptr) {  // The airline is at the beginning of the list
                            head = head->next;
                        }
                        else {  // The airline is in the middle or at the end of the list
                            prevAirline->next = currentAirline->next;
                        }
                        delete(currentAirline);
                        cout << "Removing airline " << currentAirline->name << endl;
                    }
                    else {  // The flight is at the beginning of the list but not at the end
                        currentAirline->flights = currentFlight->next;
                        currentFlight->next->prev = nullptr;
                        delete(currentFlight);
                    }
                }
                else if (currentFlight->next == nullptr) {  // The flight is at the end of the list but not at the beginning
                    prevFlight->next = nullptr;
                    delete(currentFlight);
                }
                else {  // The flight is in the middle of the list
                    prevFlight->next = currentFlight->next;
                    currentFlight->next->prev = prevFlight;
                    delete(currentFlight);
                }
                cout << "Removing flight id: " << id << endl;
                return;
            }
            prevFlight = currentFlight;
            currentFlight = currentFlight->next;
        }
        prevAirline = currentAirline;
        currentAirline = currentAirline->next;
    }

    cout << "There is no flight with id " << id << endl;
}

void pathfinder(airline* head) {
    string startLocation, destination;
    int maxTransfers;
    cout << "Where are you now? ";
    cin >> startLocation;
    cout << "Where do you want to go? ";
    cin >> destination;
    cout << "Maximum number of transfers: ";
    cin >> maxTransfers;

    // Initialize minimum cost to a large number and best path to an empty path
    int minCost = INT_MAX;
    vector<flight*> bestPath;

    // Helper function to recursively search for paths
    function<void(flight*, int, int, vector<flight*>&)> search = [&](flight* currentFlight, int currentCost, int currentTransfers, vector<flight*>& currentPath) {
        // If the current flight is null or the number of transfers exceeds the maximum, stop searching
        if (currentFlight == nullptr || currentTransfers > maxTransfers) {
            return;
        }

        // Add the current flight to the current path
        currentPath.push_back(currentFlight);

        // If the current flight reaches the destination and the current cost is less than the minimum cost, update the minimum cost and best path
        if (currentFlight->to == destination && currentCost < minCost) {
            minCost = currentCost;
            bestPath = currentPath;
        }

        // Recursively search for the next flight from the current location
        airline* currentAirline = head;
        while (currentAirline != nullptr) {
            flight* nextFlight = currentAirline->flights;
            while (nextFlight != nullptr) {
                if (nextFlight->from == currentFlight->to) {
                    search(nextFlight, currentCost + nextFlight->price, currentTransfers + 1, currentPath);
                }
                nextFlight = nextFlight->next;
            }
            currentAirline = currentAirline->next;
        }

        // Remove the current flight from the current path before backtracking
        currentPath.pop_back();
        };

    // Start the search from each flight in each airline
    airline* currentAirline = head;
    while (currentAirline != nullptr) {
        flight* currentFlight = currentAirline->flights;
        while (currentFlight != nullptr) {
            if (currentFlight->from == startLocation) {
                vector<flight*> currentPath;
                search(currentFlight, currentFlight->price, 0, currentPath);
            }
            currentFlight = currentFlight->next;
        }
        currentAirline = currentAirline->next;
    }

    // Print the best path
    cout << "##Best price path##" << endl;
    for (flight* f : bestPath) {
        cout << "[" << f->ID << "|" << f->from << "->" << f->to << "|" << f->hour << ":" << f->min << "|" << f->price << "]";
    }
    cout << " $TOTAL PRICE: " << minCost << endl;
}

void delete_linked_list(airline*& head) {
    airline* currentAirline = head;
    while (currentAirline != nullptr) {
        flight* currentFlight = currentAirline->flights;
        while (currentFlight != nullptr) {
            flight* nextFlight = currentFlight->next;
            delete(currentFlight);
            currentFlight = nextFlight;
        }
        airline* nextAirline = currentAirline->next;
        delete(currentAirline);
        currentAirline = nextAirline;
    }
    head = nullptr;
}

void printMainMenu() {
    cout << endl;
    cout << "I***********************************************I" << endl
        << "I               0 - DELETE DATA                 I" << endl
        << "I               1 - READ FILES                  I" << endl
        << "I               2 - PRINT ALL FLIGHTS           I" << endl
        << "I               3 - ADD FLIGHT                  I" << endl
        << "I               4 - REMOVE FLIGHT               I" << endl
        << "I               5 - PATH FINDER                 I" << endl
        << "I               6 - EXIT                        I" << endl
        << "I***********************************************I" << endl
        << ">>";
    cout << endl;
}

void processMainMenu() {
    pair<vector<string>, vector<vector<flight>>> lines_flights;

    char input;
    do {
        printMainMenu();
        cout << "Please enter your option " << endl;
        cin >> input;
        switch (input) {
        case '0':
            delete_linked_list(head);
            cout << "Data is deleted!" << endl;
            input_done = false;
            break;
        case '1':
            if (!input_done) {
                lines_flights = read_files();
                head = make_linked_list_structure(lines_flights.first, lines_flights.second);
                cout << "Files are read.." << endl;
            }
            else {
                cout << "Files are already read.." << endl;
            }
            input_done = true;
            break;
        case '2':
            print_all(head);
            break;
        case '3':
            add_flight_with_input(head);
            break;
        case '4':
            remove_flight_with_input(head);
            break;
        case '5':
            pathfinder(head);
            break;
        case '6':
            cout << "Exiting.." << endl;
            exit(0);
        default:
            cout << "Invalid option: please enter again" << endl;
        }
    } while (true);
}

int main() {
    processMainMenu();
    return 0;
}

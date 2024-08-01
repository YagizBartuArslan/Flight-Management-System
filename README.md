# Flight Management System

This project is a Flight Management System implemented in C++. It allows users to manage airlines and flights, including reading flight data from files, adding and removing flights, and finding paths with the best price between locations.

## Features

- **Read Flight Data**: Load flight data from files and store them in a linked list structure.
- **Add Flights**: Manually add new flights to the system.
- **Remove Flights**: Remove flights by their ID.
- **Path Finder**: Find the best price path between two locations with a specified maximum number of transfers.
- **Print All Flights**: Display all flights for each airline.

## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/yourusername/flight-management-system.git
    cd flight-management-system
    ```

2. **Compile the code**:
    ```sh
    g++ -o flight_management main.cpp
    ```

3. **Run the executable**:
    ```sh
    ./flight_management
    ```

## Usage

1. **Main Menu Options**:
    - `0`: Delete all data.
    - `1`: Read flight data from files.
    - `2`: Print all flights.
    - `3`: Add a flight manually.
    - `4`: Remove a flight by ID.
    - `5`: Find the best price path between two locations.
    - `6`: Exit the program.

2. **File Format**:
    - Each flight should be represented by 5 lines in the file:
        - From location
        - To location
        - Hour of departure
        - Minute of departure
        - Price of the flight

    Example:
    ```
    Istanbul
    Ankara
    14
    30
    150
    ```

## Contributing

Contributions are welcome! Please fork the repository and create a pull request with your changes.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the MIT License. See `LICENSE` for more information.


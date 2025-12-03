# DroneALPHA: Drone Route Planner 🇹🇷

## About the Project
This is a C++ simulation project. It plans a flight path for a drone named "ALPHA" to travel across provinces in Türkiye.

The goal is to visit the maximum number of cities starting from **Ankara**. The drone has a fuel limit and must follow specific rules.

## Key Features
* **Fuel Limit:** The drone can only travel **250 km** at a time.
* **Weather Check:** The drone skips cities with bad weather conditions.
* **Priority Cities:** Some cities are "Important". The drone tries to visit them first.
* **Smart Routing:** If the drone gets stuck (dead-end), it goes back (backtracking) to find a new path.

## Technical Details
In this project, I **did not** use standard C++ libraries (like `std::stack` or `std::vector`). I implemented my own data structures from scratch using static arrays.

* **Custom Stack:** Used for **Backtracking**. When the drone has no place to go, it uses the Stack to return to the previous city.
* **Custom Queue:** Used for **Route Management**. It lists the neighbor cities to decide where to go next.
* **Adjacency Matrix:** A 2D array used to store distance data between 81 cities.

## Input Files
The program reads data from these files:
* `distance_data.csv`: Distances between cities.
* `priority_provinces.txt`: List of important cities to visit.
* `weather_restricted_provinces.txt`: List of cities with bad weather (to avoid).

## How to Run
You can compile and run the code using a C++ compiler (like g++).

**1. Compile:**
```bash
g++ -std=c++11 *.cpp *.h -o DroneALPHA

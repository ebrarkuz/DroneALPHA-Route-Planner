#include "RoutePlanner.h"
#include <iostream>
#include <string>

int main() {

    // Parse the maximum allowed travel distance and the starting city index
    int maxDistance = 250;
    int startingCity = 5;

    // File paths
    std::string distance_data = "distance_data.csv"; // Path to the distance data file
    std::string priority_data = "priority_provinces.txt"; // Path to the txt file involving priority provinces
    std::string restricted_data = "weather_restricted_provinces.txt"; // Path to the txt file involving weather restricted provinces

    // Initialize the RoutePlanner with the file and max distance constraint
    RoutePlanner planner(distance_data, priority_data, restricted_data, maxDistance);

    // Start exploring the route from the specified starting city
    planner.exploreRoute(startingCity);

    return 0;
}

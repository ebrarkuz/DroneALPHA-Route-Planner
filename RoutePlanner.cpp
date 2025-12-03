#include "RoutePlanner.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Array to help you out with name of the cities in order
const std::string cities[81] = { 
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik", 
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne", 
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta", 
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya", 
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya", 
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat", 
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir", 
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce" 
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0) {
    map.loadDistanceData(distance_data);
    map.resetVisited();
    loadPriorityProvinces(priority_data);
    loadWeatherRestrictedProvinces(restricted_data);
    // TO DO:
    // Load map data from file
    // Mark all provinces as unvisited initially

    // Load priority provinces
    // Load restricted provinces
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << " file cannot be open kardes: " << filename << std::endl;
        return;
    }

    numPriorityProvinces = 0;

    std::string line;
    while (std::getline(infile, line)) {
        if (numPriorityProvinces >= MAX_PRIORITY_PROVINCES) {
            std::cerr << "index out of bounds " << std::endl;
            break;
        }
        std::istringstream iss(line);
        std::string cityName;
        int index;

        std::getline(iss, cityName, '(');
        cityName.erase(cityName.find_last_not_of(" ") + 1); // Sondaki boşlukları temizle


        if (!(iss >> index)) {
            std::cerr << "wrong line format: " << line << std::endl;
            continue;
        }


        if (index < 0 || index >= MAX_SIZE) {
            std::cerr << "index out of range in file: " << line << std::endl;
            continue;
        }


        priorityProvinces[numPriorityProvinces] = index;
        numPriorityProvinces++;
    }

    infile.close();
}


// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    numWeatherRestrictedProvinces = 0; // Sayacı sıfırlıyoruz

    std::string line;
    while (std::getline(infile, line)) {
        if (numWeatherRestrictedProvinces >= MAX_WEATHER_RESTRICTED_PROVINCES) {
            std::cerr << "array is full " << std::endl;
            break;
        }

        std::istringstream iss(line);
        std::string city;
        int index;


        std::getline(iss, city, '(');
        city.erase(city.find_last_not_of(" ") + 1); // Sondaki boşlukları temizle

        // Parantez içinde kalan indeksi oku
        if (!(iss >> index)) {
            std::cerr << "line format is wrong: " << line << std::endl;
            continue;
        }


        char paranthesis;
        if (!(iss >> paranthesis) || paranthesis != ')') {
            std::cerr << "line format is wrong (missing closing paranthesis): " << line << std::endl;
            continue;
        }


        if (index < 0 || index >= MAX_SIZE) {
            std::cerr << "index out of bounds: " << index << std::endl;
            continue;
        }


        weatherRestrictedProvinces[numWeatherRestrictedProvinces] = index;
        numWeatherRestrictedProvinces++;
    }

    infile.close();
}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    for(int i = 0; i < numPriorityProvinces; i++) {
        if(priorityProvinces[i] == province) {
            return true;
        }
    }
    // TODO: Your code here
    return false;
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    for (int i = 0; i < numWeatherRestrictedProvinces; i++) {
        if(weatherRestrictedProvinces[i] == province) {
            return true;
        }
    }
    // TODO: Your code here
    return false;
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {
    map.markAsVisited(startingCity);
    stack.push(startingCity);
    route.push_back(startingCity);
    exploreFromProvince(startingCity);
    displayResults();
    // TODO: Your code here
}

// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    enqueueNeighbors(province);
    while (!queue.isEmpty()) {
        int next=queue.dequeue();
        if(isWeatherRestricted(next)) {
            std::cout << "Province " << cities[next] << " is weather-restricted. Skipping." << std::endl;
            continue;
        }
        if(!map.isVisited(next)) {
            totalDistanceCovered += map.getDistance(province, next);

            map.markAsVisited(next);
            stack.push(next);
            route.push_back(next);
            exploreFromProvince(next);
        }
        // TODO: Your code here
    }
    if (queue.isEmpty() && !stack.isEmpty()) {
        backtrack();
    }
}

void RoutePlanner::enqueueNeighbors(int province) {
    bool allvisited=false;
    for(int i = 0; i < MAX_SIZE; i++) {
        if(!map.isVisited(i)&&map.getDistance(province,i)<=maxDistance) {
            if (isWeatherRestricted(i)) {
                std::cout << "Province " << cities[i] << " is weather-restricted. Skipping." << std::endl;
                continue;
            }
            if(isPriorityProvince(i)) {
                queue.enqueuePriority(i);
            }else {
                queue.enqueue(i);
            }
            allvisited=true;
        }

    }
    
    // TO DO: Enqueue priority & non-priority neighbors to the queue according to given constraints
}

void RoutePlanner::backtrack() {

    if(!stack.isEmpty()) {
        int current=stack.pop();
        enqueueNeighbors(current);
        route.push_back(current);
    }else {
        std::cerr << "Empty stack " << std::endl;
    }
    // TODO: Your code here
}

bool RoutePlanner::isExplorationComplete() const {
    // TODO: Your code here
    for(int i = 0; i < numPriorityProvinces; i++) {
        if(!map.isVisited(priorityProvinces[i])) {
            return false;
        }
    }
    return true;
}

void RoutePlanner::displayResults() const {
    std::cout << "----------------------------\n";
    std::cout << "Journey Completed!\n";
    std::cout << "----------------------------\n";


    std::cout << "Total Number of Provinces Visited: " << route.size() << "\n";


    std::cout << "Total Distance Covered: " << totalDistanceCovered << " km\n";


    std::cout << "Route Taken:\n";
    for (size_t i = 0; i < route.size(); ++i) {
        std::cout << cities[route[i]];
        if (i != route.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\nEnd\n";


    std::cout << "\nPriority Provinces Status:\n";
    for (int i = 0; i < numPriorityProvinces; i++) {
        std::cout << "- " << cities[priorityProvinces[i]] << " (";
        if (map.isVisited(priorityProvinces[i])) {
            std::cout << "Visited";
        } else {
            std::cout << "Not Visited";
        }
        std::cout << ")\n";
    }


    int visitedPriorityCount = 0;
    for (int i = 0; i < numPriorityProvinces; i++) {
        if (map.isVisited(priorityProvinces[i])) {
            visitedPriorityCount++;
        }
    }
    std::cout << "\nTotal Priority Provinces Visited: " << visitedPriorityCount << " out of " << numPriorityProvinces << "\n";
    if (visitedPriorityCount == numPriorityProvinces) {
        std::cout << "Success: All priority provinces were visited." << std::endl;
    } else {
        std::cout << "Warning: Not all priority provinces were visited." << std::endl;
    }

    // TODO: Your code here
    // Display "Journey Completed!" message
    // Display the total number of provinces visited
    // Display the total distance covered
    // Display the route in the order visited
    // Priority Province Summary
}



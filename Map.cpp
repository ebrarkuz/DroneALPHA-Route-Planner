#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>

Map::Map() {
    for(int i=0;i<MAX_SIZE;i++) {
        for(int j=0;j<MAX_SIZE;j++) {
            if(i==j) {
                distanceMatrix[i][j]=0;
            }else {
                distanceMatrix[i][j]= -1;
            }
        }
    }
    // TODO: Your code here
    // Initialize all distances to a value representing no direct connection
    // Initialize all provinces as unvisited
    for(int i=0;i<MAX_SIZE;i++) {
           visited[i]=false;
    }
}

// Loads distance data from a file and fills the distanceMatrix
void Map::loadDistanceData(const std::string& filename) {
    std::ifstream infile;
    infile.open(filename);
    if(!infile.is_open()) {
        std::cout<<"Failed to open file "<<filename<<std::endl;
        return;
    }
    std::string line;
    int x=0;
    while(std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string distance;
        int y=0;
        while(std::getline(iss, distance, ',')) {
            distanceMatrix[x][y] = std::stoi(distance);
            y++;
        }
        x++;
    }
    infile.close();
    // TODO: Your code here
    // Read each line in the CSV file
    // Read each cell separated by a comma
    // Convert cell to an integer and store in distanceMatrix
}

// Checks if the distance between two provinces is within the allowed maxDistance
bool Map::isWithinRange(int provinceA, int provinceB, int maxDistance) const {
    if(distanceMatrix[provinceA][provinceB] > maxDistance|| distanceMatrix[provinceB][provinceA] ==-1) {
        return false;
    }
    // TODO: Your code here
    return true;
}

// Marks a province as visited
void Map::markAsVisited(int province) {
   visited[province] = true;
    // TODO: Your code here
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const {
    return visited[province];
    // TODO: Your code here
    return false;
}

// Resets all provinces to unvisited
void Map::resetVisited() {
    for(int i=0;i<MAX_SIZE;i++) {
        visited[i]=false;
    }
    // TODO: Your code here
}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const {
    int count=0;
    for(int i=0;i<MAX_SIZE;i++) {
        if(visited[i]) {
        count++;
        }
    }
    // TODO: Your code here
    return count;
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const {
    return distanceMatrix[provinceA][provinceB];
    // TODO: Your code here
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>

void partOne()
{
    std::ifstream infile("input.txt");
    std::string line;
    int currentScore = 0, highScore = 0;
    
    while (std::getline(infile, line)) {
        if (not line.empty()) {
            currentScore += std::stoi(line);
        } else {
            if (currentScore > highScore) { highScore = currentScore; }
            currentScore = 0;
        }
    }
    std::cout << highScore << std::endl;
}

void partTwo()
{
    std::ifstream infile("input.txt");
    std::string line;
    int highScores[3] = {};
    int currentScore = 0;
    
    while(std::getline(infile, line)) {
        if (not line.empty()) {
            currentScore += std::stoi(line);
        } else {
            if (currentScore > highScores[0]) {
                highScores[2] = highScores[1];
                highScores[1] = highScores[0];
                highScores[0] = currentScore;
            } else if (currentScore > highScores[1]) {
                highScores[2] = highScores[1];
                highScores[1] = currentScore;
            } else if (currentScore > highScores[2]) {
                highScores[2] = currentScore;
            }
            currentScore = 0;
        }
    }
    int sum = 0;
    std::cout << std::accumulate(highScores, highScores + 3, sum) << std::endl;
}

int main()
{
    partOne();
    partTwo();
}

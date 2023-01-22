#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>
#include <sstream>

std::vector<std::vector<char>> getStacks(std::ifstream &infile)
{
    std::string line;
    std::vector<std::string> vec;

    // Strip lines and save them in a vector
    while (std::getline(infile, line)) {
        if (not std::isdigit(line[1])) {
            line = std::regex_replace(line, std::regex("    "), " [-] ");
            line.erase(std::remove(line.begin(), line.end(), '['), line.end());
            line.erase(std::remove(line.begin(), line.end(), ']'), line.end());
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

            vec.push_back(line);
        } else
            break;
    }

    // Get the number of stacks and their size
    int vecElements = (int)vec.size();
    int rows = (int)vec[0].length();

    // Create a 2D vector
    std::vector<std::vector<char>> v(
            rows,
            std::vector<char>(vecElements, ' '));

    // Initialise the new vector with transposed original vector
    for (int i = 0; i < vecElements; ++i)
        for (int j = 0; j < rows; ++j)
            v[j][i] = vec[i][j];

    for (auto &row : v)
        std::erase(row, '-');

    return v;
}

std::vector<std::string> getInstructions(std::ifstream &infile)
{
    std::vector<std::string> vec;
    std::string line;

    while (std::getline(infile, line)) {
        if (line[0] == 'm') {
            vec.push_back(line);
        }
    }
    return vec;
}

void moveCrates(
        std::vector<std::vector<char>> &stacks1,
        std::vector<std::vector<char>> &stacks2,
        std::vector<std::string> &instructions)
{
    for (auto &line : instructions) {
        // Get integers from each line and save them in a vector
        std::stringstream ss(line);
        int found;
        std::string temp;
        std::vector<int> numbers;
        while (not ss.eof()) {
            ss >> temp;
            if (std::stringstream(temp) >> found)
                numbers.push_back(found);
            temp = "";
        }

        int howMany = numbers[0];
        int from = numbers[1] - 1;
        int to = numbers[2] - 1;

        // Move crates
        int counter = howMany - 1;
        for (int i = 0; i < howMany; ++i) {
            stacks1[to].insert(stacks1[to].begin(), stacks1[from][0]);
            stacks1[from].erase(stacks1[from].begin());
            stacks2[to].insert(stacks2[to].begin(), stacks2[from][counter]);
            counter--;
        }
        for (int i = 0; i < howMany; ++i) {
            stacks2[from].erase(stacks2[from].begin());
        }
    }
}

int main()
{
    std::ifstream infile;
    infile.open("input.txt");

    std::vector<std::vector<char>> stacks1 = getStacks(infile);
    std::vector<std::vector<char>> stacks2 = stacks1;
    std::vector<std::string> instructions = getInstructions(infile);

    infile.close();

    moveCrates(stacks1, stacks2, instructions);

    // Print the results
    std::cout << "Part one: ";
    for (auto &row : stacks1) {
        std::cout << row[0];
    }
    std::cout << std::endl;
    std::cout << "Part two: ";
    for (auto &row : stacks2) {
        std::cout << row[0];
    }
    std::cout << std::endl;
}

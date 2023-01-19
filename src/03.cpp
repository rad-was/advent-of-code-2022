#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

void partOne()
{
    std::ifstream infile("/Users/rad/Developer/advent-of-code-2022/src/input.txt");
    std::string line;
    std::string compartment1, compartment2;
    int sum = 0;

    while (std::getline(infile, line)) {
        compartment1 = line.substr(0, line.length()/2);
        compartment2 = line.substr(line.length()/2);

        for (int i = 0; i < compartment1.length(); ++i) {
            if (compartment2.find(compartment1[i]) != std::string::npos) {
                if (std::islower(compartment1[i]))
                    sum += compartment1[i] - 'a' + 1;
                else
                    sum += compartment1[i] - 'A' + 27;
                break;
            }
        }
    }
    std::cout << sum << std::endl;
}

void partTwo()
{
    std::ifstream infile("/Users/rad/Developer/advent-of-code-2022/src/input.txt");
    std::string line;
    std::string group[3] = {};
    bool groupFull = false;
    int counter = 0;
    int sum = 0;

    while (std::getline(infile, line)) {
        if (counter == 0) {
            group[0] = line;
            counter++;
        } else if (counter == 1) {
            group[1] = line;
            counter++;
        } else {
            group[2] = line;
            counter = 0;
            groupFull = true;
        }

        if (groupFull) {
            for (int i = 0; i < group[0].length(); ++i) {
                if (group[1].find(group[0][i]) != std::string::npos and group[2].find(group[0][i]) != std::string::npos) {
                    char badge = group[0][i];
                    if (std::islower(badge))
                        sum += badge - 'a' + 1;
                    else
                        sum += badge - 'A' + 27;
                    break;
                }
            }
            groupFull = false;
        }
    }
    std::cout << sum << std::endl;
}

int main()
{
    partOne();
    partTwo();
}

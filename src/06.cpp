#include <iostream>
#include <fstream>
#include <string>

int findStartMarker(std::ifstream &infile)
{
    std::string line;
    std::getline(infile, line);
    std::string sequence;
    int counter = 0;

    for (int i = 0; i < line.length(); ++i) {
        if (counter == 0) {
            sequence = line[i];
            counter++;
            continue;
        }
        if (sequence.find(line[i]) != std::string::npos) {
            counter = 0;
            continue;
        }

        sequence += line[i];
        counter++;

        if (counter == 4) {
            return i;
        }
    }
    return -1;
}

int main()
{
    std::ifstream infile;
    infile.open("input.txt");

    std::cout << findStartMarker(infile) << std::endl;

    infile.close();
}

#include <iostream>
#include <fstream>
#include <string>

int findPacketMarker(std::string &line)
{
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

int findMessageMarker(std::string &line)
{
    std::string sequence;
    int counter = 0;

    for (int i = 0; i < line.length(); ++i) {
        if (counter == 0) {
            sequence = line[i];
            counter++;
            continue;
        }
        if (sequence.find(line[i]) != std::string::npos) {
            std::string sequenceCopy = sequence;
            for (int j = 0; j < sequence.length(); ++j) {
                sequenceCopy.erase(0, 1);
                if (sequenceCopy.find(line[i]) != std::string::npos) {
                    continue;
                }
                sequence.erase(0, j + 1);
                counter = (int)sequence.length();
                break;
            }
        }
        sequence += line[i];
        counter++;

        if (counter == 15) {
            return i;
        }
    }
    return -1;
}

int main()
{
    std::ifstream infile;
    infile.open("input.txt");
    std::string line;
    std::getline(infile, line);
    infile.close();

    std::cout << "Part one: " << findPacketMarker(line) << std::endl;
    std::cout << "Part two: " << findMessageMarker(line) << std::endl;
}

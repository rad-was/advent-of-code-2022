#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

int main()
{
    std::ifstream infile("input.txt");
    std::string line;
    int counter1 = 0, counter2 = 0;

    while (std::getline(infile, line)) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::replace(line.begin(), line.end(), '-', ' ');

        std::istringstream strm(line);
        std::vector<std::string> vec;
        std::string s;

        while (strm >> s)
            vec.push_back(s);

        int elf1Begin = std::stoi(vec[0]);
        int elf1End = std::stoi(vec[1]);
        int elf2Begin = std::stoi(vec[2]);
        int elf2End = std::stoi(vec[3]);

        if ((elf1Begin >= elf2Begin and elf1End <= elf2End) or (elf2Begin >= elf1Begin and elf2End <= elf1End)) {
            counter1++;
            counter2++;
            continue;
        }
        if ((elf1End >= elf2Begin and elf1End <= elf2End) or (elf1Begin <= elf2End and elf1End >= elf2End))
            counter2++;
    }
    std::cout << "Part one: " << counter1 << std::endl;
    std::cout << "Part two: " << counter2 << std::endl;
}

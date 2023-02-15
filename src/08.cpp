#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

void getSize(std::ifstream &file, int &rows, int &columns)
{
    int n = 0;
    std::string line;

    std::getline(file, line);
    int m = line.length();
    n++;
    while (std::getline(file, line)) { n++; }

    rows = n;
    columns = m;

    file.clear();
    file.seekg(0);
}

void fileToMatrix(std::ifstream &file, std::vector<std::vector<int>> &v)
{
    std::string line;
    int lineCounter = 0;

    while (std::getline(file, line)) {
        for (int i = 0; i < v[lineCounter].size(); ++i) {
            v[lineCounter][i] = line[i] - '0';
        }
        lineCounter++;
    }
    file.clear();
    file.seekg(0);
}

int findVisible(std::vector<std::vector<int>> &v) {
    int visibleTrees = v.size() * 2 + v[0].size() * 2 - 4;

    bool isVisible = false;
    int counter;
    // For every element in matrix
    for (int i = 1; i < v.size() - 1; ++i) {
        for (int j = 1; j < v[i].size() - 1; ++j) {
            // Check if all values between it and the edge of matrix are less than it

            // From the top
            counter = 0;
            for (int k = i - 1; k >= 0; --k) {
                if (v[k][j] >= v[i][j])
                    break;
                else
                    counter++;
                if (counter == i) {
                    //std::cout << i << ' ' << j << "    " << v[i][j] << std::endl;
                    visibleTrees++;
                    isVisible = true;
                }
            }
            if (isVisible) {
                isVisible = false;
                continue;
            }

            // From the bottom
            counter = 0;
            for (int k = i + 1; k < v.size(); ++k) {
                if (v[k][j] >= v[i][j])
                    break;
                else
                    counter++;
                if (counter + i == v.size() - 1) {
                    //std::cout << i << ' ' << j << "    " << v[i][j] << std::endl;
                    visibleTrees++;
                    isVisible = true;
                }
            }
            if (isVisible) {
                isVisible = false;
                continue;
            }

            // From the right
            counter = 0;
            for (int k = j + 1; k < v[i].size(); ++k) {
                if (v[i][k] >= v[i][j])
                    break;
                else
                    counter++;
                if (counter + j == v[i].size() - 1) {
                    //std::cout << i << ' ' << j << "    " << v[i][j] << std::endl;
                    visibleTrees++;
                    isVisible = true;
                }
            }
            if (isVisible) {
                isVisible = false;
                continue;
            }

            // From the left
            counter = 0;
            for (int k = j - 1; k >= 0; --k) {
                if (v[i][k] >= v[i][j])
                    break;
                else
                    counter++;
                if (counter == j) {
                    //std::cout << i << ' ' << j << "    " << v[i][j] << std::endl;
                    visibleTrees++;
                    isVisible = true;
                }
            }
            if (isVisible) {
                isVisible = false;
                continue;
            }
        }
    }

    return visibleTrees;
}

int main()
{
    std::ifstream infile("/Users/rad/Developer/advent-of-code-2022/src/input.txt");

    int rows;
    int cols;
    getSize(infile, rows, cols);

    std::vector<std::vector<int>> vec(rows, std::vector<int> (cols, 0));

    fileToMatrix(infile, vec);
    std::cout << findVisible(vec) << std::endl;

    infile.close();
}

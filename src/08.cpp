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

int findBestSpot(std::vector<std::vector<int>> &v) {
    int topScore = 0;
    // For every element in matrix
    for (int i = 1; i < v.size() - 1; ++i) {
        for (int j = 1; j < v[i].size() - 1; ++j) {
            int scenicScore = 1;
            int viewingDistance = 0;

            // From the top
            for (int k = i - 1; k >= 0; --k) {
                if (v[k][j] >= v[i][j]) {
                    viewingDistance++;
                    break;
                } else {
                    viewingDistance++;
                }
            }
            scenicScore *= viewingDistance;
            viewingDistance = 0;

            // From the bottom
            for (int k = i + 1; k < v.size(); ++k) {
                if (v[k][j] >= v[i][j]) {
                    viewingDistance++;
                    break;
                } else {
                    viewingDistance++;
                }
            }
            scenicScore *= viewingDistance;
            viewingDistance = 0;

            // From the right
            for (int k = j + 1; k < v[i].size(); ++k) {
                if (v[i][k] >= v[i][j]) {
                    viewingDistance++;
                    break;
                } else {
                    viewingDistance++;
                }
            }
            scenicScore *= viewingDistance;
            viewingDistance = 0;

            // From the left
            for (int k = j - 1; k >= 0; --k) {
                if (v[i][k] >= v[i][j]) {
                    viewingDistance++;
                    break;
                } else {
                    viewingDistance++;
                }
            }
            scenicScore *= viewingDistance;

            if (scenicScore > topScore)
                topScore = scenicScore;
        }
    }
    return topScore;
}

int main()
{
    std::ifstream infile("input.txt");

    int rows;
    int cols;
    getSize(infile, rows, cols);

    std::vector<std::vector<int>> vec(rows, std::vector<int> (cols, 0));

    fileToMatrix(infile, vec);
    std::cout << "Part one: " << findVisible(vec) << std::endl;
    std::cout << "Part two: " << findBestSpot(vec) << std::endl;

    infile.close();
}

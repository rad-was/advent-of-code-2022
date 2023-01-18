#include <iostream>
#include <fstream>
#include <string>

void partOne()
{
    std::ifstream infile("input.txt");
    char opponent, me;
    int opponentScore = 0, myScore = 0;
    
    while (infile >> opponent >> me) {
        // 1 for rock, 2 for paper, 3 for scissors
        int myMove = me - 'X' + 1;
        int opponentsMove = opponent - 'A' + 1;
        
        // I win
        if ((myMove == 1 and opponentsMove == 3) or (myMove == 2 and opponentsMove == 1) or (myMove == 3 and opponentsMove == 2)) {
            myScore += 6;
        }
        // draw
        else if (myMove == opponentsMove) {
            myScore += 3;
            opponentScore += 3;
        }
        // opponent wins
        else {
            opponentScore += 6;
        }
        myScore += myMove;
        opponentScore += opponentsMove;
    }
    std::cout << myScore << std::endl;
}

void partTwo()
{
    std::ifstream infile("input.txt");
    char me, opponent;
    int myScore = 0, opponentScore = 0;
    int rock = 1, paper = 2, scissors = 3;
    int win = 6, draw = 3;
    
    while (infile >> opponent >> me) {
        int myMove = me - 'X' + 1; // 1: I need to loose, 2: must be a draw, 3: I need to win
        int opponentsMove = opponent - 'A' + 1;
        
        switch (myMove) {
            case 1: // I need to lose
                switch (opponentsMove) {
                    case 1:
                        myScore += scissors;
                        break;
                    case 2:
                        myScore += rock;
                        break;
                    case 3:
                        myScore += paper;
                        break;
                }
                opponentScore += opponentsMove + win;
                break;
                
            case 2: // must be a draw
                myScore += opponentsMove + draw;
                opponentScore += opponentsMove + draw;
                break;
                
            case 3: // I need to win
                switch (opponentsMove) {
                    case 1:
                        myScore += paper;
                        break;
                    case 2:
                        myScore += scissors;
                        break;
                    case 3:
                        myScore += rock;
                        break;
                }
                myScore += win;
                opponentScore += opponentsMove;
                break;
        }
    }
    std::cout << myScore << std::endl;
}

int main()
{
    partOne();
    partTwo();
}

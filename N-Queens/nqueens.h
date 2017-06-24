#ifndef NQUEENS_H_INCLUDED
#define NQUEENS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <string>

class NQueens
{
public:
    NQueens(unsigned);
    void solve();
    void printBoard() const;
    bool isEmpty() const;
private:
    unsigned boardSize;
    std::vector<unsigned> rows;
    std::vector<unsigned> queensInRow;
    std::vector<unsigned> diagonalsPrimary;
    std::vector<unsigned> diagonalsSecondary;

    std::default_random_engine generator {static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<unsigned> distribution;

    void initialize();
    void clear();
};

#endif // NQUEENS_H_INCLUDED

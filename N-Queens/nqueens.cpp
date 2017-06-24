#include "nqueens.h"

NQueens::NQueens(unsigned size)
    : boardSize(size)
{
    if (boardSize > 0)
    {
        distribution.param(std::uniform_int_distribution<unsigned>::param_type(0, boardSize - 1));
        initialize();
    }
}

void NQueens::initialize()
{
    rows.resize(boardSize);
    diagonalsPrimary.resize(2*boardSize - 1);
    diagonalsSecondary.resize(2*boardSize - 1);
    queensInRow.resize(boardSize);

    unsigned row = 0;
    for (unsigned col = 0; col < boardSize; ++col)
    {
        row = distribution(generator);
        rows[col] = row;
        ++queensInRow[row];
        ++diagonalsPrimary[boardSize - 1 + col - row];
        ++diagonalsSecondary[row + col];
    }
}

void NQueens::clear()
{
    rows.clear();
    queensInRow.clear();
    diagonalsPrimary.clear();
    diagonalsSecondary.clear();
}

void NQueens::solve()
{
    if (isEmpty())
    {
        std::cout << "Empty board.\n";
        return;
    }

    if (boardSize == 2 || boardSize == 3)
    {
        std::cout << "No solution!\n";
        return;
    }

    unsigned moves = 0;
    std::vector<unsigned> candidates;
    unsigned minConflicts, maxConflicts, conflicts;
    while (true)
    {
        maxConflicts = 0;
        for (unsigned col = 0; col < boardSize; ++col)
        {
            conflicts = queensInRow[rows[col]] + diagonalsPrimary[boardSize - 1 + col - rows[col]]
                        + diagonalsSecondary[rows[col] + col] - 3;
            if (maxConflicts == conflicts)
            {
                candidates.push_back(col);
            }
            else if (maxConflicts < conflicts)
            {
                maxConflicts = conflicts;
                candidates.clear();
                candidates.push_back(col);
            }
        }

        if (maxConflicts == 0)
        {
            return;
        }

        unsigned worstQueenColumn = candidates.at(distribution(generator) % candidates.size());
        candidates.clear();
        minConflicts = boardSize;
        for (unsigned row = 0; row < boardSize; ++row)
        {
            conflicts = queensInRow[row] + diagonalsPrimary[boardSize - 1 + worstQueenColumn - row]
                        + diagonalsSecondary[row + worstQueenColumn];

            if (row == rows[worstQueenColumn])
            {
                conflicts -= 3;
            }

            if (conflicts == minConflicts)
            {
                candidates.push_back(row);
            }
            else if (minConflicts > conflicts)
            {
                minConflicts = conflicts;
                candidates.clear();
                candidates.push_back(row);
            }
        }

        unsigned oldRow = rows[worstQueenColumn];
        unsigned newRow = candidates.at(distribution(generator) % candidates.size());
        rows[worstQueenColumn] = newRow;
        --queensInRow[oldRow];
        ++queensInRow[newRow];
        --diagonalsPrimary[boardSize - 1 + worstQueenColumn - oldRow];
        ++diagonalsPrimary[boardSize - 1 + worstQueenColumn - newRow];
        --diagonalsSecondary[oldRow + worstQueenColumn];
        ++diagonalsSecondary[newRow + worstQueenColumn];
        candidates.clear();
        ++moves;

        if (moves > 5 * boardSize)
        {
            clear();
            initialize();
            moves = 0;
        }
    }
}

void NQueens::printBoard() const
{
    for (unsigned i = 0; i < boardSize; ++i)
    {
        for (unsigned j = 0; j < boardSize; ++j)
        {
            if (rows[j] == i)
            {
                std::cout << '*';
            }
            else
            {
                std::cout << '_';
            }
        }
        std::cout << '\n';
    }
}

bool NQueens::isEmpty() const
{
    return boardSize == 0;
}

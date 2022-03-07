#include <iostream>
#include <vector>

class Board
{
    int size;   //Size of board, it has to be greater than 3 and positive. Assumption: always a square board
    public:

    bool getSize()
    {
        std::cout << "Enter the size of Board: ";
        std::cin >> size;
        if(size < 3)
        {
            std::cout << "Invalid Size" << std::endl;
            return false;
        }
        return true;
    }

    std::vector<std::vector<char>> createBoard()
    {
        //Create a 2D vector board based on the input size
        std::vector<std::vector<char>> board(size, std::vector<char> (size, 'E'));   //E is empty cell
        return board;
        //Create board outside to save time and space and not have copies
    }

    void updateBoard(std::vector<std::vector<char>> &board, int row, int col, char alphabet)
    {
        board[row][col] = alphabet;
    }

    void drawBoard(std::vector<std::vector<char>> &board)
    {
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(j == 0)
                {
                    std::cout << board[i][j];
                }
                else
                {
                    std::cout << "|" << board[i][j];
                }  
            }
            std::cout << std::endl;
        }   
    }  
};

//Can check the board directly as well

class Player
{   
    public:
    char alphabet;
    std::vector<std::vector<bool>> entriesPlayer, entriesPlayer1, entriesPlayer2;
    //Initialiser list
    Player(): entriesPlayer (3, std::vector<bool> (3)), entriesPlayer1 (3, std::vector<bool> (3)), 
              entriesPlayer2 (3, std::vector<bool> (3))
    {

    }

    void newEntry(int row, int col, bool turn)
    {
        if(turn)
        {
            entriesPlayer1[row][col] = true;    
        }

        else
        {
            entriesPlayer2[row][col] = true;
        }  
    }

    bool checkBoundary(int row, int col, std::vector<std::vector<char>> &board)
    {
        bool isValid{true};
        if(row >= 3 || col >= 3)
        {
            isValid = false;
            std::cout << "Out of bounds" << std::endl;
        }
        
        if(board[row][col] == 'X' || board[row][col] == 'O')
        {
            isValid = false;
            std::cout << "Already exists" << std::endl;
        }
        return isValid;
    }

    int checkRow(std::vector<std::vector<bool>> entriesPlayer, int &rowCounter, int i, int j)
    {
        if(entriesPlayer[i][j] == true)
        {
            rowCounter++;
        }
        return rowCounter;
    }

    int checkCol(std::vector<std::vector<bool>> entriesPlayer, int &colCounter, int i, int j)
    {
        if(entriesPlayer[j][i] == true)
        {
            colCounter++;
        }
        return colCounter;
    }

    int checkDiag1(std::vector<std::vector<bool>> entriesPlayer, int &diagCounter1, int i, int j)
    {
        if(i == j && entriesPlayer[i][j] == true)
        {
            diagCounter1++;
        }
        return diagCounter1;
    }

    int checkDiag2(std::vector<std::vector<bool>> entriesPlayer, int &diagCounter2, int i, int j)
    {
        if(((i == 1 && j == 1) || (i == 2 && j == 0) || (i == 0 && j == 2)) && entriesPlayer[i][j] == true)
        {
            diagCounter2++;
        }
        return diagCounter2;
    }

    bool checkWin(bool turn)
    {
        if(turn)
        {
            entriesPlayer = entriesPlayer1;
        }     
        else
        {
            entriesPlayer = entriesPlayer2;
        }
        int diagCounter1{0}, diagCounter2{0};
        for(int i = 0; i < 3; i++)
        {
            int rowCounter{0}, colCounter{0};
            for(int j = 0; j < 3; j++)
            {
                rowCounter = checkRow(entriesPlayer, rowCounter, i, j);
                colCounter = checkCol(entriesPlayer, colCounter, i, j);
                diagCounter1 = checkDiag1(entriesPlayer, diagCounter1, i, j);
                diagCounter2 = checkDiag2(entriesPlayer, diagCounter2, i, j);
                if(rowCounter == 3 || colCounter == 3 || diagCounter1 == 3 || diagCounter2 == 3)
                {
                    return true;
                }
            }   
        }  
        return false;                
    }

    bool playTurn(std::vector<std::vector<char>> &board, bool turn, Player &P, Board &classBoard)
    {
        //classBoard.drawBoard(board);
        bool isValid{false};
        int row{0}, col{0};
        bool win{false};
        while(!isValid)
        {
            std::cout << "Enter position: ";  //enter the row and col with space in between
            std::cin >> row >> col;
            isValid = P.checkBoundary(row, col, board);
        }
        newEntry(row, col, turn);
        classBoard.updateBoard(board, row, col, P.alphabet);
        win = P.checkWin(turn);
        classBoard.drawBoard(board);
        return win;
    }
};

int main()
{
    Board classBoard;
    bool validSize{false};
    while(!validSize)
    {
        validSize = classBoard.getSize();
    }
    Player P1, P2;
    P1.alphabet = 'X';
    P2.alphabet = 'O';
    bool win{false};
    std::vector<std::vector<char>> board = classBoard.createBoard();
    bool turn{true};   //turn = true is Player 1 to play, turn = false is Player 2 to play
    int row{0}, col{0};
    int totalTurns{0};
  
    classBoard.drawBoard(board);
    while(!win)
    {
        std::cout << "Player 1 to play" << std::endl;
        win = P1.playTurn(board, turn, P1, classBoard);
        if(win == true)
            {
                std::cout << "Player 1 Wins" << std::endl;
                break;
            }
        turn = false;  //Pass the turn

        std::cout << "Player 2 to play" << std::endl;
        win = P2.playTurn(board, turn, P2, classBoard);
        if(win == true)
            {
                std::cout << "Player 2 Wins" << std::endl;
                break;
            }
        turn = true;  //Pass the turn

        totalTurns++;
        if(totalTurns == 9)
        {
            std::cout << "It is a Tie";
            break;
        }
    }
}
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>


std::vector<char> board = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void insertLetter(char letter, int pos){
    board[pos] = letter;
}

bool spaceIsFree(int pos){
    char position = board[pos];
    char empty_pos = ' ';
    bool is_free = false;
    if (position == empty_pos){
        is_free = true;
    }
    return is_free;
}

void printBoard(std::vector<char> board){
    std::cout << "   |   |" << std::endl;
    std::cout << " " << board[1] <<  " | " << board[2] << " | " << board[3] << std::endl;
    std::cout << "   |   |" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "   |   |" << std::endl;
    std::cout << " " << board[4] <<  " | " << board[5] << " | " << board[6] << std::endl;
    std::cout << "   |   |" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "   |   |" << std::endl;
    std::cout << " " << board[7] <<  " | " << board[8] << " | " << board[9] << std::endl;
    std::cout << "   |   |" << std::endl;
}

bool isWinner(std::vector<char> board, char letter){
    bool is_winner = false;
    if ((board[7] == letter && board[8] == letter && board[9] == letter) ||
        (board[4] == letter && board[5] == letter && board[6] == letter) ||
        (board[1] == letter && board[2] == letter && board[3] == letter) ||
        (board[1] == letter && board[5] == letter && board[9] == letter) ||
        (board[7] == letter && board[5] == letter && board[3] == letter) ||
        (board[2] == letter && board[5] == letter && board[8] == letter) ||
        (board[1] == letter && board[4] == letter && board[7] == letter) ||
        (board[3] == letter && board[6] == letter && board[9] == letter)
    ){
        is_winner = true;
    }
    return is_winner;
}

void playerMove(){
    bool run = true;
    int move;

    while (run == true){
        while((std::cout << "Please, select a position to place an X (1-9): ") && (!(std::cin >> move) || move < 1 || move > 9)) {
            std::cout << "Please, type a number within the range" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (spaceIsFree(move) == true){
            run = false;
            insertLetter('X', move);
        }else{
            std::cout << "Sorry, this space is occupied!" << std::endl;
        }
    }
}

int selectRandom(std::vector<char> numbers){
    int length = numbers.size();
    int r = rand() % length - 1;
    return numbers[r];
} 

int compMove(){
    std::vector<char> possibleMoves;
    int move = 0;

    for (int i = 0; i < 10; i++){
        if ((board[i] == ' ') && (i != 0)) {
            possibleMoves.push_back(i);
        }
    }

    char letters[] = {'O', 'X'};
    for (int l = 0; l < 2; l++){
        char letter = letters[l];
        for (int i = 0; i < possibleMoves.size(); i++){
            int possibleMove = possibleMoves[i];
            std::vector<char> boardCopy;
            for (int k = 0; k < board.size(); k++){
                boardCopy.push_back(board[k]);
            }
            boardCopy[possibleMove] = letter;
            if (isWinner(boardCopy, letter) == true){
                move = possibleMove;
                return move;
            }
        }
    }

    for (int i = 0; i < possibleMoves.size(); i++){
        if (possibleMoves[i] == 5){
            move = 5;
            return move;
        }
    }

    std::vector<char> cornersOpen;
    for (int i = 0; i < possibleMoves.size(); i++){
        int possibleMove = possibleMoves[i];
        int corners[] = {1, 3, 7, 9};
        for(int k = 0; k < 4; k++){
            if (possibleMove == corners[k]){
                cornersOpen.push_back(possibleMove);
            }
        }          
    }
    if (cornersOpen.size() > 0 ){
        move = selectRandom(cornersOpen);
        return move;
    }

    
    std::vector<char> edgesOpen;
    for (int i = 0; i < possibleMoves.size(); i++){
        int possibleMove = possibleMoves[i];
        int corners[] = {2, 4, 6, 8};
            for(int k = 0; k < 4; k++){
                if (possibleMove == corners[k]){
                    edgesOpen.push_back(possibleMove);
                }
            }          
    }
    if (edgesOpen.size() > 0 ){
        move = selectRandom(edgesOpen);
        return move;
    }

    return move;
}

bool isBoardFull(){
    bool is_full = false;
    int count = 0;
    for (int i=0; i < 10; i++ ){
        if (board[i] == ' '){
            count++;
        }
    }

    if (count < 2) {
        is_full = true;
    }

    return is_full;
}

int main(){
    std::cout << "Welcome to Tic Tac Toe!" << std::endl;
    printBoard(board);

    while (isBoardFull() == false){
        if (!(isWinner(board, 'O'))){
            playerMove();
            printBoard(board);
        }else{
            std::cout << "Sorry, O won this time!" << std::endl;
            break;
        }

        if (!(isWinner(board, 'X'))){
            int move = compMove();
            if (move == 0) {
                std::cout << "Tie game!" << std::endl;
            }else{
                insertLetter('O', move);
                std::cout << "Computer placed 0 in position: " << move << std::endl;
                printBoard(board);
            }
            
        }else{
            std::cout << "X won this time! Good job!" << std::endl;
            break;
        }
    }

    if (isBoardFull()){
        std::cout << "Tie Game!" << std::endl;
    }
}
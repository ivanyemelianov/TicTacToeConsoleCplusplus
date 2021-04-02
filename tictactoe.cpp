#include <iostream>
#include <string>
#include <vector>
#include <map>


std::vector<char> board = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
std::map< std::string, int> inputTranslator = {{"A1", 0}, {"A2", 1}, {"A3", 2}, {"B1", 3},
{"B2", 4}, {"B3", 5}, {"C1", 6}, {"C2", 7}, {"C3", 8}};

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
    std::cout << "   1   2   3" << std::endl;
    std::cout << "     |   |" << std::endl;
    std::cout << "A " << " " << board[0] <<  " | " << board[1] << " | " << board[2] << std::endl;
    std::cout << "     |   |" << std::endl;
    std::cout << "  -----------" << std::endl;
    std::cout << "     |   |" << std::endl;
    std::cout << "B " << " " << board[3] <<  " | " << board[4] << " | " << board[5] << std::endl;
    std::cout << "     |   |" << std::endl;
    std::cout << "  -----------" << std::endl;
    std::cout << "     |   |" << std::endl;
    std::cout << "C " << " " << board[6] <<  " | " << board[7] << " | " << board[8] << std::endl;
    std::cout << "     |   |" << std::endl;
}

bool isWinner(std::vector<char> board, char letter){
    bool is_winner = false;
    if ((board[6] == letter && board[7] == letter && board[8] == letter) ||
        (board[3] == letter && board[4] == letter && board[5] == letter) ||
        (board[0] == letter && board[1] == letter && board[2] == letter) ||
        (board[0] == letter && board[4] == letter && board[8] == letter) ||
        (board[6] == letter && board[4] == letter && board[2] == letter) ||
        (board[1] == letter && board[4] == letter && board[7] == letter) ||
        (board[0] == letter && board[3] == letter && board[6] == letter) ||
        (board[2] == letter && board[5] == letter && board[8] == letter)
    ){
        is_winner = true;
    }
    return is_winner;
}

bool isValidInput(std::string input){
    bool isValid;
    //std::vector<std::string> validInput {"A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3"};
    //for (int i = 0; i == validInput.size(); i++){
    if (inputTranslator.count(input)){
        return isValid = true;
    }else{
        return isValid = false;
    }
    //}
}

void playerMove(){
    bool run = true;
    int move;
    std::string input;

    while (run == true){
        /*while((std::cout << "Please, select a position to place an X: ") && (!(std::cin >> move) || move < 1 || move > 9)) {
            std::cout << "Please, type a number within the range" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }*/
        std::cout << "Please, select a position to place an X: ";
        std::cin >> input;

        

        if (isValidInput(input) == true){
            move = inputTranslator[input];
            if (spaceIsFree(move) == true){
                run = false;
                insertLetter('X', move);
            }else{
                std::cout << "Sorry, this space is occupied!" << std::endl;
            }
        }else{
            std::cout << "Input is not valid. Please enter an upprcase A, B or C followed by a gigit from 1 to 3" << std::endl;
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

    for (int i = 0; i < 9; i++){
        if (board[i] == ' ') {
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
        if (possibleMoves[i] == 4){
            move = 4;
            return move;
        }
    }

    std::vector<char> cornersOpen;
    for (int i = 0; i < possibleMoves.size(); i++){
        int possibleMove = possibleMoves[i];
        int corners[] = {0, 2, 6, 8};
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
        int corners[] = {1, 3, 5, 7};
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
    for (int i=0; i < 9; i++ ){
        if (board[i] == ' '){
            count++;
        }
    }

    if (count == 0) {
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
            if (isBoardFull()) {
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

    /*if (isBoardFull()){
        std::cout << "Tie Game!" << std::endl;
    }*/
}
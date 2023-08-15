#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;
void reveal(int, int, char [10][10], char [10][10]);  
void create_mine_positions(char [10][10]); 
void cell_number(int, int, char [10][10]);
void create_table(char [10][10]);
void open_cell(char [10][10], char [10][10], int&, bool&);
void game(); 
void print_table(char [10][10]); 
void cell_number(int i, int j, char table_mine_positions[10][10]) {
    if(i >= 0 && i < 10 && j >= 0 && j < 10 && table_mine_positions[i][j] != 'X')
        table_mine_positions[i][j]++;
}
enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};
Difficulty chooseDifficulty() {
    cout << "Choose difficulty level:" << endl;
    cout << "1. Easy (10 mines)" << endl;
    cout << "2. Medium (15 mines)" << endl;
    cout << "3. Hard (20 mines)" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1: return EASY;
        case 2: return MEDIUM;
        case 3: return HARD;
        default: return EASY; 
    }
}
void create_mine_positions(char table_mine_positions[10][10], Difficulty difficulty) {
    int counter = 0;
    srand(time(NULL));
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            table_mine_positions[i][j] = '0';
    int total_mines = 0;
    switch (difficulty) {
        case EASY:
            total_mines = 10;
            break;
        case MEDIUM:
            total_mines = 15;
            break;
        case HARD:
            total_mines = 20;
            break;
    }
    while(counter < total_mines) {
        int i = rand() % 10;
        int j = rand() % 10;
        if(table_mine_positions[i][j] == '0') {
            table_mine_positions[i][j] = 'X';
            cell_number(i-1, j, table_mine_positions);
            cell_number(i+1, j, table_mine_positions);
            cell_number(i, j-1, table_mine_positions);
            cell_number(i, j+1, table_mine_positions);
            cell_number(i-1, j-1, table_mine_positions);
            cell_number(i-1, j+1, table_mine_positions);
            cell_number(i+1, j-1, table_mine_positions);
            cell_number(i+1, j+1, table_mine_positions);
            counter++;
        }
    }
}
void create_table(char table[10][10]) {
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            table[i][j] = '*';
}
void print_table(char arr[10][10]) {
    cout << "    ";
    for(int i = 0; i < 10; i++){
        cout << setw(3) << i;
    }
    cout << endl << "  ";
    for(int i = 0; i < 32; i++){
        cout << "_";
    }
    cout << endl;
    for(int i = 0; i < 10; i++) {
        cout << setw(3) << i << "|";
        for(int j = 0; j < 10; j++){
            cout << setw(3) << arr[i][j];
        }
        cout << endl;
    }
}
void open_cell(char table[10][10], char table_mine_positions[10][10], int &flag_counter, bool &end_game_lose) {
    int i, j;
    do {
        cin >> i >> j;
    } while(i < 0 || i > 9 || j < 0 || j > 9);
    if(table_mine_positions[i][j] == 'X') {
        table[i][j] = 'X';
        end_game_lose = true;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(table_mine_positions[i][j] == 'X'){
                    table[i][j] = 'X';
                }
            }
        }
    } else {
        reveal(i, j, table, table_mine_positions);
    }
}
void place_or_remove_flag(char table[10][10], char table_mine_positions[10][10], int &flag_counter, int &mines_flagged_counter) {
    int i, j;
    do {
        cin >> i >> j;
    } while(i < 0 || i > 9 || j < 0 || j > 9);
    if (table[i][j] == '*') {
        table[i][j] = 'F';
        flag_counter++;
        if(table_mine_positions[i][j] == 'X'){
            mines_flagged_counter++;
        }
    } else if (table[i][j] == 'F') {
        table[i][j] = '*';
        flag_counter--;
        if(table_mine_positions[i][j] == 'X'){
            mines_flagged_counter--;
        }
    }
}
void input_symbol(char table[10][10], char table_mine_positions[10][10], int &flag_counter, bool &end_game_lose, int &mines_flagged_counter) {
    char symbol;
    cin >> symbol;
    switch (symbol) {
        case 'o': 
		    open_cell(table, table_mine_positions, flag_counter, end_game_lose); 
			break;
        case 'f': 
		    place_or_remove_flag(table, table_mine_positions, flag_counter, mines_flagged_counter); 
			break;
        default : 
		    cout << "Invalid input. Please try again." << endl; 
			input_symbol(table, table_mine_positions, flag_counter, end_game_lose, mines_flagged_counter);
    }
}
void reveal(int i, int j, char table[10][10], char table_mine_positions[10][10]) {
    if (table[i][j] == '*' && table_mine_positions[i][j] != 'X' && i >= 0 && i < 10 && j >= 0 && j < 10) {
        table[i][j] = table_mine_positions[i][j];
        if(table_mine_positions[i][j] == '0') {
            reveal(i, j-1, table, table_mine_positions);
            reveal(i, j+1, table, table_mine_positions);
            reveal(i-1, j-1, table, table_mine_positions);
            reveal(i+1, j-1, table, table_mine_positions);
            reveal(i+1, j+1, table, table_mine_positions);
            reveal(i-1, j+1, table, table_mine_positions);
            reveal(i-1, j, table, table_mine_positions);
            reveal(i+1, j, table, table_mine_positions);
        }
    }
}
bool end_game_win_check(int flag_counter, int mines_flagged_counter) {
    return (flag_counter == 10 && mines_flagged_counter == 10);
}
void game() {
    char table[10][10];
    char table_mine_positions[10][10];
    int flag_counter = 0, mines_flagged_counter = 0;
    bool end_game_lose = false;
    create_table(table);
    Difficulty difficulty = chooseDifficulty();
    create_mine_positions(table_mine_positions, difficulty);
    time_t time_since_epoch = time(0);
    time_t game_time;
    while(!end_game_lose && !end_game_win_check(flag_counter, mines_flagged_counter)) {
        game_time = time(0);
        print_table(table);
        cout << endl << "Flags: " << flag_counter << endl;
        cout << "Time: " << game_time - time_since_epoch << " seconds" << endl;
        cout << "Enter operation (o/f) followed by row and column: ";
        input_symbol(table, table_mine_positions, flag_counter, end_game_lose, mines_flagged_counter);
    }
    if(end_game_lose) {
        print_table(table);
        cout << endl << "GAME OVER" << endl;
    }
    if(end_game_win_check(flag_counter, mines_flagged_counter)) {
        cout << "Time to complete: " << game_time - time_since_epoch << " seconds" << endl;
        cout << "YOU WIN!" << endl;
    }
}
int main() {
    cout
    << "Rules:" << endl
    << "Enter 'o' , then enter value of row and column to open cell[row][col]." << endl
    << "Enter 'f' ,then enter value of row and column to place "
    << "or remove flag on cell[row][col]." << endl << endl;
    game();
    return 0;
}
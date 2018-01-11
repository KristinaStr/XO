#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <utility>
using namespace std;

void pole(char array[3][3]) {
  for (int i = 0; i < 3; i++) {
    cout << " +---+---+---+" << endl;
    for (int j = 0; j < 3; j++) {
      if (j == 2) {
        cout << " | " << array[i][j] << " | " << endl;
        break;
      }
      cout << " | " << array[i][j];
    }
  }
  cout << " +---+---+---+" << endl;
}

void show_move(char array[3][3], char op) {
  int k = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!(array[i][j] == 'X' || array[i][j] == 'O')) {
        if (i == 0) {
          cout << ++k << ".mark cell a" << j + 1 << " as " << op << endl;
        }
        if (i == 1) {
          cout << ++k << ".mark cell b" << j + 1 << " as " << op << endl;
        }
        if (i == 2) {
          cout << ++k << ".mark cell c" << j + 1 << " as " << op << endl;
        }
      }
    }
  }
  cout << ++k << ". quit" << endl;
}

bool proverka(char array[3][3]) {
  unsigned int l = 0;
  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      if (!(array[i][j] == 'X' || array[i][j] == 'O')) {
        l++;
      }
      if (l > 0) return true;
    }
  }
  cout << " No more motion" << endl;
  return false;
}

bool win(char array[3][3]) {
  for (unsigned int i = 0; i < 3; i++) {
    int j = 0;
    if (array[i][j] == 'X' || array[i][j] == 'O') {
      if (array[i][j] == array[i][j + 1] && array[i][j] == array[i][j + 1]) {
        return true;
        break;
      }
    }
  }
  for (unsigned int j = 0; j < 3; j++) {
    int i = 0;
    if (array[i][j] == 'X' || array[i][j] == 'O') {
      if (array[i][j] == array[i + 1][j] && array[i][j] == array[i + 2][j]) {
        return true;
        break;
      }
    }
  }

  if (array[0][0] == 'X' || array[0][0] == 'O') {
    if (array[0][0] == array[1][1] && array[0][0] == array[2][2]) {
      return true;
    }
  }
  if (array[0][2] == 'X' || array[0][2] == 'O') {
    if (array[0][2] == array[1][1] && array[0][2] == array[2][0]) {
      return true;
    }
  }
  return false;
}

void make_move(char array[3][3], unsigned int move, char op) {
  bool found = false;
  int k = 0, result_i = 0, result_j = 0;
  for (unsigned int i = 0; i < 3 && !found; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      if (array[i][j] == 0) {
        k++;
      }
      if (k == move) {
        found = true;
        result_i = i;
        result_j = j;
        break;
      }
    }
  }
  array[result_i][result_j] = op;
}
int main() {
  char op;
  char array[3][3] = {};
  int i = 0;
  int k = 0;
  int move;
  bool found = false, ok = true, choose = true;
  pole(array);
  while (proverka(array)) {
    if (choose == true)
      op = 'X';
    else
      op = 'O';
    show_move(array, op);
    string string;
    getline(cin, string);
    istringstream stream(string);
    stream >> move;
    if (move == 10 - i) {
      cout << "Game Over" << endl;
      return -1;
    }
    while (move < 1 || move > (10 - i)) {
      cout << endl << "You can`t use this number, please, try again: ";
      getline(cin, string);
      istringstream stream(string);
      stream >> move;
      if (move == 10 - i) {
        cout << "Game Over" << endl;
        return -1;
      }
    }
    make_move(array, move, op);
    if (ok == found) break;
    pole(array);
    if (win(array)) {
      cout << endl << "Player " << op << " is winner!";
      cin.get();
      return 0;
    }
    choose = !choose;
    i++;
  }
}

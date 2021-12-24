#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

vector<vector<int>> board;
vector<int> board_row;

int get_winner(vector<vector<int>> board, vector<vector<bool>> marked, vector<int> nums) {
  int winning_val = 0, unmarked_sum = 0;
  for(auto &num : nums) {
    for(size_t i = 0; i < board.size(); i++) {
      for(size_t j = 0; j < board[0].size(); j++) {
        if(board[i][j] == num) marked[i][j] = true;
      }
    }

    bool bingo = true;
    for(size_t i = 0; i < marked.size(); i++) {
      for(size_t j = 0; j < marked[0].size(); j++) {
        if(!marked[i][j]) bingo = false;
      }

      if(bingo) break;
      else bingo = true;
    }

    if(!bingo) {
      for(size_t i = 0; i < marked.size(); i++) {
        for(size_t j = 0; j < marked[0].size(); j++) {
          if(!marked[j][i]) bingo = false;
        }

        if(bingo) break;
        else bingo = true;
      }
    }

    if(bingo) {
      winning_val = num;
      for(size_t i = 0; i < board.size(); i++) {
        for(size_t j = 0; j < board[0].size(); j++) {
          if(!marked[i][j]) unmarked_sum += board[i][j];
        }
      }

      break;
    }
  }

  return unmarked_sum * winning_val;
}

void part_one(string filename) {
  ifstream file;
  file.open(filename);

  string numbers;
  file >> numbers;

  vector<int> nums;
  int temp;
  for(auto &i : numbers) {
    if(!isdigit(i)) {
      nums.push_back(temp);
      temp = 0;
    } else {
      temp = (temp * 10) + i - '0';
    }
  }

  vector<vector<int>> board;
  vector<int> ans;
  while(!file.eof()) {
    string line;
    getline(file, line);

    if(line.size() == 0) {
      vector<vector<bool>> marked(board.size(), vector<bool>(board[0].size()));
      ans.push_back(get_winner(board, marked, nums));

      board.clear();
    } else {
      istringstream iss(line);
      int n;
      while(iss >> n) {
        board_row.push_back(n);
      }

      board.push_back(board_row);
      board_row.clear();
    }
  }

}

int main() {
  part_one("example");
}

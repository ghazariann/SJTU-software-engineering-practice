#include "lexicon.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;
class Board {
public:
  Board(int N, const std::string &lexiconFile)
      : map(N, vector<char>(N)), score(0) {
    try {
      lex = Lexicon(lexiconFile);
    } catch (const std::exception &e) {
      std::cerr << "Failed to load lexicon file: " << e.what() << '\n';
      std::exit(EXIT_FAILURE); // Terminate the program
    }
  }

  bool findWordInMap(const string &word) const {
    vector<vector<bool>> visited(map.size(),
                                 vector<bool>(map[0].size(), false));
    for (int i = 0; i < map.size(); ++i) {
      for (int j = 0; j < map[0].size(); ++j) {
        if (dfs(i, j, word, 0, visited)) {
          return true;
        }
      }
    }
    return false;
  }

  void findAllWords() {
    vector<vector<bool>> visited(map.size(),
                                 vector<bool>(map[0].size(), false));
    string currentWord;
    for (int i = 0; i < map.size(); ++i) {
      for (int j = 0; j < map[0].size(); ++j) {
        dfsFindWords(i, j, currentWord, visited);
      }
    }
  }
  void printState() const {
    cout << "Map:" << endl;
    for (const auto &row : map) {
      for (const auto &elem : row) {
        cout << elem;
      }
      cout << endl;
    }

    cout << "Your Score: " << score << endl;

    cout << "Your Words: ";
    for (const auto &word : foundWords) {
      cout << word << ' ';
    }
    cout << endl;
  }
  Lexicon getLexicon() const { return lex; }
  int getComputerScore() const { return computerScore; }
  // void setComputerScore(int newScore) { computerScore = newScore; }
  unordered_set<string> getFoundWords() const { return foundWords; }
  set<string> getComputerFoundWords() const { return computerFoundWords; }
  void setElement(int row, int col, char letter) { map[row][col] = letter; }
  void addWord(const string &word) { foundWords.insert(word); }
  int getScore() const { return score; }
  void setScore(int newScore) { score = newScore; }
  bool hasWordBeenFound(const string &word) const {
    return foundWords.find(word) != foundWords.end();
  }

private:
  vector<vector<char>> map;
  int score = 0;
  int computerScore = 0;
  Lexicon lex;
  unordered_set<string> foundWords;
  set<string> computerFoundWords;
  bool dfs(int x, int y, const string &word, int index,
           vector<vector<bool>> &visited) const {
    if (index == word.size()) {
      return true;
    }
    if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size() ||
        visited[x][y] || map[x][y] != word[index]) {
      return false;
    }

    visited[x][y] = true;

    // Check all 8 directions
    static int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    static int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    for (int i = 0; i < 8; ++i) {
      if (dfs(x + dx[i], y + dy[i], word, index + 1, visited)) {
        return true;
      }
    }

    visited[x][y] = false;
    return false;
  }

  void dfsFindWords(int x, int y, string &currentWord,
                    vector<vector<bool>> &visited) {
    if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size() ||
        visited[x][y]) {
      return;
    }

    currentWord.push_back(map[x][y]);
    visited[x][y] = true;

    if (lex.containsPrefix(currentWord)) {
      if (lex.contains(currentWord)) {
        // found in lexicon
        string lowerWord = currentWord;
        transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(),
                  ::tolower);
        if (currentWord.length() >= 4 && !hasWordBeenFound(lowerWord) &&
            !computerFoundWords.count(currentWord)) {
          computerFoundWords.insert(currentWord);
          computerScore += currentWord.length() - 3;
        }
      }
      // Check all 8 directions
      static int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
      static int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
      for (int i = 0; i < 8; ++i) {
        dfsFindWords(x + dx[i], y + dy[i], currentWord, visited);
      }
    }
    // word not found
    visited[x][y] = false;
    currentWord.pop_back();
  }
};

int main() {
  int N;
  cin >> N;
  Board board(N, "EnglishWords.txt");
  Lexicon lex = board.getLexicon();
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      char value;
      cin >> value;
      board.setElement(i, j, value);
    }
    cin.ignore(); // Clear the input buffer after each row
  }
  board.printState();

  while (true) {
    string word;
    cin >> word;
    string lowerWord = word;
    string upperWord = word;
    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
    transform(upperWord.begin(), upperWord.end(), upperWord.begin(), ::toupper);

    if (word == "???") {
      board.findAllWords();
      cout << "Computer Score: " << board.getComputerScore() << endl;
      cout << "Computer Words: ";
      set<string> foundWords = board.getComputerFoundWords();
      for (const auto &word : foundWords) {
        cout << word << ' ';
      }
      cout << endl;
      break;
    }

    if (word.length() < 4) {
      cout << word << " is too short." << endl;
      continue;
    }
    if (board.hasWordBeenFound(lowerWord)) {
      cout << word << " is already found." << endl;
      continue;
    }
    if (!lex.contains(lowerWord)) {
      cout << word << " is not a word." << endl;
      continue;
    }
    if (!board.findWordInMap(upperWord)) {
      cout << word << " is not on board." << endl;
      continue;
    }
    board.addWord(word);
    board.setScore(board.getScore() + word.length() - 3);
    board.printState();
  }
  return 0;
}
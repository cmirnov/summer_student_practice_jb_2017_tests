#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <fstream>
#include <regex>
#include <iterator>
#include <vector>

namespace fs = std::experimental::filesystem;

class InvalidOption {
  private:
    std::string message;

  public:
    InvalidOption(std::string str) : message(str) {}
    void showMessage() {
      std::cout << "\"" << message << "\" is invalid message\n";
    }
};

class Input {
  private:
    bool caseSensitive;
    bool invert;
    bool regexp;
    bool recursive;
    std::string pattern;
    std::string path;

  public:
    Input(int argc, char *argv[]) {
      caseSensitive = true;
      invert = false;
      regexp = false;
      recursive = false;
      for (int i = 1; i < argc - 2; ++i) {
        if (!strcmp(argv[i], "-i")) {
          caseSensitive = false;
          continue;
        }
        if (!strcmp(argv[i], "-v")) {
          invert = true;
          continue;
        }
        if (!strcmp(argv[i], "-E")) {
          regexp = true;
          continue;
        }
        if (!strcmp(argv[i], "-R")) {
          recursive = true;
          continue;
        }
        throw(new InvalidOption(argv[i]));
      }
      for (int i = 0; argv[argc - 2][i]; ++i) {
        pattern.push_back(argv[argc - 2][i]);
      }
      path = "./";
      for (int i = 0; argv[argc - 1][i]; ++i) {
        path.push_back(argv[argc - 1][i]);
      }
    }
    std::string getPattern() {
      return pattern;
    }
    std::string getPath() {
      return path;
    }
    bool getRecursive() {
      return recursive;
    }
    bool getRegexp() {
      return regexp;
    }
};

class Solver {
  private:
    Input* input;

  public:
    Solver(Input* input) : input(input) {}
    void run();
    void findByStr();
    void findByRegexp();
    bool check(std::string pattern, std::string str);
    std::vector <int> pFunc(std::string pattern, std::string str);
    void outputStr(const fs::directory_entry entry);
    void outputRegexp(const fs::directory_entry entry);
  };

  void Solver::run() {
    if (this->input->getRegexp()) {
      this->findByRegexp();
    } else {
      this->findByStr();
    }
}

void Solver::findByStr() {
  const fs::directory_entry entry(this->input->getPath());
  if (fs::is_regular_file(entry)) {
    outputStr(entry);
  } else {
    if (this->input->getRecursive()) {
      for (auto& p : fs::recursive_directory_iterator(this->input->getPath())) {
        const fs::directory_entry& entry = p;
        if (fs::is_regular_file(entry)) {
          outputStr(entry);
        }
      }
    } else {
      for (auto& p : fs::directory_iterator(this->input->getPath())) {
        const fs::directory_entry& entry = p;
        if (fs::is_regular_file(entry)) {
          outputStr(entry);
        }
      }
    }
  }
}

std::vector <int> Solver::pFunc(std::string pattern, std::string str) {
  std::string s = pattern;
  s += "#";
  s += str;
  int n = s.length();
  std::vector<int> pi(n);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
  return pi;
}

bool Solver::check(std::string pattern, std::string str) {
  std::vector <int> pi = this->pFunc(pattern, str);
  for (int i = pattern.length(); i < pi.size(); ++i) {
    if (pi[i] == pattern.length()) {
      return true;
    }
  }
  return false;
}

void Solver::findByRegexp() {
  const fs::directory_entry entry(this->input->getPath());
  if (fs::is_regular_file(entry)) {
    outputRegexp(entry);
  } else {
    if (this->input->getRecursive()) { 
      for (auto& p : fs::recursive_directory_iterator(this->input->getPath())) {
        const fs::directory_entry& entry = p;
        if (fs::is_regular_file(entry)) {
          outputRegexp(entry);
        }
      }
    } else {
      for (auto& p : fs::directory_iterator(this->input->getPath())) {
        const fs::directory_entry& entry = p;
        if (fs::is_regular_file(entry)) {
          outputRegexp(entry);
        }
      }
    }
  }
}

void Solver::outputStr(const fs::directory_entry entry) {
  std::ifstream in(entry.path().string());
  std::string s;
  while (std::getline(in, s)) {
    if (this->check(this->input->getPattern(), s)) {
      std::vector<int> pi = pFunc(this->input->getPattern(), s);
      int n = this->input->getPattern().length();
      for (int i = n + 1; i < pi.size() - n + 1; ++i) {
        if (pi[i + n - 1] == n) {
          for (int j = 0; j < n; ++j) {
            std::cout << "\033[31m" << s[i - n - 1 + j];
          }
          i--;
          i += n;
        } else {
          std::cout << "\033[37m" << s[i - n - 1];
        }
      }
      std::cout << '\n';
    }
  }
}

int mmax(int a, int b) {
  return a > b ? a : b;
}

void Solver::outputRegexp(const fs::directory_entry entry) {
  std::regex reg(this->input->getPattern());
  std::ifstream in(entry.path().string());
  std::smatch m;
  std::string s;
  while (std::getline(in, s)) {
    if (std::regex_search(s, m, reg)) {
      int idx = 0;
      int n = this->input->getPattern().length();
      for (int i = 0; i < s.length(); ++i) {
        if (idx < m.size() && m.position(idx) == i) {
          int to = i + m[idx].length();
          while (idx < m.size() && m.position(idx) < to) {
            to = mmax(to, m.position(idx) + m[idx].length());
            idx++;
          }
          for (; i < to; ++i) {
            std::cout << "\033[31m" << s[i];
          }
        } else {
          std::cout << "\033[37m" << s[i];
        }
      }
      std::cout << "\033[37m" << '\n';
    }
  }
}

int main(int argc, char *argv[]) {
  try {
    Input* input = new Input(argc, argv);
    Solver* solver = new Solver(input);
    solver->run();
  }
  catch(InvalidOption *e) {
    e->showMessage();
  }
  return 0;
}

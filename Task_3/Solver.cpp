#include "Solver.h"


Solver::Solver(Input* in) {
  input = in;
}

Solver::~Solver() {
  delete input;
}

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
    if (this->input->getInvert() ^ this->check(this->input->getPattern(), s)) {
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
    if (this->input->getInvert() ^ std::regex_search(s, m, reg)) {
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


#include "Support.h"
#include "Solver.h"

namespace fs = std::experimental::filesystem;

class Solver;

std::vector<std::string> outputStr(const fs::directory_entry entry, std::string pattern, bool invert) {
  std::ifstream in(entry.path().string());
  std::string s;
  std::vector<std::string> res;
  while (std::getline(in, s)) {
    if (invert ^ check(pattern, s)) {
      res.push_back("");
      std::vector<int> pi = pFunc(pattern, s);
      int n = pattern.length();
      for (int i = n + 1; i < pi.size() - n + 1; ++i) {
        if (pi[i + n - 1] == n) {
          
          for (int j = 0; j < n; ++j) {
            res.back().push_back(s[i - n - 1 + j]);
          }
          i--;
          i += n;
        } else {
          res.back().push_back(s[i - n - 1]);
        }
      }
    }
  }
  return res;
}

int mmax(int a, int b) {
  return a > b ? a : b;
}

std::vector<std::string> outputRegexp(const fs::directory_entry entry, std::string pattern, bool invert) {
  std::regex reg(pattern);
  std::ifstream in(entry.path().string());
  std::smatch m;
  std::string s;
  std::vector<std::string> res;
  while (std::getline(in, s)) {
    if (invert ^ std::regex_search(s, m, reg)) {
      res.push_back("");
      int idx = 0;
      int n = pattern.length();
      for (int i = 0; i < s.length(); ++i) {
        if (idx < m.size() && m.position(idx) == i) {
          int to = i + m[idx].length();
          while (idx < m.size() && m.position(idx) < to) {
            to = mmax(to, m.position(idx) + m[idx].length());
            idx++;
          }
          for (; i < to; ++i) {
            res.back().push_back(s[i]);
          }
        } else {
          res.back().push_back(s[i]);
        }
      }
    }
  }
  return res;
}

bool check(std::string pattern, std::string str) {
  std::vector <int> pi = pFunc(pattern, str);
  for (int i = pattern.length(); i < pi.size(); ++i) {
    if (pi[i] == pattern.length()) {
      return true;
    }
  }
  return false;
}

std::vector <int> pFunc(std::string pattern, std::string str) {
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


#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <fstream>
#include <regex>
#include <iterator>
#include <vector>
#include "Input.h"

namespace fs = std::experimental::filesystem;

class Solver {
  private:
    Input* input;

  public:
    Solver(Input* input);
    ~Solver();
    void run();
    void findByStr();
    void findByRegexp();
    bool check(std::string pattern, std::string str);
    std::vector <int> pFunc(std::string pattern, std::string str);
    void outputStr(const fs::directory_entry entry);
    void outputRegexp(const fs::directory_entry entry);
};


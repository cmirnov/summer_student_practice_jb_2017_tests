#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <fstream>
#include <regex>
#include <iterator>
#include <vector>
#include "Input.h"
#include <mutex>
#include <thread>
#include "Support.h"

namespace fs = std::experimental::filesystem;

class Solver {
  private:
    std::vector<std::vector<std::string>> output;
  public:
    Input* input;
    Solver(Input* input);
    ~Solver();
    void run();
    void findByStr();
    void findByRegexp();
    std::mutex lock;
};


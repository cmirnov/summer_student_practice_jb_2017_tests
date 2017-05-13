#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <fstream>
#include <regex>
#include <iterator>
#include <vector>
#include <mutex>


namespace fs = std::experimental::filesystem;

class Solver;

std::vector<std::string> outputStr(const fs::directory_entry entry, std::string pattern, bool invert);
std::vector<std::string> outputRegexp(const fs::directory_entry entry, std::string pattern, bool invert);
int mmax(int a, int b);
bool check(std::string pattern, std::string str);
std::vector <int> pFunc(std::string pattern, std::string str);


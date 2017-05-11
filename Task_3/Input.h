#include "InvalidOption.h"
#include "InvalidNumberOfArg.h"
#include <string>

class Input {
  private:
    bool caseSensitive;
    bool invert;
    bool regexp;
    bool recursive;
    std::string pattern;
    std::string path;

  public:
    Input(int argc, char *argv[]);
    ~Input();
    std::string getPattern();
    std::string getPath();
    bool getRecursive();
    bool getRegexp();
    bool getInvert();
};


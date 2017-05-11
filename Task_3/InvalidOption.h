#include <iostream>
#include <string>

class InvalidOption {
  private:
    std::string message;

  public:
    InvalidOption(std::string str);
    ~InvalidOption();
    void showMessage();
};


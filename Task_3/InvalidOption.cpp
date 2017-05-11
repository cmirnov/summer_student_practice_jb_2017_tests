#include "InvalidOption.h"

InvalidOption::InvalidOption(std::string str) {
  this->message = str;
}

InvalidOption::~InvalidOption() {}

void InvalidOption::showMessage() {
  std::cout << "\"" << this->message << "\" is invalid message\n";
}

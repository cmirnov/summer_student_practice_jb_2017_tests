#include "Input.h"
#include <string.h>
#include <iostream>

Input::Input(int argc, char *argv[]) {
  if (argc > 1 && !strcmp(argv[1], "--help")) {
    std::cout << "\t-E, --extended-regexp\n\t-i, --ignore-case\n\t-R, --dereference-recursive\n\t-v, --invert-match\n";
    return;
  }
  if (argc < 3) {
    throw (new InvalidNumberOfArg());
  }
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

Input::~Input() {}
std::string Input::getPattern() {
  return pattern;
}
std::string Input::getPath() {
  return path;
}
bool Input::getRecursive() {
  return recursive;
}
bool Input::getRegexp() {
  return regexp;
}
bool Input::getInvert() {
  return invert;
}

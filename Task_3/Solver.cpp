#include "Solver.h"
#include "Support.h"
#include <future>
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
    std::vector<std::string> res = outputStr(entry, this->input->getPattern(), this->input->getInvert());
    for (int i = 0; i < res.size(); ++i) {
      std::cout << res[i] << '\n';
    }
  } else {
    std::vector<std::future<std::vector<std::string>>> threads;
    if (this->input->getRecursive()) {
      for (auto& p : fs::recursive_directory_iterator(this->input->getPath())) {
        const fs::directory_entry& entry = p;
        if (fs::is_regular_file(entry)) {
          threads.push_back(std::async(outputStr, entry, this->input->getPattern(), this->input->getInvert()));
        }
      }
    } else {
      for (auto& p : fs::directory_iterator(this->input->getPath())) {
        const fs::directory_entry& entry = p;
        if (fs::is_regular_file(entry)) {
          threads.push_back(std::async(outputStr, entry, this->input->getPattern(), this->input->getInvert()));
        }
      }
    }
    for (int i = 0; i < threads.size(); ++i) {
      std::vector<std::string> out = threads[i].get();
      for (int j = 0; j < out.size(); ++j) {
        std::cout << out[j] << '\n';
      }
    }
  }
}

void Solver::findByRegexp() {
  const fs::directory_entry entry(this->input->getPath());
  if (fs::is_regular_file(entry)) {
    std::vector<std::string> res = outputRegexp(entry, this->input->getPattern(), this->input->getInvert());
    for (int i = 0; i < res.size(); ++i) {
      std::cout << res[i] << '\n';
    }
  } else {
    std::vector<std::future<std::vector<std::string>>> threads;
    if (this->input->getRecursive()) { 
      for (auto& p : fs::recursive_directory_iterator(this->input->getPath())) {
        const fs::directory_entry& entry = p;
        if (fs::is_regular_file(entry)) {
          threads.push_back(std::async(outputRegexp, entry, this->input->getPattern(), this->input->getInvert()));
        }
      }
    } else {
      for (auto& p : fs::directory_iterator(this->input->getPath())) {
        const fs::directory_entry& entry = p;
        if (fs::is_regular_file(entry)) {
          threads.push_back(std::async(outputRegexp, entry, this->input->getPattern(), this->input->getInvert()));
        }
      }
    }
    for (int i = 0; i < threads.size(); ++i) {
      std::vector<std::string> out = threads[i].get();
      for (int j = 0; j < out.size(); ++j) {
        std::cout << out[j] << '\n';
      }
    }
  }
}

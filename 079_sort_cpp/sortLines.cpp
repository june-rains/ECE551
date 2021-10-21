#include <algorithm>  // std::sort
#include <cstdlib>    // EXIT_SUCCESS
#include <fstream>    // std::ifstream
#include <iostream>   // std::cin, std::cout
#include <vector>     //std::vector

void sort_lines(std::istream & is) {
  std::string str;
  std::vector<std::string> lines;
  while (getline(is, str)) {
    lines.push_back(str);
  }

  if ((is.eof() != 1) && (is.good() != 1)) {
    std::cerr << "error when reading from input" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::sort(lines.begin(), lines.end());
  typename std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

void sort_files(int argc, char ** argv) {
  for (int i = 1; i < argc; i++) {
    std::ifstream ifs(argv[i], std::ifstream::in);
    if (!ifs.is_open()) {
      std::cerr << "Can not open the file" << std::endl;
      exit(EXIT_FAILURE);
    }
    sort_lines(ifs);
    ifs.close();
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sort_lines(std::cin);
  }

  if (argc > 1) {
    sort_files(argc, argv);
  }
}

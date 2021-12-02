#include <cstdlib>
#include <fstream>
#include <iostream>

#include "cyoa1.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Invalid Argument!\n";
    exit(EXIT_FAILURE);
  }
  std::ifstream ifsn(argv[1], std::ifstream::in);
  std::ifstream ifsc(argv[1], std::ifstream::in);
  if (!ifsn.is_open() || !ifsc.is_open()) {
    std::cerr << "Can not open the file!\n";
    exit(EXIT_FAILURE);
  }

  std::vector<std::string> navigation = parseNav(ifsn);
  std::map<unsigned, std::string> choices;
  std::vector<std::string> navCont;
  std::vector<std::string> contents = parseCont(ifsc);
  bool is_normal = is_pageNormal(navigation);
  if (is_normal) {
    choices = parseChoice(navigation);
    navCont = cutNav(navigation);
  }

  if (is_normal) {
    normalPage page(contents, choices, navCont);
    page.printContents();
    std::cout << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << std::endl;
    page.printChoices();
  }

  else {
    std::string nav = navigation[0];
    winlosePage page(contents, nav);
    page.printContents();
    std::cout << std::endl;
    page.printChoices();
  }

  ifsn.close();
  ifsc.close();
  return EXIT_SUCCESS;
}

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "cyoa.hpp"

int main(int argc, char ** argv) {
  // std::ifstream ifs = openFiles(argc, argv);

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
  std::vector<std::string> contents = parseCont(ifsc);
  bool is_normal = is_pageNormal(navigation);
  if (is_normal) {
    choices = parseChoice(navigation);
  }

  if (is_normal) {
    normalPage page(contents, choices);
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

  //test stub code
  /*
  for (size_t i = 0; i < navigation.size(); ++i) {
    std::cout << navigation[i] << std::endl;
  }

  for (size_t i = 0; i < contents.size(); ++i) {
    std::cout << contents[i] << std::endl;
  }
  for (std::map<unsigned, std::string>::iterator it = choices.begin();
       it != choices.end();
       ++it) {
    std::cout << it->first << " => " << it->second << '\n';
  }

  std::cout << "Success\n";
  */
  ifsn.close();
  ifsc.close();
  return EXIT_SUCCESS;
}

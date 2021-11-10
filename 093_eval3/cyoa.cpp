#include "cyoa.hpp"

/*
std::ifstream openFiles(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Invalid Argument!\n";
    exit(EXIT_FAILURE);
  }
  std::ifstream ifs(argv[1], std::ifstream::in);
  if (!ifs.is_open()) {
    std::cerr << "Can not open the file!\n";
    exit(EXIT_FAILURE);
  }

  return ifs;
}
*/

std::vector<std::string> parseNav(std::ifstream & ifs) {
  std::string str;
  std::vector<std::string> lines;
  std::vector<std::string> navigation;

  while (std::getline(ifs, str)) {
    lines.push_back(str);
  }

  if ((ifs.eof() != 1) && (ifs.good() != 1)) {
    std::cerr << "error when reading from input" << std::endl;
    exit(EXIT_FAILURE);
  }

  size_t index_seperate = 0;
  size_t num_seperate = 0;
  for (size_t i = 0; i < lines.size(); i++) {
    if (lines[i].find('#') == 0) {
      num_seperate++;
      index_seperate = i;
    }
  }

  if (num_seperate == 0) {
    std::cerr << "Invalid Input Format: No #!\n";
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < index_seperate; ++i) {
    navigation.push_back(lines[i]);
  }

  return navigation;
}

std::vector<std::string> parseCont(std::ifstream & ifs) {
  std::string str;
  std::vector<std::string> lines;
  std::vector<std::string> contents;
  while (std::getline(ifs, str)) {
    lines.push_back(str);
  }

  size_t index_seperate = 0;
  for (size_t i = 0; i < lines.size(); i++) {
    if (lines[i].find('#') == 0) {
      index_seperate = i;
    }
  }

  for (size_t i = index_seperate + 1; i < lines.size(); ++i) {
    contents.push_back(lines[i]);
  }

  return contents;
}

std::map<unsigned, std::string> parseChoice(std::vector<std::string> & nav) {
  std::map<unsigned, std::string> choices;

  for (size_t i = 0; i < nav.size(); i++) {
    int found = nav[i].find(':');
    if (found == -1) {
      std::cerr << "Invaild Input Format: no colon in choices!\n";
      exit(EXIT_FAILURE);
    }
    std::string choiceNum;
    std::string choiceCont;
    choiceNum = nav[i].substr(0, found);
    choiceCont = nav[i].substr(found + 1);
    const char * choiceNum_char = choiceNum.c_str();
    char * endptr;
    long num = strtol(choiceNum_char, &endptr, 10);
    if (endptr == choiceNum_char) {
      std::cerr << "Invalid Input Format: can not convert to number!\n";
      exit(EXIT_FAILURE);
    }
    if (num <= 0) {
      std::cerr << "Invalid Input Format: Invalid Number!(Neg or Zero)\n";
      exit(EXIT_FAILURE);
    }
    choices[num] = choiceCont;
  }
  return choices;
}

bool is_pageNormal(std::vector<std::string> & nav) {
  bool normal = true;
  std::string strWin("WIN");
  std::string strLose("LOSE");
  if ((nav.size() == 1) &&
      ((nav[0].compare(strWin) == 0) || (nav[0].compare(strLose) == 0))) {
    normal = false;
  }
  return normal;
}

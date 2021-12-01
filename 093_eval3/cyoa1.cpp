#include "cyoa1.hpp"

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

std::vector<std::string> cutNav(std::vector<std::string> & nav) {
  std::vector<std::string> navCont;

  for (size_t i = 0; i < nav.size(); i++) {
    int found = nav[i].find(':');
    navCont.push_back(nav[i].substr(found + 1));
  }
  return navCont;
}

Page * makeOnePage(std::ifstream & ifsn, std::ifstream & ifsc) {
  Page * newpage;
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
    newpage = new normalPage(contents, choices, navCont);
  }

  else {
    std::string nav = navigation[0];
    newpage = new winlosePage(contents, nav);
  }

  return newpage;
}

std::vector<Page *> makePages(int argc, char ** argv) {
  std::vector<Page *> Pages;
  if (argc != 2) {
    std::cerr << "Invalid Argument!\n";
    exit(EXIT_FAILURE);
  }

  std::stringstream ss1;
  ss1 << argv[1] << "/page1.txt";
  const char * page1Name = ss1.str().c_str();
  std::ifstream ifsn1(page1Name, std::ifstream::in);
  std::ifstream ifsc1(page1Name, std::ifstream::in);

  if (!ifsn1.is_open() || !ifsc1.is_open()) {
    std::cerr << "Not have page1.txt!!\n";
    exit(EXIT_FAILURE);
  }

  Pages.push_back(makeOnePage(ifsn1, ifsc1));

  while (true) {
    std::stringstream ss;
    size_t index = 2;
    ss << argv[1] << "/page" << index << ".txt";
    const char * pageName = ss.str().c_str();
    std::ifstream ifsn(pageName, std::ifstream::in);
    std::ifstream ifsc(pageName, std::ifstream::in);

    if (!ifsn.is_open() || !ifsc.is_open()) {
      break;
    }
    Pages.push_back(makeOnePage(ifsn, ifsc));
  }
  return Pages;
}

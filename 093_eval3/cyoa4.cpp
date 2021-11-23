#include "cyoa4.hpp"

void Page::printContents() {
  std::vector<std::string>::iterator it = contents.begin();
  while (it != contents.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

bool Page::is_pageNormal() {
  bool normal = true;
  std::string strWin("WIN");
  std::string strLose("LOSE");
  if ((navigation.size() == 1) &&
      ((navigation[0].compare(strWin) == 0) || (navigation[0].compare(strLose) == 0))) {
    normal = false;
  }
  return normal;
}

std::vector<std::string> Page::parseNav() {
  std::vector<std::string> navCont;
  if (is_pageNormal()) {
    for (size_t i = 0; i < navigation.size(); i++) {
      int found = navigation[i].find(':');
      if (found == -1) {
        std::cerr << "Invaild Input Format: no colon in choices!\n";
        exit(EXIT_FAILURE);
      }
      std::string choiceNum;
      std::string choiceCont;
      choiceNum = navigation[i].substr(0, found);
      choiceCont = navigation[i].substr(found + 1);
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
      navCont.push_back(choiceCont);
    }
  }
  else {
    navCont.push_back(navigation[0]);
  }
  return navCont;
}

std::vector<unsigned> Page::getChoiceNum() {
  std::vector<unsigned> choiceNum;
  if (is_pageNormal()) {
    for (size_t i = 0; i < navigation.size(); i++) {
      int found = navigation[i].find(':');
      if (found == -1) {
        std::cerr << "Invaild Input Format: no colon in choices!\n";
        exit(EXIT_FAILURE);
      }
      std::string Num;
      Num = navigation[i].substr(0, found);
      const char * choiceNum_char = Num.c_str();
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
      choiceNum.push_back(num);
    }
  }
  return choiceNum;
}

void Page::printPages() {
  if (is_pageNormal()) {
    printContents();
    std::cout << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << std::endl;
    printNav();
  }
  else {
    printContents();
    std::cout << std::endl;
    printNav();
  }
}

void Page::printNav() {
  std::vector<std::string> navCont;
  if (is_pageNormal()) {
    navCont = parseNav();
    int index = 1;
    for (std::vector<std::string>::iterator it = navCont.begin(); it != navCont.end();
         ++it) {
      std::cout << " " << index << ". " << *it << '\n';
      index++;
    }
  }
  else {
    std::string strWin("WIN");
    std::string strLose("LOSE");
    navCont = parseNav();
    if (!navCont[0].compare(strWin)) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    if (!navCont[0].compare(strLose)) {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
  }
}

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

Page makeOnePage(std::ifstream & ifsn, std::ifstream & ifsc) {
  std::vector<std::string> navigation = parseNav(ifsn);
  std::vector<std::string> contents = parseCont(ifsc);
  Page newpage(contents, navigation);
  return newpage;
}

std::vector<Page> makePages(int argc, char ** argv) {
  std::vector<Page> Pages;
  if (argc != 2) {
    std::cerr << "Invalid Argument!\n";
    exit(EXIT_FAILURE);
  }

  std::stringstream ss1;
  ss1 << argv[1] << "/page1.txt";
  std::ifstream ifsn1(ss1.str().c_str(), std::ifstream::in);
  std::ifstream ifsc1(ss1.str().c_str(), std::ifstream::in);

  if (!ifsn1.is_open() || !ifsc1.is_open()) {
    std::cerr << "Not have page1.txt!!\n";
    exit(EXIT_FAILURE);
  }

  Pages.push_back(makeOnePage(ifsn1, ifsc1));
  ifsn1.close();
  ifsc1.close();
  size_t index = 2;
  while (true) {
    std::stringstream ss;
    ss << argv[1] << "/page" << index << ".txt";
    std::ifstream ifsn(ss.str().c_str(), std::ifstream::in);
    std::ifstream ifsc(ss.str().c_str(), std::ifstream::in);

    if (!ifsn.is_open() || !ifsc.is_open()) {
      break;
    }
    Pages.push_back(makeOnePage(ifsn, ifsc));
    index++;
    ifsn.close();
    ifsc.close();
  }
  return Pages;
}

void checkPages(std::vector<Page> & p) {
  int numWin = 0;
  int numLose = 0;
  std::vector<unsigned> choiceNum;
  for (size_t i = 0; i < p.size(); i++) {
    std::vector<std::string> navCont = p[i].getNav();
    if (!p[i].is_pageNormal()) {
      if (!navCont[0].compare("WIN")) {
        numWin++;
      }
      else {
        numLose++;
      }
    }

    else {
      std::vector<unsigned> num;
      num = p[i].getChoiceNum();
      for (size_t j = 0; j < num.size(); j++) {
        choiceNum.push_back(num[j]);
      }
    }
  }
  if (numWin == 0 || numLose == 0) {
    std::cerr << "Invalid Page Format: no WIN or no LOSE" << std::endl;
    exit(EXIT_FAILURE);
  }
  for (size_t m = 0; m < choiceNum.size(); m++) {
    if (choiceNum[m] > p.size()) {
      std::cerr << "Invalid Page Format: invalid reference page!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  for (unsigned n = 2; n <= p.size(); n++) {
    bool find = false;
    for (size_t k = 0; k < choiceNum.size(); k++) {
      if (choiceNum[k] == n) {
        find = true;
        break;
      }
    }
    if (find == false) {
      std::cerr << "Invalid Page Format : not every page is referenced at least once!"
                << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

void getStory(std::vector<Page> & pageStory, unsigned pageNum) {
  pageStory[pageNum - 1].printPages();
  if (!pageStory[pageNum - 1].is_pageNormal()) {
    exit(EXIT_SUCCESS);
  }
  else {
    int choice;
    std::cin >> choice;
    while (true) {
      if (!std::cin.good()) {
        std::cin.clear();
        std::string badinput;
        std::cin >> badinput;
      }
      //!!!!!!!Corner Case!!!!!
      else if (choice <= 0 || choice > (int)pageStory[pageNum - 1].getNav().size()) {
        std::cout << "That is not a valid choice, please try again\n";
        std::cin >> choice;
      }
      else {
        break;
      }
    }
    std::vector<unsigned> choiceNum = pageStory[pageNum - 1].getChoiceNum();
    return getStory(pageStory, choiceNum[choice - 1]);
  }
}
bool Page::isVisited() {
  if (visited == true) {
    return true;
  }
  else {
    return false;
  }
}

void BFS(std::vector<Page> & p) {
  p[0].setVisited();
  std::queue<Page> myqueue;
  myqueue.push(p[0]);
  while (!myqueue.empty()) {
    int currdepth = myqueue.front().getDepth();
    std::vector<unsigned> choiceNum = myqueue.front().getChoiceNum();
    myqueue.pop();
    for (size_t i = 0; i < choiceNum.size(); i++) {
      if (!p[choiceNum[i] - 1].isVisited()) {
        p[choiceNum[i] - 1].setVisited();
        p[choiceNum[i] - 1].setDepth(currdepth + 1);
        myqueue.push(p[choiceNum[i] - 1]);
      }
    }
  }
}

void printDepth(std::vector<Page> & p) {
  for (size_t i = 0; i < p.size(); i++) {
    std::cout << "Page " << i + 1 << ":" << p[i].getDepth() << std::endl;
  }
}

void DFS(std::vector<Page> & p) {
  p[0].setVisited();
  std::stack<Page> mystack;
  mystack.push(p[0]);
  while (!mystack.empty()) {
    int currNum = mystack.top().getpageNum();
    Page * curr = &p[currNum - 1];

    std::vector<unsigned> choiceNum = mystack.top().getChoiceNum();
    mystack.pop();
    for (size_t i = 0; i < choiceNum.size(); i++) {
      if (p[choiceNum[i] - 1].is_pageWin()) {
        p[choiceNum[i] - 1].setPrev(curr);
        p[choiceNum[i] - 1].setChoice(i + 1);
        p[choiceNum[i] - 1].setpageNum(choiceNum[i]);
        printSolution(&p[choiceNum[i] - 1]);
        continue;
      }

      if (!p[choiceNum[i] - 1].isVisited()) {
        p[choiceNum[i] - 1].setVisited();
        p[choiceNum[i] - 1].setPrev(curr);
        p[choiceNum[i] - 1].setChoice(i + 1);
        p[choiceNum[i] - 1].setpageNum(choiceNum[i]);
        mystack.push(p[choiceNum[i] - 1]);
      }
    }
  }
}

bool Page::is_pageWin() {
  bool win = false;
  std::string strWin("WIN");
  if ((navigation.size() == 1) && ((navigation[0].compare(strWin) == 0))) {
    win = true;
  }
  return win;
}

void printSolution(Page * p) {
  std::vector<Page *> pageSol;
  Page * curr = p;
  while (curr->getPrev() != NULL) {
    pageSol.push_back(curr);
    curr = curr->getPrev();
  }
  pageSol.push_back(curr);
  std::vector<Page *>::iterator it_s = pageSol.begin();
  std::vector<Page *>::iterator it_e = pageSol.end();
  std::reverse(it_s, it_e);

  int pathlen = pageSol.size();
  for (int i = 0; i < pathlen - 1; i++) {
    std::cout << pageSol[i]->getpageNum() << "(" << pageSol[i + 1]->getChoice() << "),";
  }
  std::cout << pageSol[pathlen - 1]->getpageNum() << "(win)\n";
}

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Page {
  std::vector<std::string> contents;

 public:
  Page(std::vector<std::string> & ct) : contents(ct){};
  virtual void printChoices() = 0;
  virtual void printContents() {
    std::vector<std::string>::iterator it = contents.begin();
    while (it != contents.end()) {
      std::cout << *it << std::endl;
      ++it;
    }
  }
  virtual ~Page() {}
};

class normalPage : public Page {
  std::map<unsigned, std::string> choices;

 public:
  normalPage(std::vector<std::string> & ct, std::map<unsigned, std::string> & ch) :
      Page(ct),
      choices(ch) {}

  virtual void printChoices() {
    int index = 1;
    std::vector<unsigned> intArray;
    for (std::map<unsigned, std::string>::iterator it = choices.begin();
         it != choices.end();
         ++it) {
      intArray.push_back(it->first);
    }

    std::sort(intArray.begin(), intArray.end());
    for (size_t i = 0; i < choices.size(); i++) {
      std::cout << " " << index << ". " << choices[intArray[i]] << '\n';
      index++;
    }
  }
  virtual ~normalPage(){};
};

class winlosePage : public Page {
  std::string choices;

 public:
  winlosePage(std::vector<std::string> & ct, std::string & nav) :
      Page(ct),
      choices(nav){};
  virtual void printChoices() {
    std::string strWin("WIN");
    std::string strLose("LOSE");
    if (!choices.compare(strWin)) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    if (!choices.compare(strLose)) {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
  }
  virtual ~winlosePage(){};
};

//std::ifstream openFiles(int argc, char ** argv);

std::vector<std::string> parseNav(std::ifstream & ifs);

std::vector<std::string> parseCont(std::ifstream & ifs);

std::map<unsigned, std::string> parseChoice(std::vector<std::string> & nav);

bool is_pageNormal(std::vector<std::string> & nav);

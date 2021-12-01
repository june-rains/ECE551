#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
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
  std::vector<std::string> navigation;

 public:
  normalPage(std::vector<std::string> & ct,
             std::map<unsigned, std::string> & ch,
             std::vector<std::string> & nav) :
      Page(ct),
      choices(ch),
      navigation(nav) {}
  virtual void printChoices() {
    int index = 1;
    for (std::vector<std::string>::iterator it = navigation.begin();
         it != navigation.end();
         ++it) {
      std::cout << " " << index << ". " << *it << '\n';
      index++;
    }
  }

  virtual std::map<unsigned, std::string> getChoices() { return choices; };
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

  virtual std::string getChoices() { return choices; }
  virtual ~winlosePage(){};
};

std::vector<std::string> parseNav(std::ifstream & ifs);

std::vector<std::string> parseCont(std::ifstream & ifs);

std::map<unsigned, std::string> parseChoice(std::vector<std::string> & nav);

bool is_pageNormal(std::vector<std::string> & nav);

std::vector<std::string> cutNav(std::vector<std::string> & nav);

Page * makeOnePage(std::ifstream & ifsn, std::ifstream & ifsc);

std::vector<Page *> makePages(int argc, char ** argv);

void checkPages(std::vector<Page *> & p);

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
  std::vector<std::string> navigation;

 public:
  Page(std::vector<std::string> & ct, std::vector<std::string> & nav) :
      contents(ct),
      navigation(nav){};
  void printPages();
  void printNav();
  void printContents();
  std::vector<std::string> parseNav();
  bool is_pageNormal();
  std::vector<std::string> getNav() const { return navigation; }
  std::vector<unsigned> getChoiceNum();

  ~Page() {}
};

std::vector<std::string> parseNav(std::ifstream & ifs);

std::vector<std::string> parseCont(std::ifstream & ifs);

Page makeOnePage(std::ifstream & ifsn, std::ifstream & ifsc);

std::vector<Page> makePages(int argc, char ** argv);

void checkPages(std::vector<Page> & p);

void getStory(std::vector<Page> & pageStory, unsigned pageNum);

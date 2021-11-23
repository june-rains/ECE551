#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

class Page {
  std::vector<std::string> contents;
  std::vector<std::string> navigation;
  bool visited;
  int depth;
  int userChoice;
  int pageNum;
  Page * prev;

 public:
  Page(std::vector<std::string> & ct, std::vector<std::string> & nav) :
      contents(ct),
      navigation(nav),
      visited(false),
      depth(0),
      userChoice(0),
      pageNum(1),
      prev(NULL) {}
  void printPages();
  void printNav();
  void printContents();
  std::vector<std::string> parseNav();
  bool is_pageNormal();
  bool is_pageWin();
  std::vector<std::string> getNav() const { return navigation; }
  std::vector<unsigned> getChoiceNum();
  void setVisited() { visited = true; }
  bool isVisited();
  void setDepth(int d) { depth = d; }
  int getDepth() { return depth; }
  void setChoice(int d) { userChoice = d; }
  int getChoice() { return userChoice; }
  void setPrev(Page * p) { prev = p; }
  Page * getPrev() { return prev; }
  void setpageNum(int d) { pageNum = d; }
  int getpageNum() { return pageNum; }
  ~Page() {}
};

std::vector<std::string> parseNav(std::ifstream & ifs);

std::vector<std::string> parseCont(std::ifstream & ifs);

Page makeOnePage(std::ifstream & ifsn, std::ifstream & ifsc);

std::vector<Page> makePages(int argc, char ** argv);

void checkPages(std::vector<Page> & p);

void BFS(std::vector<Page> & p);

void printDepth(std::vector<Page> & p);

void DFS(std::vector<Page> & p);

void printSolution(Page * p);

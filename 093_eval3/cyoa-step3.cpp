#include "cyoa4.hpp"

int main(int argc, char ** argv) {
  std::vector<Page> pageStory = makePages(argc, argv);
  checkPages(pageStory);
  BFS(pageStory);
  printDepth(pageStory);
  return EXIT_SUCCESS;
}

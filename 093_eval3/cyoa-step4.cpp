#include "cyoa4.hpp"

int main(int argc, char ** argv) {
  std::vector<Page> pageStory = makePages(argc, argv);
  checkPages(pageStory);
  DFS(pageStory);

  return EXIT_SUCCESS;
}

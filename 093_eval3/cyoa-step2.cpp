#include "cyoa.hpp"

int main(int argc, char ** argv) {
  std::vector<Page> pageStory = makePages(argc, argv);
  checkPages(pageStory);

  getStory(pageStory, 1);

  return EXIT_SUCCESS;
}

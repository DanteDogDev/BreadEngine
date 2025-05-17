#include "Toast/engine.hpp"

int main(int argc, char** argv) {
  // Sets the .so path to ./modules
  setenv("LD_LIBRARY_PATH", "./modules", 1);

  toast::Engine* app = new toast::Engine;
  if (!app) { return -1; }
  app->Run(argc, argv);
  delete app;

  return 0;
}

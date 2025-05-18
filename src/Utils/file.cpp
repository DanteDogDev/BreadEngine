#include "file.hpp"
#include "Utils/log.hpp"


std::string LoadTextFile(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    TOAST_ERROR("FILE COULD NOT OPEN: {}",path);
  }
  std::stringstream file_stream;
  file_stream << file.rdbuf();
  file.close();
  return file_stream.str();
}

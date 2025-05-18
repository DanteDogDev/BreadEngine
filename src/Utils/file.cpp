#include "file.hpp"

#include "Utils/log.hpp"

namespace utils {

std::string LoadTextFile(const std::string& path) {
  TOAST_INFO("READING FILE: {}", path);
  std::ifstream file(path);
  if (!file.is_open()) { TOAST_ERROR("File Error: Failed to Read: {}", path); }
  std::stringstream file_stream;
  file_stream << file.rdbuf();
  file.close();
  return file_stream.str();
}

}

#include "tracy/Tracy.hpp"

#ifdef TRACY_ENABLE
void* operator new(std ::size_t count) {
  if (auto* ptr = malloc(count)) {    // NOLINT
    TracyAlloc(ptr, count);
    return ptr;
  }

  throw std::bad_alloc();
}

void operator delete(void* ptr) noexcept {
  TracyFree(ptr);
  free(ptr);    // NOLINT
}
#endif

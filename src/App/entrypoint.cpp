/**
 * @file entrypoint.hpp
 * @author Dante Harper
 * @date 17/05/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */

#if defined(__linux__)

#include "Platform/linux.inl"

#else

#error "OS not supported by Toast Engine"

#endif

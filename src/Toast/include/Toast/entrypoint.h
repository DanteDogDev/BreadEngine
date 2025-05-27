/**
 * @file entrypoint.h
 * @author Dante Harper
 * @date 17/05/25
 */

#if defined(__linux__)

#include "../../Platform/linux.inl"

#else

#error "OS not supported by Toast Engine"

#endif

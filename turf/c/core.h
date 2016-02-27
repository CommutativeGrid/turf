/*------------------------------------------------------------------------
  Turf: Configurable C++ platform adapter
  Copyright (c) 2016 Jeff Preshing

  Distributed under the Simplified BSD License.
  Original location: https://github.com/preshing/turf

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the LICENSE file for more information.
------------------------------------------------------------------------*/

#ifndef TURF_C_CORE_H
#define TURF_C_CORE_H

#include "turf_config.h" // turf_config.h generated by CMake.
#include "platform_detect.h"

// clang-format off

//---------------------------------------------
// Global system headers
//---------------------------------------------
#if TURF_TARGET_XBOX_360    // Xbox 360
    #include <xtl.h>
#elif TURF_TARGET_WIN32     // Win32 API
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #include <windows.h>
    #undef WIN32_LEAN_AND_MEAN
    #undef NOMINMAX
#endif

//---------------------------------------------
// Integer types
//---------------------------------------------
#include <stddef.h>
#if TURF_HAS_STDINT
    #include <stdint.h>
#else
	typedef signed char int8_t;
	typedef unsigned char uint8_t;
	#define INT8_MIN (-0x7f - 1)
	#define INT8_MAX 0x7f
	#define UINT8_MAX 0xff

	typedef short int16_t;
	typedef unsigned short uint16_t;
	#define INT16_MIN (-0x7fff - 1)
	#define INT16_MAX 0x7fff
	#define UINT16_MAX 0xffff

	typedef int int32_t;
	typedef unsigned int uint32_t;
	#define INT32_MIN (-0x7fffffff - 1)
	#define INT32_MAX 0x7fffffff
	#define UINT32_MAX 0xffffffff

	typedef __int64 int64_t;
	typedef unsigned __int64 uint64_t;
	#define INT64_MIN (-0x7fffffffffffffff - 1)
	#define INT64_MAX 0x7fffffffffffffff
	#define UINT64_MAX 0xffffffffffffffffu
#endif

// FIXME: Check PowerPC, where registers might be larger than pointers.
typedef intptr_t intreg_t;
typedef uintptr_t uintreg_t;
#define INTREG_MIN INTPTR_MIN
#define INTREG_MAX INTPTR_MAX
#define UINTREG_MAX UINTPTR_MAX

//---------------------------------------------
// Macros
//---------------------------------------------
#if TURF_COMPILER_MSVC
    #include "impl/compiler_msvc.h"
#elif TURF_COMPILER_GCC
    #include "impl/compiler_gcc.h"
#else
    #error "Unsupported platform!"
#endif

#define TURF_STRINGIFY2(x) #x
#define TURF_STRINGIFY(x) TURF_STRINGIFY2(x)
#define TURF_CAT2(a, b) a ## b
#define TURF_CAT(a, b) TURF_CAT2(a, b)
#define TURF_UNIQUE_VARIABLE(prefix) TURF_CAT(prefix, __LINE__)
#define TURF_PTR_OFFSET(ptr, ofs) ((void*)(((u8*)(void*)(ptr)) + (ofs)))
#define TURF_MEMBER_OFFSET(type, member) offsetof(type, member)
#define TURF_STATIC_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define TURF_UNUSED(x) ((void) x)

//---------------------------------------------
// Format strings
//---------------------------------------------
// FIXME: Detect and support format strings used by older compilers/CRTs.
#define TURF_U32D "u"
#define TURF_S32D "d"
#define TURF_U32X "x"
#define TURF_U64D "llu"
#define TURF_S64D "lld"
#define TURF_U64X "llx"
#if TURF_PTR_SIZE == 4
    #define TURF_UPTRD TURF_U32D
    #define TURF_SPTRD TURF_S32D
    #define TURF_UPTRX TURF_U32X
#else
    #define TURF_UPTRD TURF_U64D
    #define TURF_SPTRD TURF_S64D
    #define TURF_UPTRX TURF_U64X
#endif
#define TURF_UREGD TURF_UPTRD
#define TURF_SREGD TURF_SPTRD
#define TURF_UREGX TURF_UPTRX

#endif // TURF_C_CORE_H

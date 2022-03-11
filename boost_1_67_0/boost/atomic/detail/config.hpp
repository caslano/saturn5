/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2012 Hartmut Kaiser
 * Copyright (c) 2014-2018, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/config.hpp
 *
 * This header defines configuraion macros for Boost.Atomic
 */

#ifndef BOOST_ATOMIC_DETAIL_CONFIG_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CONFIG_HPP_INCLUDED_

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__CUDACC__)
// nvcc does not support alternatives ("q,m") in asm statement constraints
#define BOOST_ATOMIC_DETAIL_NO_ASM_CONSTRAINT_ALTERNATIVES
// nvcc does not support condition code register ("cc") clobber in asm statements
#define BOOST_ATOMIC_DETAIL_NO_ASM_CLOBBER_CC
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_ASM_CLOBBER_CC)
#define BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC "cc"
#define BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "cc",
#else
#define BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC
#define BOOST_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA
#endif

#if (defined(__i386__) || defined(__x86_64__)) && (defined(__clang__) || (defined(BOOST_GCC) && (BOOST_GCC+0) < 40500) || defined(__SUNPRO_CC))
// This macro indicates that the compiler does not support allocating eax:edx or rax:rdx register pairs ("A") in asm blocks
#define BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS
#endif

#if defined(__i386__) && (defined(__PIC__) || defined(__PIE__)) && !(defined(__clang__) || (defined(BOOST_GCC) && (BOOST_GCC+0) >= 50100))
// This macro indicates that asm blocks should preserve ebx value unchanged. Some compilers are able to maintain ebx themselves
// around the asm blocks. For those compilers we don't need to save/restore ebx in asm blocks.
#define BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX
#endif

#if defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#if !(defined(BOOST_LIBSTDCXX11) && (BOOST_LIBSTDCXX_VERSION+0) >= 40700) /* libstdc++ from gcc >= 4.7 in C++11 mode */
// This macro indicates that there is not even a basic <type_traits> standard header that is sufficient for most Boost.Atomic needs.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS
#endif
#endif // defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)

#if defined(BOOST_NO_CXX11_ALIGNAS) ||\
    (defined(BOOST_GCC) && (BOOST_GCC+0) < 40900) ||\
    (defined(BOOST_MSVC) && (BOOST_MSVC+0) < 1910 && defined(_M_IX86))
// gcc prior to 4.9 doesn't support alignas with a constant expression as an argument.
// MSVC 14.0 does support alignas, but in 32-bit mode emits "error C2719: formal parameter with requested alignment of N won't be aligned" for N > 4,
// when aligned types are used in function arguments, even though the std::max_align_t type has alignment of 8.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS
#endif

#if defined(BOOST_NO_CXX11_CONSTEXPR) || (defined(BOOST_GCC) && (BOOST_GCC+0) < 40800)
// This macro indicates that the compiler doesn't support constexpr constructors that initialize one member
// of an anonymous union member of the class.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_UNION_INIT
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_UNION_INIT)
#define BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT BOOST_CONSTEXPR
#else
#define BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT
#endif

// Enable pointer/reference casts between storage and value when possible.
// Note: Despite that MSVC does not employ strict aliasing rules for optimizations
// and does not require an explicit markup for types that may alias, we still don't
// enable the optimization for this compiler because at least MSVC-8 and 9 are known
// to generate broken code sometimes when casts are used.
#define BOOST_ATOMIC_DETAIL_MAY_ALIAS BOOST_MAY_ALIAS
#if !defined(BOOST_NO_MAY_ALIAS)
#define BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS
#endif

#if defined(__GCC_ASM_FLAG_OUTPUTS__)
// The compiler supports output values in flag registers.
// See: https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html, Section 6.44.3.
#define BOOST_ATOMIC_DETAIL_ASM_HAS_FLAG_OUTPUTS
#endif

#if defined(BOOST_INTEL) || (defined(BOOST_GCC) && (BOOST_GCC+0) < 40700) ||\
    (defined(BOOST_CLANG) && !defined(__apple_build_version__) && ((__clang_major__+0) * 100 + (__clang_minor__+0)) < 302) ||\
    (defined(__clang__) && defined(__apple_build_version__) && ((__clang_major__+0) * 100 + (__clang_minor__+0)) < 402)
// Intel compiler (at least 18.0 update 1) breaks if noexcept specification is used in defaulted function declarations:
// error: the default constructor of "boost::atomics::atomic<T>" cannot be referenced -- it is a deleted function
// GCC 4.6 doesn't seem to support that either. Clang 3.1 deduces wrong noexcept for the defaulted function and fails as well.
#define BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL
#define BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL BOOST_NOEXCEPT
#else
#define BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL BOOST_NOEXCEPT
#define BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL
#endif

#if defined(__has_builtin)
#if __has_builtin(__builtin_constant_p)
#define BOOST_ATOMIC_DETAIL_IS_CONSTANT(x) __builtin_constant_p(x)
#endif
#elif defined(__GNUC__)
#define BOOST_ATOMIC_DETAIL_IS_CONSTANT(x) __builtin_constant_p(x)
#endif

#if !defined(BOOST_ATOMIC_DETAIL_IS_CONSTANT)
#define BOOST_ATOMIC_DETAIL_IS_CONSTANT(x) false
#endif

#if (defined(__BYTE_ORDER__) && defined(__FLOAT_WORD_ORDER__) && (__BYTE_ORDER__+0) == (__FLOAT_WORD_ORDER__+0)) ||\
    defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
// This macro indicates that integer and floating point endianness is the same
#define BOOST_ATOMIC_DETAIL_INT_FP_ENDIAN_MATCH
#endif

// Deprecated symbols markup
#if !defined(BOOST_ATOMIC_DETAIL_DEPRECATED) && defined(_MSC_VER)
#if (_MSC_VER) >= 1400
#define BOOST_ATOMIC_DETAIL_DEPRECATED(msg) __declspec(deprecated(msg))
#else
// MSVC 7.1 only supports the attribute without a message
#define BOOST_ATOMIC_DETAIL_DEPRECATED(msg) __declspec(deprecated)
#endif
#endif

#if !defined(BOOST_ATOMIC_DETAIL_DEPRECATED) && defined(__has_extension)
#if __has_extension(attribute_deprecated_with_message)
#define BOOST_ATOMIC_DETAIL_DEPRECATED(msg) __attribute__((deprecated(msg)))
#endif
#endif

// gcc since 4.5 supports deprecated attribute with a message; older versions support the attribute without a message.
// Oracle Studio 12.4 supports deprecated attribute with a message; this is the first release that supports the attribute.
#if !defined(BOOST_ATOMIC_DETAIL_DEPRECATED) && (\
    (defined(__GNUC__) && ((__GNUC__ + 0) * 100 + (__GNUC_MINOR__ + 0)) >= 405) ||\
    (defined(__SUNPRO_CC) && (__SUNPRO_CC + 0) >= 0x5130))
#define BOOST_ATOMIC_DETAIL_DEPRECATED(msg) __attribute__((deprecated(msg)))
#endif

#if !defined(BOOST_ATOMIC_DETAIL_DEPRECATED) && __cplusplus >= 201402
#define BOOST_ATOMIC_DETAIL_DEPRECATED(msg) [[deprecated(msg)]]
#endif

#if !defined(BOOST_ATOMIC_DETAIL_DEPRECATED) && defined(__GNUC__)
#define BOOST_ATOMIC_DETAIL_DEPRECATED(msg) __attribute__((deprecated))
#endif

#if !defined(BOOST_ATOMIC_DETAIL_DEPRECATED) && defined(__has_attribute)
#if __has_attribute(deprecated)
#define BOOST_ATOMIC_DETAIL_DEPRECATED(msg) __attribute__((deprecated))
#endif
#endif

#if !defined(BOOST_ATOMIC_DETAIL_DEPRECATED)
#define BOOST_ATOMIC_DETAIL_DEPRECATED(msg)
#endif

// In Boost.Atomic 1.73 we deprecated atomic<>::storage() accessor in favor of atomic<>::value(). In future releases storage() will be removed.
#if !defined(BOOST_ATOMIC_SILENCE_STORAGE_DEPRECATION)
#define BOOST_ATOMIC_DETAIL_STORAGE_DEPRECATED BOOST_ATOMIC_DETAIL_DEPRECATED("Boost.Atomic 1.73 has deprecated atomic<>::storage() in favor of atomic<>::value() and atomic<>::storage_type in favor of atomic<>::value_type. You can define BOOST_ATOMIC_SILENCE_STORAGE_DEPRECATION to disable this warning.")
#else
#define BOOST_ATOMIC_DETAIL_STORAGE_DEPRECATED
#endif

#endif // BOOST_ATOMIC_DETAIL_CONFIG_HPP_INCLUDED_

/* config.hpp
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
*/
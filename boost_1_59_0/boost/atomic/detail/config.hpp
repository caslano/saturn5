/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2012 Hartmut Kaiser
 * Copyright (c) 2014-2018, 2020-2021 Andrey Semashev
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

#if (defined(__i386__) || defined(__x86_64__)) && (defined(__clang__) || (defined(BOOST_GCC) && BOOST_GCC < 40500) || defined(__SUNPRO_CC))
// This macro indicates that the compiler does not support allocating eax:edx or rax:rdx register pairs ("A") in asm blocks
#define BOOST_ATOMIC_DETAIL_X86_NO_ASM_AX_DX_PAIRS
#endif

#if defined(__i386__) && (defined(__PIC__) || defined(__PIE__)) && !(defined(__clang__) || (defined(BOOST_GCC) && BOOST_GCC >= 50100))
// This macro indicates that asm blocks should preserve ebx value unchanged. Some compilers are able to maintain ebx themselves
// around the asm blocks. For those compilers we don't need to save/restore ebx in asm blocks.
#define BOOST_ATOMIC_DETAIL_X86_ASM_PRESERVE_EBX
#endif

#if defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#if !(defined(BOOST_LIBSTDCXX11) && BOOST_LIBSTDCXX_VERSION >= 40700) /* libstdc++ from gcc >= 4.7 in C++11 mode */
// This macro indicates that there is not even a basic <type_traits> standard header that is sufficient for most Boost.Atomic needs.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS
#endif
#endif // defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)

#if defined(BOOST_NO_CXX11_ALIGNAS) ||\
    (defined(BOOST_GCC) && BOOST_GCC < 40900) ||\
    (defined(BOOST_MSVC) && BOOST_MSVC < 1910 && defined(_M_IX86))
// gcc prior to 4.9 doesn't support alignas with a constant expression as an argument.
// MSVC 14.0 does support alignas, but in 32-bit mode emits "error C2719: formal parameter with requested alignment of N won't be aligned" for N > 4,
// when aligned types are used in function arguments, even though the std::max_align_t type has alignment of 8.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS
#endif

#if defined(BOOST_NO_CXX11_CONSTEXPR) || (defined(BOOST_GCC) && BOOST_GCC < 40800)
// This macro indicates that the compiler doesn't support constexpr constructors that initialize one member
// of an anonymous union member of the class.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_UNION_INIT
#endif

#if (defined(_MSC_VER) && (_MSC_VER < 1914 || _MSVC_LANG < 201703)) || (!defined(_MSC_VER) && (!defined(__cpp_deduction_guides) || __cpp_deduction_guides < 201606))
#define BOOST_ATOMIC_DETAIL_NO_CXX17_DEDUCTION_GUIDES
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

#if defined(BOOST_INTEL) || (defined(BOOST_GCC) && BOOST_GCC < 40700) ||\
    (defined(BOOST_CLANG) && !defined(__apple_build_version__) && (__clang_major__ * 100 + __clang_minor__) < 302) ||\
    (defined(__clang__) && defined(__apple_build_version__) && (__clang_major__ * 100 + __clang_minor__) < 402)
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
#if __has_builtin(__builtin_clear_padding)
#define BOOST_ATOMIC_DETAIL_CLEAR_PADDING(x) __builtin_clear_padding(x)
#elif __has_builtin(__builtin_zero_non_value_bits)
#define BOOST_ATOMIC_DETAIL_CLEAR_PADDING(x) __builtin_zero_non_value_bits(x)
#endif
#endif

#if !defined(BOOST_ATOMIC_DETAIL_IS_CONSTANT) && defined(__GNUC__)
#define BOOST_ATOMIC_DETAIL_IS_CONSTANT(x) __builtin_constant_p(x)
#endif

#if !defined(BOOST_ATOMIC_DETAIL_IS_CONSTANT)
#define BOOST_ATOMIC_DETAIL_IS_CONSTANT(x) false
#endif

#if !defined(BOOST_ATOMIC_DETAIL_CLEAR_PADDING) && defined(BOOST_MSVC) && BOOST_MSVC >= 1927
// Note that as of MSVC 19.29 this intrinsic does not clear padding in unions:
// https://developercommunity.visualstudio.com/t/__builtin_zero_non_value_bits-does-not-c/1551510
#define BOOST_ATOMIC_DETAIL_CLEAR_PADDING(x) __builtin_zero_non_value_bits(x)
#endif

#if !defined(BOOST_ATOMIC_DETAIL_CLEAR_PADDING)
#define BOOST_ATOMIC_NO_CLEAR_PADDING
#define BOOST_ATOMIC_DETAIL_CLEAR_PADDING(x)
#endif

#if (defined(__BYTE_ORDER__) && defined(__FLOAT_WORD_ORDER__) && __BYTE_ORDER__ == __FLOAT_WORD_ORDER__) ||\
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
    (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) >= 405) ||\
    (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x5130))
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
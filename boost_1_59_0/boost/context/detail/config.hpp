
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_CONFIG_H
#define BOOST_CONTEXT_DETAIL_CONFIG_H

// required for SD-6 compile-time integer sequences
#include <utility>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_CONTEXT_DECL
# undef BOOST_CONTEXT_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CONTEXT_DYN_LINK) ) && ! defined(BOOST_CONTEXT_STATIC_LINK)
# if defined(BOOST_CONTEXT_SOURCE)
#  define BOOST_CONTEXT_DECL BOOST_SYMBOL_EXPORT
#  define BOOST_CONTEXT_BUILD_DLL
# else
#  define BOOST_CONTEXT_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_CONTEXT_DECL)
# define BOOST_CONTEXT_DECL
#endif

#if ! defined(BOOST_USE_UCONTEXT) && defined(__CYGWIN__)
# define BOOST_USE_UCONTEXT
#endif

#if ! defined(BOOST_CONTEXT_SOURCE) && ! defined(BOOST_ALL_NO_LIB) && ! defined(BOOST_CONTEXT_NO_LIB)
# define BOOST_LIB_NAME boost_context
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CONTEXT_DYN_LINK)
#  define BOOST_DYN_LINK
# endif
# include <boost/config/auto_link.hpp>
#endif

#undef BOOST_CONTEXT_CALLDECL
#if (defined(i386) || defined(__i386__) || defined(__i386) \
     || defined(__i486__) || defined(__i586__) || defined(__i686__) \
     || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) \
     || defined(__I86__) || defined(__INTEL__) || defined(__IA32__) \
     || defined(_M_IX86) || defined(_I86_)) && defined(BOOST_WINDOWS)
# define BOOST_CONTEXT_CALLDECL __cdecl
#else
# define BOOST_CONTEXT_CALLDECL
#endif

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if ! ( (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6) ) ) || \
         (defined(__clang__) && (__clang_major__ > 2 || ( __clang_major__ == 2 && __clang_minor__ > 3) ) ) )
#  error "compiler does not support segmented_stack stacks"
# endif
# define BOOST_CONTEXT_SEGMENTS 10
#endif


#define BOOST_CONTEXT_NO_CXX14_INTEGER_SEQUENCE
// use rd6 macros for std::integer_sequence
#if defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304
# undef BOOST_CONTEXT_NO_CXX14_INTEGER_SEQUENCE
#endif
// workaroud: MSVC 14 does not provide macros to test for compile-time integer sequence
#if _MSC_VER > 1800 // _MSC_VER == 1800 -> MS Visual Studio 2013
# undef BOOST_CONTEXT_NO_INDEX_SEQUENCE
#endif
// workaround: Xcode clang feature detection
#if ! defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304
# if _LIBCPP_STD_VER > 11
#  undef BOOST_CONTEXT_NO_CXX14_INTEGER_SEQUENCE
# endif
#endif

// workaroud: MSVC 14 does support constexpr
#if _MSC_VER > 1800 // _MSC_VER == 1800 -> MS Visual Studio 2013
# undef BOOST_NO_CXX11_CONSTEXPR
#endif

#undef BOOST_CONTEXT_NO_CXX11
#if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) || \
    defined(BOOST_NO_CXX11_CONSTEXPR) || \
    defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || \
    defined(BOOST_NO_CXX11_FINAL) || \
    defined(BOOST_NO_CXX11_HDR_TUPLE) || \
    defined(BOOST_NO_CXX11_NOEXCEPT) || \
    defined(BOOST_NO_CXX11_NULLPTR) || \
    defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    defined(BOOST_NO_CXX11_TEMPLATE_ALIASES) || \
    defined(BOOST_NO_CXX11_UNIFIED_INITIALISATION_SYNTAX) || \
    defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || \
    defined(BOOST_NO_HDR_ATOMIC) || \
    defined(BOOST_NO_HDR_TUPLE) 
# define BOOST_CONTEXT_NO_CXX11
#endif

#if ! defined(BOOST_EXECUTION_CONTEXT)
# if defined(BOOST_USE_SEGMENTED_STACKS)
#  define BOOST_EXECUTION_CONTEXT 1
# else
#  define BOOST_EXECUTION_CONTEXT 2
# endif
#endif

#if ! defined(BOOST_NO_CXX11_CONSTEXPR)
// modern architectures have cachelines with 64byte length
// ARM Cortex-A15 32/64byte, Cortex-A9 16/32/64bytes
// MIPS 74K: 32byte, 4KEc: 16byte
// ist should be safe to use 64byte for all
static constexpr std::size_t cache_alignment{ 64 };
static constexpr std::size_t cacheline_length{ 64 };
// lookahead size for prefetching
static constexpr std::size_t prefetch_stride{ 4 * cacheline_length };
#endif

#if defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#  define BOOST_CONTEXT_HAS_CXXABI_H
#endif

#if defined( BOOST_CONTEXT_HAS_CXXABI_H )
# include <cxxabi.h>
#endif

#if defined(__OpenBSD__)
// stacks need mmap(2) with MAP_STACK
# define BOOST_CONTEXT_USE_MAP_STACK
#endif

#endif // BOOST_CONTEXT_DETAIL_CONFIG_H

/* config.hpp
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
*/
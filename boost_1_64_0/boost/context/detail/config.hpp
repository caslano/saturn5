
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
4phpnd1tHzi/pyO5rncV1xIFl+rKG7+qwPWRTPNe4FexnJN8EF1h/NaIDyrJuRjjV2XJUmtjA0il81GZfN5dW6IPIS1bFdKT2/JaPpoTrNPsAr3eHdZL5neP0cu9MH9dVB3uy4spL7b/ptEmV/8lRndeaHT9UhhnuD5BNkjHQsC7/JD3y7QtUF7xHWyLaevLta1KC/f/oK5F6lNgvAFda5CyLeJ74B7Ra2TsXmHa3W3avU/wHH+4r3tlA+Py+hXZc9lnMnFrzfi7GNpUMHbrTUG9msY2chuwjW/h/JnHDB7j15sl3xzTfRrLXP0vU/4dKiPJf2EtlTNvSryrQfZSDE4U9zDv3ZRv/T3C4x+uK763QfXGnPuM+onsy2Ed10ibi9Kva6TNRYhz2iA24YNMv4/H/rUNDpeu3sn89EPos9QMjyUhQIqmaFyUmQPE4+uY/giM6Y+KzvAek5xJbZVY+h9r8P8uRGL4z/Y+bto5B/qyWO2XxbXQT6nstQ7GAboi+88QjPW3HC8m5vfnpsKvDuNfJ2PlI2a96IuOF6GB631fIvgKvd/DsfPomvWAC4NJf66h2JS67mPz6M2uTXxPaTb3p6N9fYNPYZxu1NNNnZ3JrO+60s0qf52jTKZb32hDHvQaUMf6tV10i0TrVzjXTXE4l0HdN0rdMiPgfS2tE4Gurk0ztK61fbRaNega2tfbNzigbS3B13Zs6JM7TQFstcJmlmCrV/dJ2VkBXt+mMzSmp8IGOxTvqBKsb6PCakuwjZ0KOzagV4KdhHUs8+t4SgnW37txkBaNBPeUEry7v331BhKnj99WgncNKN3TS7D2Nbr+tQJlQbUp/JkKh7tgZ5VgnQODIM8NAW6nlu8Buuu7N6/aILj/CdrRfp7AvCqFbWjfrH1UgvV3sTp0ugLSV5E8EtRAV0dpXbBMfm939/re9k6P+zGKc17PJonfGsljxvafSPrYIPp4M/0hWL4eSsLpn8box5j+X1X/T+7xvDnmzeSv8bqOxsbHt7hHhjXmaLAfHLyzWPDXHcaLhdHMrkmY25g95ePdXCe3R24JK56/T7cD76zI3Qc9T7Gc5+3hOJIrXRzWnQITOmuid4vkO0n0Xa2jge+4mWH+EwR6B+kCvYMEvIx7cn9G7g9/Hb4rWY+qx8cBNPZNxbWp0JoM47dNtZZll3HgjYpvMj/5odJ5bj/Niz8ufUspTW2QN+q+RbBG5t3RkwYMahreua64TuZw3XIWM6eJkv9+q5T9lPrvfpk03s/i7wXDdB1Y15sJ5prLVhbvGhE8m8sUMiO0zIJrqQQnDvRssuptwsH5umzwlsJ33HdN8YXGbTzHJphTM9d/cj72uzjHrtDe/vDb9qG3Qj7i9ooJxreOSS2DMZX3myI81Pprf7xw6MqeLGvat4fmiO7Dlpr0FU7+Jg4wfjvxXVpnr9V1ShXwI2adkmuTvqiRdUq4e/YDZw8YtjeVo3HWJjz9ENdqp9DTyZBsxmNkMx6STS3THGcuqPsZV+F1BJfTeaXyCcH1n6Unucl68o9CcnNOgcpN/ibeaDwEej3leKiq+Qn4fXfC2sWtAP+pmWv8TPy4u2QOcHfg70oa4jCZ+cE94mvdC/NuooflaIzCuQvAu1/xhMZPDF+/NnX9Bvi4y/D4oM5TJM/B8QzU79U3hXzqG/qZ8wZKR+q/38wHH5L0r2HeoPUoH+pv3iXzMTufeUTnM1yHnh3Utw3Cc42/Sn0LoZ0qO0yTzVAZsSxvw3kinCO7ievzf49JWZ0n/lPSF1XDO2U0bjWeEv2jMWOVHuuO0lEZ/kd48Bb4PGAZlfkNpswMwkW8xfIv9CPjzSI8tCVV9L6KzGu4r/Q=
*/
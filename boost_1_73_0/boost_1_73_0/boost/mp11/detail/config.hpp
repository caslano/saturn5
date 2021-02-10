#ifndef BOOST_MP11_DETAIL_CONFIG_HPP_INCLUDED
#define BOOST_MP11_DETAIL_CONFIG_HPP_INCLUDED

// Copyright 2016, 2018, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

// BOOST_MP11_WORKAROUND

#if defined( BOOST_STRICT_CONFIG ) || defined( BOOST_MP11_NO_WORKAROUNDS )

# define BOOST_MP11_WORKAROUND( symbol, test ) 0

#else

# define BOOST_MP11_WORKAROUND( symbol, test ) ((symbol) != 0 && ((symbol) test))

#endif

//

#define BOOST_MP11_CUDA 0
#define BOOST_MP11_CLANG 0
#define BOOST_MP11_INTEL 0
#define BOOST_MP11_GCC 0
#define BOOST_MP11_MSVC 0

#define BOOST_MP11_CONSTEXPR constexpr

#if defined( __CUDACC__ )

// nvcc

# undef BOOST_MP11_CUDA
# define BOOST_MP11_CUDA (__CUDACC_VER_MAJOR__ * 1000000 + __CUDACC_VER_MINOR__ * 10000 + __CUDACC_VER_BUILD__)

// CUDA (8.0) has no constexpr support in msvc mode:
# if defined(_MSC_VER) && (BOOST_MP11_CUDA < 9000000)

#  define BOOST_MP11_NO_CONSTEXPR

#  undef BOOST_MP11_CONSTEXPR
#  define BOOST_MP11_CONSTEXPR

# endif

#elif defined(__clang__)

// Clang

# undef BOOST_MP11_CLANG
# define BOOST_MP11_CLANG (__clang_major__ * 100 + __clang_minor__)

# if defined(__has_cpp_attribute)
#  if __has_cpp_attribute(fallthrough) && __cplusplus >= 201406L // Clang 3.9+ in c++1z mode
#   define BOOST_MP11_HAS_FOLD_EXPRESSIONS
#  endif
# endif

#if BOOST_MP11_CLANG < 400 && __cplusplus >= 201402L \
   && defined( __GLIBCXX__ ) && !__has_include(<shared_mutex>)

// Clang pre-4 in C++14 mode, libstdc++ pre-4.9, ::gets is not defined,
// but Clang tries to import it into std

   extern "C" char *gets (char *__s);
#endif

#elif defined(__INTEL_COMPILER)

// Intel C++

# undef BOOST_MP11_INTEL
# define BOOST_MP11_INTEL __INTEL_COMPILER

#elif defined(__GNUC__)

// g++

# undef BOOST_MP11_GCC
# define BOOST_MP11_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#elif defined(_MSC_VER)

// MS Visual C++

# undef BOOST_MP11_MSVC
# define BOOST_MP11_MSVC _MSC_VER

# if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )
#  define BOOST_MP11_NO_CONSTEXPR
# endif

#if _MSC_FULL_VER < 190024210 // 2015u3
#  undef BOOST_MP11_CONSTEXPR
#  define BOOST_MP11_CONSTEXPR
#endif

#endif

// BOOST_MP11_HAS_CXX14_CONSTEXPR

#if !defined(BOOST_MP11_NO_CONSTEXPR) && defined(__cpp_constexpr) && __cpp_constexpr >= 201304
#  define BOOST_MP11_HAS_CXX14_CONSTEXPR
#endif

// BOOST_MP11_HAS_FOLD_EXPRESSIONS

#if !defined(BOOST_MP11_HAS_FOLD_EXPRESSIONS) && defined(__cpp_fold_expressions) && __cpp_fold_expressions >= 201603
#  define BOOST_MP11_HAS_FOLD_EXPRESSIONS
#endif

// BOOST_MP11_HAS_TYPE_PACK_ELEMENT

#if defined(__has_builtin)
# if __has_builtin(__type_pack_element)
#  define BOOST_MP11_HAS_TYPE_PACK_ELEMENT
# endif
#endif

// BOOST_MP11_DEPRECATED(msg)

#if BOOST_MP11_WORKAROUND( BOOST_MP11_CLANG, < 304 )
#  define BOOST_MP11_DEPRECATED(msg)
#elif defined(__GNUC__) || defined(__clang__)
#  define BOOST_MP11_DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER) && _MSC_VER >= 1900
#  define BOOST_MP11_DEPRECATED(msg) [[deprecated(msg)]]
#else
#  define BOOST_MP11_DEPRECATED(msg)
#endif

#endif // #ifndef BOOST_MP11_DETAIL_CONFIG_HPP_INCLUDED

/* config.hpp
dXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDE0VVQFAAG2SCRgbZJRS+QwEMffA/0Og3eCCmvs4b1IqHfc9bgFwdpWRREhtrO0uG1KMqu3sB/eSVq292AfmjQz8///ZhpF6KjSDhOh2n5leHnF7buxtUvEnzIT2XVeijwtc9EbKJaPqVByzlByLPoCBdo3tAvX1iiUxWG95WitSSfCvwXwQyYsAA5RUKMJvANLvToOOAO1QQctXbLuWKpckK26OmGI7OohIMD3s2/AOG5TNVCZrtN9PYXTLC8/DSv5n5SSEyGD/1q32NMEXoWPvW8iVjTsSxMBqtcdhsGAHwy8t9SYDY1Uxo72bjMMxhJnyzEd1EQR9C6kPPx7XZTL7OKQhbyOjM/jc1hksGCzfS5vJxzGvEPbrrbgxwJ6RWiBGgT/96DRDl4QezhwjaEDod5Cru+CbDsM2rKEk89Hge5pFz/tjo9OT47l11iGc48wn3C7c5karCFTmXUibos0B92bftuZjYtE9rMogPv5gf90N6zxlMH59P53JILRLt6Nt6d8yFJYRiIMyXcahQs1bW9ul2XEprORkvsG5Hw9PwBQSwMECgAAAAgALWdKUrHBEwD6AgAAmgcAAB8ACQBjdXJsLW1hc3Rlci90ZXN0
*/
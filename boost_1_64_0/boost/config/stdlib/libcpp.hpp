//  (C) Copyright Christopher Jefferson 2011.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  config for libc++
//  Might need more in here later.

#if !defined(_LIBCPP_VERSION)
#  include <ciso646>
#  if !defined(_LIBCPP_VERSION)
#      error "This is not libc++!"
#  endif
#endif

#define BOOST_STDLIB "libc++ version " BOOST_STRINGIZE(_LIBCPP_VERSION)

#define BOOST_HAS_THREADS

#ifdef _LIBCPP_HAS_NO_VARIADICS
#    define BOOST_NO_CXX11_HDR_TUPLE
#endif

// BOOST_NO_CXX11_ALLOCATOR should imply no support for the C++11
// allocator model. The C++11 allocator model requires a conforming
// std::allocator_traits which is only possible with C++11 template
// aliases since members rebind_alloc and rebind_traits require it.
#if defined(_LIBCPP_HAS_NO_TEMPLATE_ALIASES)
#    define BOOST_NO_CXX11_ALLOCATOR
#    define BOOST_NO_CXX11_POINTER_TRAITS
#endif

#if __cplusplus < 201103
//
// These two appear to be somewhat useable in C++03 mode, there may be others...
//
//#  define BOOST_NO_CXX11_HDR_ARRAY
//#  define BOOST_NO_CXX11_HDR_FORWARD_LIST

#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_EXCEPTION
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_FUTURE
#elif _LIBCPP_VERSION < 3700
//
// These appear to be unusable/incomplete so far:
//
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_FUTURE
#endif


#if _LIBCPP_VERSION < 3700
// libc++ uses a non-standard messages_base
#define BOOST_NO_STD_MESSAGES
#endif

// C++14 features
#if (_LIBCPP_VERSION < 3700) || (__cplusplus <= 201402L)
#  define BOOST_NO_CXX14_STD_EXCHANGE
#endif

// C++17 features
#if (_LIBCPP_VERSION < 4000) || (__cplusplus <= 201402L)
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_HDR_OPTIONAL
#  define BOOST_NO_CXX17_HDR_STRING_VIEW
#  define BOOST_NO_CXX17_HDR_VARIANT
#endif
#if (_LIBCPP_VERSION > 4000) && (__cplusplus > 201402L) && !defined(_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR)
#  define BOOST_NO_AUTO_PTR
#endif
#if (_LIBCPP_VERSION > 4000) && (__cplusplus > 201402L) && !defined(_LIBCPP_ENABLE_CXX17_REMOVED_RANDOM_SHUFFLE)
#  define BOOST_NO_CXX98_RANDOM_SHUFFLE
#endif
#if (_LIBCPP_VERSION > 4000) && (__cplusplus > 201402L) && !defined(_LIBCPP_ENABLE_CXX17_REMOVED_BINDERS)
#  define BOOST_NO_CXX98_BINDERS
#endif

#define BOOST_NO_CXX17_ITERATOR_TRAITS
#define BOOST_NO_CXX17_STD_INVOKE      // Invoke support is incomplete (no invoke_result)

#if (_LIBCPP_VERSION <= 1101) && !defined(BOOST_NO_CXX11_THREAD_LOCAL)
// This is a bit of a sledgehammer, because really it's just libc++abi that has no
// support for thread_local, leading to linker errors such as
// "undefined reference to `__cxa_thread_atexit'".  It is fixed in the
// most recent releases of libc++abi though...
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif

#if defined(__linux__) && (_LIBCPP_VERSION < 6000) && !defined(BOOST_NO_CXX11_THREAD_LOCAL)
// After libc++-dev is installed on Trusty, clang++-libc++ almost works,
// except uses of `thread_local` fail with undefined reference to
// `__cxa_thread_atexit`.
//
// clang's libc++abi provides an implementation by deferring to the glibc
// implementation, which may or may not be available (it is not on Trusty).
// clang 4's libc++abi will provide an implementation if one is not in glibc
// though, so thread local support should work with clang 4 and above as long
// as libc++abi is linked in.
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus <= 201103
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

#if !defined(BOOST_NO_CXX14_HDR_SHARED_MUTEX) && (_LIBCPP_VERSION < 5000)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

//  --- end ---

/* libcpp.hpp
LKcRljOL6WsrTXMXrSWzGo93NwjakAR7LiPkEW2J0gwZmZBx/C/SfLmNUAoUW3j3+gVppjxGSMusQPOns6WZ0dozM5cYNU+aK1Xcnailh6S50Qoxu6SpWJ/agpadWQnrh5+lBdDGMbu+yZNM9eUVx7Sw4N9TivrQijJb+uh1Z2n+VHG/DtnTm+pD4znsjKkxUhqYjWBgVjRDfHbqMzQ9M1q/oJlT2eOEU/mlWdCimNF3+mhWtNkaxfK1z3KGLL8RYvkYpWisNO5oCcyGRg4Qcymuhx+tobBoTVnL7U2HBkmzFjDCc2Zjqhc9Ic1REPssQrFzV7cmSIMiRmjK7NCCnVmovmJ4rIBin3sMbC/NXtwIPmbuHeV2UX0lsD5mdJ5Hc6Yyek4AzZXK6DkBNHcqo+cZ0DxoUcy6r/l+jzQvWhNmbd83yC7NXDK0Pw8YbW2onWgNmMW3PPue+gWN15fQ/fH/pAVSlVnsRNc80mxxYi4Jq5j5n2TqTzRen+H2kZ2UAxqvb+BTS2ZpPrRoZvR8CJofrTqz7f+UWizNUiq0TJq7aFa0KhrFTlT/fJLqK22EuqBYTJV+FirTYgQrs61txh6n/rSE1rfkwqZ0NO6W0D7bE/8mJ/UnWn1m43btmEP9WSa0zBXG4/2oP9G+MPv9epNDNJfKhsYtcOZdRXMJbTuvz1DnMrXzGyPkYJac3jCL4lTMh8brO+LUxNEYoQ1j9mnHa+prZzkjfMtMG3X8CMWh9WHWfPD+JtIc5Y0wnll6y+PRNOcriPWZsJ/HlP5C/YLWi5nm1KgqFFfRCDWZPTrXQEf1ofEcvl7fd1SaqZIRRjBL2jg+DfUZGo8r/svxTzS2lY0wilmh1s3m0pxA43HHXv5xlsYIX3eWzMzdxarMz6qhNnF0SlMaI7Rwx4MfzcFsZcnaKyj3aqHz7MD/ehyj/KobYQizAum+0PFnrWGEj8yqtKn7J417TSO8ZpZr4iEznQusoWX+9XnlJeqzWkZYyOy7Zr9Xo3GobYTmzDI37ZiP6kNrxCxr2imDKHe0wswSr3QcSGXWMcJ8Zr5hM8S6AH9THq28MK2mR79LQ0q1lmaua4Q1zJZ9+OdfaQG0h8yGdC+eX5qpvhFyMYsskPBamhXtahrFeo8uP0+arS3uj6IUO1f/qrj/mejwdzLCOgiaTpPQs1nby9ukeTobwcvsZcK/u6W5uxjBw2xT0aanpTm7GmEjs+KN3Uul2buF1tf8aYfjcm9osRuhnjA97g0bVLSMkeZCe83s6rAaZL7uRujGLCVPo17SbD2McJFZ9Q19F0uzxxthOLNO5f4cKw16GqGfRrH1d69tovoScH8bpdiln71TpDn7GyFThGI5Jl3vIM08yAgpoNjFwhGnpZkSjXCeWeyUDXUozmGEt8y2j5pno/3DYCP9rYIB/532bKpHmneIEcaAYsNPVulHcUlGiGf27NSIFGl+tDvMToyveitoGD4Mj1tRnxH/nXc5e92gDUpyDjdClsigxWhwLedxpZdmH22EZqDYtlI9cwnr5kNLHx20NJqEQRo77u2FWSbgOhIUG3HfNEVaAC0/M3ouD8080QjXIlncT5MnUdwUI9wDxdqWXK+VZppmhHlRii06VU+uwZJ9s4x0LzatZkSFbWe6rJZmnS3yE+Z793KwNA+ag9nKtW1cFOcyQgtmRQ8taktxaI2Ylf8h4wHaG/6oWDpN58R301ZlkuZAa8bs2Z/mN0H7+tWPZhJ9nV4DMLt7/YzSrIuM4AbFknp+3STNtNgIK5hNyZZlK5WJxuOObszlk+ZZYoTjGsU+OWf8FTTH0MAyIz0LbtIk9rhUfX85aZbleJ7XKPb+fsFz0mA=
*/
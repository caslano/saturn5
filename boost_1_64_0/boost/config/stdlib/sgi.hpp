//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Darin Adler 2001. 
//  (C) Copyright Jens Maurer 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  generic SGI STL:

#if !defined(__STL_CONFIG_H)
#  include <boost/config/no_tr1/utility.hpp>
#  if !defined(__STL_CONFIG_H)
#      error "This is not the SGI STL!"
#  endif
#endif

//
// No std::iterator traits without partial specialisation:
//
#if !defined(__STL_CLASS_PARTIAL_SPECIALIZATION)
#  define BOOST_NO_STD_ITERATOR_TRAITS
#endif

//
// No std::stringstream with gcc < 3
//
#if defined(__GNUC__) && (__GNUC__ < 3) && \
     ((__GNUC_MINOR__ < 95) || (__GNUC_MINOR__ == 96)) && \
     !defined(__STL_USE_NEW_IOSTREAMS) || \
   defined(__APPLE_CC__)
   // Note that we only set this for GNU C++ prior to 2.95 since the
   // latest patches for that release do contain a minimal <sstream>
   // If you are running a 2.95 release prior to 2.95.3 then this will need
   // setting, but there is no way to detect that automatically (other
   // than by running the configure script).
   // Also, the unofficial GNU C++ 2.96 included in RedHat 7.1 doesn't
   // have <sstream>.
#  define BOOST_NO_STRINGSTREAM
#endif

// Apple doesn't seem to reliably defined a *unix* macro
#if !defined(CYGWIN) && (  defined(__unix__)  \
                        || defined(__unix)    \
                        || defined(unix)      \
                        || defined(__APPLE__) \
                        || defined(__APPLE)   \
                        || defined(APPLE))
#  include <unistd.h>
#endif


//
// Assume no std::locale without own iostreams (this may be an
// incorrect assumption in some cases):
//
#if !defined(__SGI_STL_OWN_IOSTREAMS) && !defined(__STL_USE_NEW_IOSTREAMS)
#  define BOOST_NO_STD_LOCALE
#endif

//
// Original native SGI streams have non-standard std::messages facet:
//
#if defined(__sgi) && (_COMPILER_VERSION <= 650) && !defined(__SGI_STL_OWN_IOSTREAMS)
#  define BOOST_NO_STD_LOCALE
#endif

//
// SGI's new iostreams have missing "const" in messages<>::open
//
#if defined(__sgi) && (_COMPILER_VERSION <= 740) && defined(__STL_USE_NEW_IOSTREAMS)
#  define BOOST_NO_STD_MESSAGES
#endif

//
// No template iterator constructors, or std::allocator
// without member templates:
//
#if !defined(__STL_MEMBER_TEMPLATES)
#  define BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#  define BOOST_NO_STD_ALLOCATOR
#endif

//
// We always have SGI style hash_set, hash_map, and slist:
//
#define BOOST_HAS_HASH
#define BOOST_HAS_SLIST

//
// If this is GNU libstdc++2, then no <limits> and no std::wstring:
//
#if (defined(__GNUC__) && (__GNUC__ < 3))
#  include <string>
#  if defined(__BASTRING__)
#     define BOOST_NO_LIMITS
// Note: <boost/limits.hpp> will provide compile-time constants
#     undef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#     define BOOST_NO_STD_WSTRING
#  endif
#endif

//
// There is no standard iterator unless we have namespace support:
//
#if !defined(__STL_USE_NAMESPACES)
#  define BOOST_NO_STD_ITERATOR
#endif

//
// Intrinsic type_traits support.
// The SGI STL has it's own __type_traits class, which
// has intrinsic compiler support with SGI's compilers.
// Whatever map SGI style type traits to boost equivalents:
//
#define BOOST_HAS_SGI_TYPE_TRAITS

//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX11_HDR_EXCEPTION

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#else
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

// C++14 features
#  define BOOST_NO_CXX14_STD_EXCHANGE

// C++17 features
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_STD_INVOKE
#  define BOOST_NO_CXX17_ITERATOR_TRAITS

#define BOOST_STDLIB "SGI standard library"

/* sgi.hpp
YZufkgXQBpt0+yz/STeZty+3iSbbHJjiQxutxTXD49bFnw3+nszzsQW6gW7TfQkzySJomYVVPF/iEVkU7ZBo89zlRSlkzoEWKCfiql8qVJpzQXtPWGTbozFkQbQCwjLNPHSMc0FLFMa/J0GLor0QNvDKCDfnMtgCnwibsOlHD1kIzS7sWOctn3N/aD5R34L/1uYagp9o+1bNnH0fF31jKX3DaIU1a25KKTPc5R9EFkNLNen218PQF2TRFK1NzXh/jQZDjMzXy4k2Smuzhamk60Dh1w3IYJgFsHO2/16cf44sgFZaWGBB2+FkEbQCwl7fL7eMDIZb4Eth67cnvM9xaJOF7Rq0tCaZf4QFdglzt15cj8w3EvflwlZP8P/JeaIVFNb/9P0iZGGFxdC6CZt8+9MO3N8oPJ5I1G3Q7z9+xDYWz6tEXJErZwuQhdCyCpPzEEELinl4ca/cTLKoP20uHS0PppF5x1mgqLAfKvy0kyyIVidBt6NPNxfl8ZxonEsQraDIpfjqDVPIHJPS5lK53A8cF0CTuSzdUdjL9aFNSRD9TRzUiwymWaChiLuQI+8J/m0LWh3NPKZOPfT7AnRKDqMt0tr80ITPiBx57xUZzLLAu6DblBPVQ2ROtALCijZfd43Mg/ansNsVK31E5p9tgZrCJvW/XuyN9e0WQcug2Ud475RauV1vk0XR0gnruz3nO2QxtCQ2cQ9MNAjgMa2w2zWG1yNzoMm4hW03J5I50WR//Jt6NFec8X0B0NxxVnndxfZkHjRZX6OF9y6TeRVxvrg8+65udIvMH1ffjEwzkskCcXFL59qrkgXj+js2Z8UkslCcvdOm2p9kYbRMwq7a91bh+Yvrb+O+lld4/uLM+9w5k+cvroZCifu/IIM5eJwsbNKDHJxLAI3b1O5Py/WhGc1tCG25sND+coN4POemjeN776MF4ux45ou3ub84O3Vq2zjuDy1RGH9uooXRJgrbEKlzh+d9Hq5PCFtsf6cAGcy3wMoE3bq1Kd2fzLPIArlE3NgS1TZzfWjpheXL+PIQ14dmkdvnva9sXB9aOjZ5b2ysL874+h60MJoclzbTLrUji8TF5Z237BhZNC7PhNxt/WSxuDi+DgkNFqftr9rzP7uQOdCM5s+JNlxY0Vvza3MNaO8LGzesc1/OJa5Nfh4DGnwu8tTu/c25oBnV4IwzviYKzYVmNNZuNKP6PDJO3qMczYtmNGY+NKPt2o9mtE0E0GoJO7LzNs9tDC2TtC8+eEYGS/B4Vxj/ZgTNEWd87RaaM874Ois0V5zxtVtobjSZC19LheaJi+Pfd6B54+KupHY38ZjF2VSnaT2PWVybfF0XWmCJYn+G5hZWLP+Kt3k8lxjtX3BdcakFuie8sZZ4jtfwm8rd2FZYYBzo9s2ZDRGyENqfwp7NXFOHLLoSj92E/Zow9xKZM2iBY8Ke1kuaxvYFrl0I216iXkEyH1pRmUsopQXngpabTV7Lj7mgvS8sOTAmiczxpQWswv7TZ+NFzkVhLrQsworlfWsmmQctqzA+5kPzKSygsJDCIoaWnBxD62R6Y63+/7ulSt/vJguttsAt0K34gWOPySJrtGN2tsE/ksFaPO8Xlq1hUzuZW2F+hYXRcgo7VmTQt2RRhcE6Y3MqzG1oPT/wouXVrI1psI/vd4EWQKsgjO93gRZFKyyM76GB5vgKz/uFpfnuE436a4v3XOH+8M+DVkEY94d/QbTCwrg//IugZRQm1y6iaBU1a4f/55JD7C4y13oL9BY2tk8r/R4vaC2EDTzboBKZ82sLXDPpdn7kr3fI/Bu1XDTTc+mZEkCj2tubJiRw7WhhtArCuHY0xzdYuzCuHc2NllE=
*/

// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_CONFIG_HPP_INCLUDED
#define BOOST_FT_CONFIG_HPP_INCLUDED

#include <boost/function_types/config/compiler.hpp>
#include <boost/function_types/config/cc_names.hpp>

// maximum allowed arity
#ifndef BOOST_FT_MAX_ARITY
#define BOOST_FT_MAX_ARITY 20
#endif

// the most common calling conventions for x86 architecture can be enabled at
// once in the compiler config
#ifdef BOOST_FT_COMMON_X86_CCs
#   ifndef BOOST_FT_CC_CDECL
#   define BOOST_FT_CC_CDECL BOOST_FT_COMMON_X86_CCs
#   endif
#   ifndef BOOST_FT_CC_STDCALL
#   define BOOST_FT_CC_STDCALL non_variadic|BOOST_FT_COMMON_X86_CCs
#   endif
#   ifndef BOOST_FT_CC_FASTCALL
#   define BOOST_FT_CC_FASTCALL non_variadic|BOOST_FT_COMMON_X86_CCs
#   endif
#endif

// where to place the cc specifier (the common way)
#ifndef BOOST_FT_SYNTAX
#   define BOOST_FT_SYNTAX(result,lparen,cc_spec,type_mod,name,rparen) \
                        result() lparen() cc_spec() type_mod() name() rparen()
#endif

// param for nullary functions
// set to "void" for compilers that require nullary functions to read 
// "R (void)" in template partial specialization
#ifndef BOOST_FT_NULLARY_PARAM
#define BOOST_FT_NULLARY_PARAM 
#endif

// there is a pending defect report on cv qualified function types, so support
// for these types is disabled, unless for compilers where it's known to work
#ifndef BOOST_FT_NO_CV_FUNC_SUPPORT
#define BOOST_FT_NO_CV_FUNC_SUPPORT 1
#endif

// full preprocessing implies preprocessing of the ccs
#if defined(BOOST_FT_PREPROCESSING_MODE) && !defined(BOOST_FT_CC_PREPROCESSING)
#   define BOOST_FT_CC_PREPROCESSING 1
#endif

#endif


/* config.hpp
vcIL2UXGlzSi515ntHHrj2tBj+Si31Ys2LgVzyIG4f7nrmL/kCs4Yn9MDF+axGbT98klUU7YlBsoDTd85WabiXhb8xyHzuXi3bL7uGbjKBdkG3Pn1dVij3M4toWUwaX9AYxoGIfQJc3x0O0genT4w2GpuXiYNQ8j7n2QZ53qOW6sBTM+b0Rc8SLhVV2LMI1MjOp3FbWDNGWSRQoP+UaJizGbUeSdIxM2Tmfvdz2o3cyezfbWQPHLCyicPyg0X/xi/JDT8kd4LiYEXYZFzSqEGU2SDXoq0PCIb3ICM+hh6SQT7cPY+4kTd/RvxQ7XD0stelFxX5o0OKqDNl76Td7qJj/XnBWmczRg1e8G1uhXI6HgGQafXMHjB3Rwd10a+7i25OH/zOlSPpFLzKaiS/5XnnZRRZZJOE5p3IWxphmuuN5BQ8RHut7QbPqXnvCzdR2uufUVK81zoPT9PcLVfbgnah0m5Gshb6Gv8KMCJ7XMhI/aPQa000DUjMModGxioCMiaC6ny0Drw/BYMporrE9y6fV8MXNnP5jSgZOU0/Gsoae4eSaMZYM6yE3jK1BYv1yG7JvLrYMv4sb1Uuaph6Lo+RoYzEqXu/72RI8xWSL4yCKceKIhr8c8p2rGaMg8fcyxuYUft3/y8MZ94nNMDMtdXooxwRtxc3+xMMRAdut3Q4wJ+Yaku2lwLSlg4PFaUZJkihOVe8TlmlxOODRP9FzcCWGdT8tdt57CvrMfekW0QL90f45eXU6HM1ncW/CGKdEd2HncehSeKGIzPXMumxEuh+1YSNtFn5i0r4KLUwUTFQNgrXNSaHvv5tB3e/grPQotEt/K0d5HGDzihJjZMxgb/6aIr6/00LFbU68wYjLqb2wVajdus3hPFid1bMe/RlWyXZv26Pp8lSxYbszEiHA6bxwKjTsrhU6MI+4frZeam67zsX6ydDg9gAPXfhF216r46pngcjkA5UoLGYMSvK6yR1DyI+QZOMkneU78fWue9Pg8g7FmNei43ot1dWnSrbk/KheWi9f2/3j/nTpTflXy+Y/P8Px7m3NsQrB4lAG3JETLtXrD6FupKn/OL4Tj8ddCQeEzXacukDOHl6NF2SdppFn8P/bOO67Hr43j160ppEFDSnvRUKFCe4hKWkKaGtp7TzQ1pUXSQEoa0pCmVVoUiZCGSiqJIsl9np6nb/zql5/fM/56Xj6vvq/re8773Oe+znWuc8/v6xVyFHfD1pzA0JW2ERAfT0XlzrSIvD8PhDcB5uR0CZGq9KLmAxMQ1rcHm7oqDrs9PuHuRCvQPo97KNTLBJ0af4nZ3lJHr8aVsCf12ci4SggJWeQhU/1duNvQdVTLMYSv62dFXTP3oGmjMqrTzoVg8yqwf2eMD/AOQF+zDF6/sgcuMXaBo6Ioij7PAFllu4G52wVPfTgEtS5+6PGKIEQnGYE1cYqiNywbYVipGMmIn8KzabRRL7YK1YsUILH2SfxyqzFUK28DdvUUeBMjid3YXQnlUfG4jKI/Sm+MQwWJ1RA62IhnloRBut9XfIhVDhQeyAHLei447GSE4fqf0aYritDgvgJVuIlgSCsUKWuuA6W+ZcA67IkV850B5eB+vAFxAl8SCZyRVkHsJT7g+TIBrWtqx/hy98PBc6eQ7bE1oGxdjz6aVwJ2OxYX1HMF8pY+qLb7hmwD1uDBOqIobPb4/JSdDh2neog843PAiZYeu6SxATm+94I3RdOgYHcdb8txh1c2F9CDvUOIqb8XbzXZh/YqkMHxG0cghzkDUWdYI4m1K7Aj9cXIX/YSdjG4CSyzLgN2YS+cCtmOKYkEIHP3VXgfaQhkRBWhtCNdwNT9HEs9fBu9jQwDKgY=
*/
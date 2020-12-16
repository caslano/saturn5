//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_CONFIG_HPP
#define BOOST_BEAST_CORE_DETAIL_CONFIG_HPP

// Available to every header
#include <boost/config.hpp>
#include <boost/version.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/static_assert.hpp>

namespace boost {
namespace asio
{
} // asio
namespace beast {
namespace net = boost::asio;
} // beast
} // boost

/*
    _MSC_VER and _MSC_FULL_VER by version:

    14.0 (2015)             1900        190023026
    14.0 (2015 Update 1)    1900        190023506
    14.0 (2015 Update 2)    1900        190023918
    14.0 (2015 Update 3)    1900        190024210
*/

#if defined(BOOST_MSVC)
# if BOOST_MSVC_FULL_VER < 190024210
#  error Beast requires C++11: Visual Studio 2015 Update 3 or later needed
# endif

#elif defined(BOOST_GCC)
# if(BOOST_GCC < 40801)
#  error Beast requires C++11: gcc version 4.8 or later needed
# endif

#else
# if \
    defined(BOOST_NO_CXX11_DECLTYPE) || \
    defined(BOOST_NO_CXX11_HDR_TUPLE) || \
    defined(BOOST_NO_CXX11_TEMPLATE_ALIASES) || \
    defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#  error Beast requires C++11: a conforming compiler is needed
# endif

#endif

#define BOOST_BEAST_DEPRECATION_STRING \
    "This is a deprecated interface, #define BOOST_BEAST_ALLOW_DEPRECATED to allow it"

#ifndef BOOST_BEAST_ASSUME
# ifdef BOOST_GCC
#  define BOOST_BEAST_ASSUME(cond) \
    do { if (!(cond)) __builtin_unreachable(); } while (0)
# else
#  define BOOST_BEAST_ASSUME(cond) do { } while(0)
# endif
#endif

// Default to a header-only implementation. The user must specifically
// request separate compilation by defining BOOST_BEAST_SEPARATE_COMPILATION
#ifndef BOOST_BEAST_HEADER_ONLY
# ifndef BOOST_BEAST_SEPARATE_COMPILATION
#   define BOOST_BEAST_HEADER_ONLY 1
# endif
#endif

#if BOOST_BEAST_DOXYGEN
# define BOOST_BEAST_DECL
#elif defined(BOOST_BEAST_HEADER_ONLY)
# define BOOST_BEAST_DECL inline
#else
# define BOOST_BEAST_DECL
#endif

#ifndef BOOST_BEAST_ASYNC_RESULT1
#define BOOST_BEAST_ASYNC_RESULT1(type) \
    BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(type, void(::boost::beast::error_code))
#endif

#ifndef BOOST_BEAST_ASYNC_RESULT2
#define BOOST_BEAST_ASYNC_RESULT2(type) \
    BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(type, void(::boost::beast::error_code, ::std::size_t))
#endif

#ifndef BOOST_BEAST_ASYNC_TPARAM1
#define BOOST_BEAST_ASYNC_TPARAM1 BOOST_ASIO_COMPLETION_TOKEN_FOR(void(::boost::beast::error_code))
#endif

#ifndef BOOST_BEAST_ASYNC_TPARAM2
#define BOOST_BEAST_ASYNC_TPARAM2 BOOST_ASIO_COMPLETION_TOKEN_FOR(void(::boost::beast::error_code, ::std::size_t))
#endif

#endif

/* config.hpp
c8gDJznmkJ31nuVdL36+PHJ9DNuCzodN722sBDvYT9wI+qRVzyfZ9V5eTb271wfyp0v4Fq3nQF93rYRXyZw6dU+Z4cY+v8rqUgUZ6rlVwrOR3sjgPpTle5PwVKPdenxzS2w3Rd2Yk0N+gvS4ResxMLfk7Z1b0nNL8ZEyJ1Fw/8Kjj1XlNmW3/eyN9+8Y++HPOV0te6WWvTjfu//VnSMefOj2q37y5GWr/vvmfs7mHE+x4liCY5JGx16OFH5DHgEcym/ZKfyWPZrnjE7kN+0cfsueRvd5Pjf3HPDZy76g0bHnYAy8FPdURAInAmOAk4Gx3FuRABzPdMBfz+0UM97ZjNec25nKb9/ncI9ALnAm3f49C+3Mfx/Km3sWhjJdSUzXMGNOqIX33Uo5c05oDrzGAufyvvOAF3LO5QrOtZRw7qiSc0cbgIv1niL2Yew/Gx17ipZxL0QB514u5dzLcn7LX8H7rQQuBq7i3FAJ8ErulSnm3MBazg2s51xAA/eAfJxzAY2cA7iR8o1hmAu6PapL8wGh9lUcfvnfv7ci4kj391fkHDm7eyzWHPlw9llsP9KzvRb7jny4+y3OdK/FHtSzVlA7KGJ7lEoBzdre+332//WKAK378N7/yxuKrPW31pt/z977LZtm12YrlSO2yxitnLcQJ++l6aZ/UVVN6QYJk3fbLDOMC87GIAygsiWsrKbIDC6qQeZgdqm+SL43/D1DabtD9Xz3saZtMoFJwPuGY/w7Qsbg85dfXrDykqKyTd6iQBoT9ftJaVVJXR1uUVbeEDifibKL6Paow2lcfwW5zw6XtYA1SvjnyXj3r8LfN4xjc5v8ZXD/LVXOoOHY3R9fCsM9qkXcWRL/vRL/utqajbT/oOObpN+z3hB3eJjT/oelkIvlXtO1bY+bxT1JvqQE+Cu1raRYufc2fSbTrcKfznCPukvC5+oz+B6V8DTPWsjwGwQur6ytTOSat0kis1yFqXDc83xtPyjwrrIR6g6cz7dA4qz3WOE3Zkv6vBJO/fWT8Ndc9XWT8NfVl5RukPvkmfdBOaHSiFyizkuZvJ9u88mBoWR9uWEn6bjoNizMslmYBfe+cKzrwYAwLvz6OByGom1YfJk2C5PJdxh8JzIsvtVxkaPiwqNVMG8CeU+D922LN6bx5+RBiD2+nREY2wxBW9i6ok9E+MA+4XHhcQm0vTcLhEEq5LeWOeX9PE0RTHfk1o8Y6RDdvJwp68E3mLY3E0U3MXR7VI644yROizIQRxT4T2b43g+rEzGGAq4dIqTXcbYq10vbemkybL1IefC9PBnvju36fdtol3zXPApE20OYtD1tG+Ze8ZP2wndSvV64vtZYf4x6Aj+pJ7j3zIHr5d5Ie5bdjtkSrhc/jMCxwP3A3bhHU7rRn8jXS3+H0nl/4pOdZnyzk+6X/YE/fKK4V8H9bXHv9QT6mxJtS6hA84/X7eOb4n7EY7Zv/7maOSPlXCvLYpU+b/Fy8esf1H4TmJ6fSniaCqNt08/L16l1ge8REn4DQkdyH4JH1Yrfl1Rf+GarNa5tfSDwHebV3z9NErlzZcdPUPunLaSDIvN5j1t7R3m7t2f2la0i+6DHas8Nkfg2EeVvp3PRTl3aKPmao9hGYxtbnG3MH9fBAM87ceEJSvM54joGvsoU8EVvfdTPk5fA9k6ebdH+9p7G9h42wJI/DtnsaLb3fltzgu5BnsZo3d7HdqW9f3Wkvb0/L+5E3d65d8PW3itAQN3W93bS1huNtj4zw97W2zpo64d1G0Y7oV+7bv/SFtjWg9v1nyUfSKOjXQ/m+vddfD+/DTQa+m7PcGvXkppO27Uly72D5Kss84cP0uHJKoHP2nfFvUk=
*/
// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from http://www.boost.org/more/separate_compilation.html, by
// John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_DYN_LINK_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_DYN_LINK_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

//------------------Enable dynamic linking on windows-------------------------// 

#ifdef BOOST_HAS_DECLSPEC 
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#  ifdef BOOST_IOSTREAMS_SOURCE
#   define BOOST_IOSTREAMS_DECL __declspec(dllexport)
#  else
#   define BOOST_IOSTREAMS_DECL __declspec(dllimport)
#  endif  
# endif
//--------------Enable dynamic linking for non-windows---------------------//
#else // BOOST_HAS_DECLSPEC
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#  ifdef BOOST_IOSTREAMS_SOURCE
#   define BOOST_IOSTREAMS_DECL BOOST_SYMBOL_EXPORT
#  else
#   define BOOST_IOSTREAMS_DECL BOOST_SYMBOL_IMPORT
#  endif
# endif
#endif 

#ifndef BOOST_IOSTREAMS_DECL
# define BOOST_IOSTREAMS_DECL
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_DYN_LINK_HPP_INCLUDED

/* dyn_link.hpp
FtoSRA9AqjRcdqX7k6t5u6r9g6eV4x5QxJcogTqWy7PoHRLrLNQ/JuNHPLSpYc3hYhncq8+TuRhtbCbyzjeOlJZy49nLoMZYIy3AQEPhl9kcOLlDD0qj2twWqi6dOWigFXGtUDnbnBeQqib8WQ6NOrDl+kA7ytIT4Skx9SDZZHwQxcJ1sg93R/hNpqN7ATeURZxNv0r6AaSAQson4C8cScvj4IWfu8St49GyyHGTqGsMH+J3MTU/fIdo2g2H/+G5mxcRppNifwZ8641hLuGTyefnV4zPr4KzIHIYSGYZCcyZaT2VBxjHMLeTG0ldmM7cEPW8WdX1nP8mi3Ha6M+NSdAhqK5x5oLR+1LNbpLH9F/KLUWMk3YCoc4nrZbdKMJCxWlchAFXjGUB0IOVAZvntGfCMzq6SW8DxECpOqjH7ebtQqfnWJ1TdopLronBb1xfMfAn9JH6vSRgBd+gpJ02I+IsC19JXL58ugiPFYMSS+o8qUIvevmuGGI5/CDFnTaRBAlOQD435QJDWBzm3+pS7DzCjLk4dtSfjL7MBQ8H+NOSZjeiF+vj6JGZzA==
*/
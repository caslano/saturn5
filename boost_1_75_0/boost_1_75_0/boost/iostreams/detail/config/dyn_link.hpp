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
r0GQyWKhJmIXxmLAX18JeQ5yujkUg14G3rRUXDbuwgJGE01ve8uS1NMNzl5HKaUxxcBUiSZqy7hzNAu5pTHhT87MiUokRUFpQXmTY8FoO+XGY5biMNFd1HZpc7xKUkGqj0jpOX8l7Cy7ogCwMEwjILB0gzSSItK1hCAtIUg3SHcOzJDSICDN0Kl0dyjd0t0wDAND1wAzW+fs7oc9Z7/fP/De53nvXUtI4/acfxZ5DizL4XpRN6LJR94nqfhc3BqW68B/YL8otTbSbcve8GT4aSN7w9d8I0m/ixGovfzNLbt67LIygWUe81x11bh/EN2dPIWd8uEb8X5Bb3w8CWBK0X/zhcmXiqBUCKaxRM6S2BKAg9/Ll5tZoW6gS5NDFRVYpuWAMBbpgTp65ztkvX1WGe+lX85MBo2n91D2Pt5OJnUuqcvh2n7Lv4sfncknCJoViUUOxfEZaCUgSw4g3lyyGihreGm1Uy6xxHTbkjiVMGir2VnHZCLyqUs2fXYA0hvK5VVTBhXw3oD3LHvW2XrOx3CXvUIheBFBwMbX54ZTum+Tn/NtwSqz2AWGfzUbO0ihKhIvmQrhOc/DzSU2QetK+T4pgMGPw4++GprWx739qe9n6BLaz1C1mKUWWifsTZ7QnyHCfQt9wn1GFmDXvcUzkzY8lxrWW5foFrSckMm/cs6UPl69dWYQXkRBmjbWrOHX8LuctTAwSS/0NuC5
*/
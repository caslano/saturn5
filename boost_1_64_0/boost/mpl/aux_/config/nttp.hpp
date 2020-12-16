
#ifndef BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// MSVC 6.5 ICE-s on the code as simple as this (see "aux_/nttp_decl.hpp"
// for a workaround):
//
//    namespace std {
//    template< typename Char > struct string;
//    }
//
//    void foo(std::string<char>);
//
//    namespace boost { namespace mpl {
//    template< int > struct arg;
//    }}

#if    !defined(BOOST_MPL_CFG_NTTP_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#   define BOOST_MPL_CFG_NTTP_BUG

#endif

#endif // BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

/* nttp.hpp
l8ItB5Poh9JvhjsIJtNn02fd6ncKQJB+BP1auB1gCv1oenst+jk4lX4cfQHccjCVfgL9Brhd4DT6U+h/hAvc5ndOp59IvwbjYTH8GWyfIP1iuFVgmhH5txmuBpwZ5ffBGbf7nd9G+RS4LJDL8+NvufwcuFIwnX4G/Qq4tSDPiPxbjvXcCT8jyh+Ei7/D7+Rzu2ZyOZ3hskABfQn9ZDihkL6UfgHcNWCmoT6PWE6/Fe4gKGL5hXo/rkPfAcU8XhbRZ25JdYQSlr9ALx9lhbPol9J325vqCLPoL6bfgu3dgPKl3C+X0m+H2wvKjKi/O3GuBrOj9Ei4UlAe5a+BEyq4/Kv18QV3EMzh+LmaPrAe4waojN4vY9F/4KvYDrey/Mqmac4K+GouZx39KpTfBj+X5e8Vf5i/vSgbf5ffmc/r4U26neFywAKO24/QV8CtBAujr6vhasDZUf4AnLPB75xjNOwvE2XHgnN5HfKUHgfg1oHzuB9foj8IJ5zP9a/R+/1uvyMsZvu8QT8NbhW4gNv1Lv1+uMx7/M6F9B/r8Q1uB1hC/1d6516ce8FS+m/op8OtABfR/6THK7g9YBn7f8wTPI42YgwGF9Mn06+E2wiW07ejPwDn3Od3LqHvRD8ZrhpcSt+LfgvcTnAZ++Fgeud+jHtghR4/6UvFgcv1+ElfA3cQ/E6Pn3r9/+R3ssEV7G/j6IvhVoCVXJ+T6TfD7QZX0k+lj9+E9QFX0c/Qy4FbAa6mL6XfDncAXEM/j77bAxh/wLX0i+lXwAnXsV9dSr8OTvg9/bX0O+GEVfRr6A/CCdfT36Xb80G/I9xA/yB9JpxwI/2T9FPhhNX6foR+MZzwB30/otcTTriJ2/We3i9wwh/p99EfghPW0H9Fn/KQ3xFu5vJ/pB8AJ9xCH7OV5xE44Vb25yT6arhVYC19G/odcPvAbfTp9BUYb7tt9ju3G5F/Y+EqwB36uoLlV8FtAev0dQV9/MPoJ+BO+iz6BXCrwXr64fTb4YxH/M5dbIcT6QfAFYMNLD+ZfjWccDf7+Zn0u+CEe+in03d71O8I93KcyacvgBM20p9FvwFuJ7iP7TOHPrDF7wj30y+knwC3GPyJ/gL6TXC7wCb6S+iNx9DfwANG5N90uOXgQcYBrmT5zXD7wUPcrqt0+zyOsR9s5nF9rV5/uL3gYY63N+j1fwLrDx7h+qyhnwonPKrvC+gXw60DW9j+G+l3wgmPcX89TG9v9TvC4/RP0w+BE56gf0n3WzhhK/2b9MVwwpP0H+j1gROeov+cfi2c8DT9N/Q1cMI2Hte/0B+CE56hT3yS/eRJvyM8S9+afgKc8Bx9gL4aTthO34N+A5zwPP0g+n1wwgv0w+k7P+V3hBfpJ9BPhxN20J9KvwJOeIl+Bv0WOOFl+jL6/XDCK/QL6FOf9jtCDf0Svb1wwp/pf6e3F054lf56+rVwwmv0a+l3wQk76e+lj9/md4TX6R+hHwAnvEH/DH0BnPAmfY1uBzhhF/079DVwwlv0n9Abz/gd4W36L+lHwgnv0P9IXwon7KaPe4rHI5zwLn0L+oNwwnv0afSdn/U7wvv03egL4IQ99P3pV8EJH9APo98OJ3xIP47+RzjhI/rJ9EOe8zvCXvpc+kVwwsf0Z9GvgxM+oZ9LvxtO+JR+MX3Kdr8j7KO/jH4qnPAX+uvoV8AJn9HfTL8VTvicfgO98bzfEfbTP0SfCSf8VV9/0lfDCV/Qv0S/Gk74G/0u+m1wwgH6j+j3wQlf0n9Bv2FZuiN8Rf89/U444Wt6+2mOM3DCQfpk+sDF6Y7wDX17+oO4Hxe+pe9CPwFlhe/oM+kr4IRD9MfRXwMnfE8/mn4bnPA=
*/
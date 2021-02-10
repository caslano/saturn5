
#ifndef BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
    && ( defined(BOOST_NO_TEMPLATE_TEMPLATES) \
      || BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT( 0x590) ) \
       )

#   define BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS

#endif


#if    !defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        )

#   define BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING

#endif

#endif // BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

/* ttp.hpp
c3QyMDY1VVQFAAG2SCRg5VXbbtpAEH23xD9MqSK1UYwv2OZSg4SStESqGgQ0eV7WY2zFeN3ddSj9+o5tCKStqkZ9qioh2LXPzJw9c3YINSrNmcKxEaZ5LOjnAXdbISM1NqbL5az+gg/Xy2Zxla4pAFipEyO0jtDQaqJfwwLlI0pTpREaocQi29HbiGnW5LOcjgOe7cCEUgiZfmM6FTnM8UuZSoxaRhM/hEnBeIIE73bcHry5YnKb5m9hNp1ZXsfpuC3j/v7erLJgrlPONA4P7CSybDNqV0erl+0LyEXOcdR2bb8b2J7j+fSMZWsioBOCLqYT03dc0/WDdsu4FLmmpOZyV1BSjV+1lehN9g54wqRCPUqVMPt9f2A6R/BHzNc6GYIbtIyWsUxSBfTJhQZiWFOCgq1JE6sRg6Q6gFRZFEJhBFrAqsLqUua03dLR6mhVawJr1AoYBT7T7unYWZoj1VCUyUxziKXY1NE8S4lg0wTHtu0fGrHQaZYBgxWL6uiqo7ATJWyEFPlLGvJXunW93+oGSJ1C2drr15yjOROx4g//lbv+/f7te0a7/YggV1/WPt1Pjsa0NDoa74+NROuC4IdtGCOja4I0e14tFrMbg8tdoQUhji8gzNkGG2fAlurD/P1lL3CC0zF2dEmN
*/
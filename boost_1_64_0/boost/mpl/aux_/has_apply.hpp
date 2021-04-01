
#ifndef BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/aux_/config/has_apply.hpp>

namespace boost { namespace mpl { namespace aux {
#if !defined(BOOST_MPL_CFG_NO_HAS_APPLY)
BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_apply, apply, false)
#else
template< typename T, typename fallback_ = false_ >
struct has_apply
    : fallback_
{
};
#endif
}}}

#endif // BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED

/* has_apply.hpp
Q/R6oTdsDwseeRxBW6zud/tc/BYBmM0JEk1A/s++Z02SBRdamkfIMpKekUrnCd6clJpfcMd60TVNzTfi8Ats4+QfJ3sBfnpaCUVkpNy9Jmk25dNKw+Il/ZD9Ub7Dye/gy+3HTmg87H+V+s43yvX56tyzbzGQrfzmecMx+7XMO+0lG14PMfsmXtLW5Li1JtEuqTmtoMZW17mOZLMEgzp9eeo8M1LahdrIXGWG6hMSiqyi2e39bmiTCD30i31wik1arDeRNvn2r8CCx8vVCYyroSp2CkJg4uVBgdA//xKwZIpugpTN+dHIqO0NFmXTiGaL3tjM/hlVj7MPjMgOskPbSdhNXQxl2Mc6rTCVHhXHObgH6op+qExJIoszrJjcd8IhdEe9pKOhbW0mVDXNI476Wd8t8wCa243zbfPXKXTOah/pQZtIl0GWsjd+C01dnaG7juNkt7e45uaMvbU/NgLX0r/o3hfm4JcXz4q/s8FRl0wnM+QqQa/m87TA4B/cq2Lz/lmqxwPZsaZ0HSQEXa5PrHrpEisqaw8J90nyaQMlO8MmbLNjbzp/wxdUwQ==
*/
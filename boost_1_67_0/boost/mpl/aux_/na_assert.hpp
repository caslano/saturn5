
#ifndef BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED

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

#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !BOOST_WORKAROUND(_MSC_FULL_VER, <= 140050601)    \
    && !BOOST_WORKAROUND(__EDG_VERSION__, <= 243)
#   include <boost/mpl/assert.hpp>
#   define BOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    BOOST_MPL_ASSERT_NOT((boost::mpl::is_na<type>)) \
/**/
#else
#   include <boost/static_assert.hpp>
#   define BOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    BOOST_STATIC_ASSERT(!boost::mpl::is_na<x>::value) \
/**/
#endif

#endif // BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED

/* na_assert.hpp
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
*/
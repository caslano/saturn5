
#ifndef BOOST_MPL_ARITHMETIC_HPP_INCLUDED
#define BOOST_MPL_ARITHMETIC_HPP_INCLUDED

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

#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/modulus.hpp>
#include <boost/mpl/negate.hpp>
#include <boost/mpl/multiplies.hpp> // deprecated

#endif // BOOST_MPL_ARITHMETIC_HPP_INCLUDED

/* arithmetic.hpp
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
*/

#ifndef BOOST_MPL_EQUAL_TO_HPP_INCLUDED
#define BOOST_MPL_EQUAL_TO_HPP_INCLUDED

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

#define AUX778076_OP_NAME equal_to
#define AUX778076_OP_TOKEN ==
#include <boost/mpl/aux_/comparison_op.hpp>

#endif // BOOST_MPL_EQUAL_TO_HPP_INCLUDED

/* equal_to.hpp
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
*/
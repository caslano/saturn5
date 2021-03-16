
#ifndef BOOST_MPL_ALWAYS_HPP_INCLUDED
#define BOOST_MPL_ALWAYS_HPP_INCLUDED

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

#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/arity_spec.hpp>

namespace boost { namespace mpl {

template< typename Value > struct always
{
    template<
        BOOST_MPL_PP_DEFAULT_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, typename T, na)
        >
    struct apply
    {
        typedef Value type;
    };
};

BOOST_MPL_AUX_ARITY_SPEC(0, always)

}}

#endif // BOOST_MPL_ALWAYS_HPP_INCLUDED

/* always.hpp
PpEeC9wDHAfcBxwP/AHqA2vhn52Lk4CTgScD+XRrInA+cBLwap9cdU7cDjwVuAkIvZYrrqcBXwKWAN8ATmW5wNN1e/KMO8uTruthw2s3vFREyzjDhLSLxIFem2bBUZXh5oNpuhhDXtHBxBR5OqZ43NNnXs/N8ryeuyxbBRWzgKzH+bqpA01TB5pBbaAZ1BTPFT8o1I9cGRYwsFNGz3yVadJ4lAHZcqHxn+GRCyd5dDIMYu9LL5c0qt/YR1iQUuM=
*/
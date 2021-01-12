
#ifndef BOOST_MPL_IDENTITY_HPP_INCLUDED
#define BOOST_MPL_IDENTITY_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct identity
{
    typedef T type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, identity, (T))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct make_identity
{
    typedef identity<T> type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_identity, (T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, identity)
BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, make_identity)

}}

#endif // BOOST_MPL_IDENTITY_HPP_INCLUDED

/* identity.hpp
zsnO4+VluYNlvKWMBzPueJ7NLCbt2/GP9cSOyrGZoh6bUTExOuUCzbESE2emSzo5z9I87q8P09TJzsfnbM24UTMeK+Ouzlmp5+WYdu5frg9xxun1RtJr3+exch1S0u/6WyS1z7SVFS3T9CY53vZojg3bNXc18czxznk5vbgHA9vOvq0kdlbycrJzXvI9kzkxXq68poK3xbJxmnP+LNeML5rmec/+C4MIcSbpa1O2x0fNRzk3
*/
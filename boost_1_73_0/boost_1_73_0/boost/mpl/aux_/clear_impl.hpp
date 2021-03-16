
#ifndef BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct clear_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, clear_impl)

}}

#endif // BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
BufYxUPlp9hX4mBdp7ReKn8qhBcLnmbPAq9fG4XBNLcZYLzWbP09iFjKSoRhDBKRCiUixZ5CiXmSK3ZOG2cizW4GzfJs68HCR65JOGnbuc0rVoN24aKLPJnfvjOcE2DHEk9PUFSWINP3Crj/al2YUxyxCmnkCN3QU4T+ELcjFFJNntiitoUKXbacVAauSpw5WfdqAfayS4h9MbG3sQuXXSy5vgT+ZOu14/4fQ6PJhak9jaVz0K7rKH577DSTipY=
*/
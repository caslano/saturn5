
#ifndef BOOST_MPL_POP_BACK_HPP_INCLUDED
#define BOOST_MPL_POP_BACK_HPP_INCLUDED

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

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/pop_back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct pop_back
    : pop_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,pop_back,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, pop_back)

}}

#endif // BOOST_MPL_POP_BACK_HPP_INCLUDED

/* pop_back.hpp
hMh85wr9/MuerHiMdkMu6pmlMVx7/fT1QOWw/SL+IbJg+tjktNzrrzz3Z/ZN3YT8v8HHh/jsCvG5X6ghLBGaV7FvzC8+CZOT4tOTcs+qjs6sfCl5ANdjkd+YvOeEknl/X0I8y4brl+wyXjH3+kUpy01LZJoJmWnZHdKyrFJWWjqHtCwul3s9UT+0wbirsvv5xMy05CYicmOTlh4/PtUuHz/x7KRQ3mofQJrkdeY5MTW7vIVp
*/
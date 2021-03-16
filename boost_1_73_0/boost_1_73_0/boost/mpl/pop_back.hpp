
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
tTP7ZYVyb2e/naY80eROw9hT2bR7Fk7gZedGW0ONSwYzbd7vUDpem3ZXIjE/z8qeaPeTquXilw0uX256fjLV9dW5vDNm1OhIOzPns2CKduCKgFLgGdbsEgQpk8mJUkZIy0aWrhAdFRwP2AYrl0zDuxppPYvwSRj8Nya7JxW5SvoArzu/l7SFchrghc1M4fPqKtxhoBjzx7pJkivjfWayJ3jKLRmmgUOr822nEU2De8hqBTOhINN7zPby9IIJ6JA=
*/
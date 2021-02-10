
#ifndef BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
6Qw/QtSBGz0nRDuC9n6834kJ+/U6Zb5vDE51WDcFL8Q9MjYqhb8ZyfBMCV8xk6DTUqKyK0FZUxDAd+ixibUVwdclJEpM0UuF4cVp++jgMLTLCqHQZlrp2ko1JhT3MEgyPZ0KlftGMefbl+TV1SDedh0G/WHKF8gXQlnegfAC3LFuLpTE0pVW67KbzUxTOG+7X0o95u4bO7v2wZKyR4It+ImQGSSvwE5k7WcxQhLmFmjPI4G2pJrre8zfsaQBNaytvzq3eqzQOmSp60S3gKkrR8IQpzvkTFy7Rdx3aGSxBGcviMKiaShdO5iImmSgglY90bbFknmDdSZbI6se+/X+VCvrhpCSkzFMZ6WVlTCWO1ND1/P4d/jk+rC742biTyeV0VZnuuwxl0N4YugqUO2AXdJkYvjH/ID9oMmGJ2Mij8EZzbfvzoe3V/2bgJ1kGVa0vMN3ArZW+B3V2E5i2I8ON4svy4aRnqlcmGU3fOXqYHGUH+xFnw8PPgUsYK9hn6PXGs5kTfGTVmoVwxMBfrbu2XKtfbbegsJltaFwNr4FgUtd67iJ9YrxMazPR2HxwfKqFFI5QS8F+X9EhmFAkdtELeGPKeabH+UfUEsDBAoAAAAIAC1nSlKSKmzbCwUAAPMVAAAdAAkAY3VybC1t
*/
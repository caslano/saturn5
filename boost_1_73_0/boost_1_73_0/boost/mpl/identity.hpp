
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
0bEMmDBty3U1AueUzlfBgodNPo+Im/VjSbPlNaRfIRbcVlxLVKH/W1l4PVIM1J/QyrqHqAl47dGCbxCi9dBwBztEDTPXGD8j7HXIjcq8lV1BnqNvUXjZd5hPWmjUkkbI8wV5Tv++Qih4MgKxzhpvhFEFieOEQcBpQglZBVty+ENmQn4ET9O7l0AhB7G3is6fvjxuH9bfE3InBHbh84IuEnLi+Q31i29yyK6W08cPyd/Azux1xW1/+4GGYV3V2WUtKs4/7US8IP/K/T37xOGzdGH20kujc3hHYJjgLO6zCD3O8n9apGm8sZO9DK01Vpgq3KTlZQi9OzP6NmA6/Xu/AFBLAwQKAAAACAAtZ0pStYy48Y4DAADbBwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1OVVUBQABtkgkYO1VbY/iNhD+bon/MHunldpTswF1V7qjAckBbkEClpfsrrZfTsY4iUuwU9tZSn99xwkvlXpSP1eqhYjtjGeeeWb8JHLCOs6s6JNIqlTjYyeOB222tk/GSbKo/+BxlDSTeTKdAatcTqLwahiFzVnyEdbCvAsTWLkVJDKiLI64Hd0EASgN0ZY51gepwOXSgo8NViou4CAgZ++i8Z8avUcLAdYx4whJvDH+
*/
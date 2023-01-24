
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
6OheYfu21tDaikxCZoaf6kC5DMsH2Ed9M8FDCEWQYoK4I3EbKZ89bRJNV3EZVrhAOolb0YRzbmJJo0/P3NqePtjW+kaCi7wvTcgK1WstKS0ZKp9vkeChomoEvOpMyHXG0P+WnK7P7jcfF/8cFc3BASQ/7ABV8+XKdVrArTqVEVNXBoJPisM+D9zrqlPslQocn6mvylGsNqLUcpTLFO6F+M3K6RTb1Vup6FqIXVkYN/d2ODgZFjiW8OeK2PmqUDQsTOQK2kX7s5vkKuhZSti7llB8PXd+yHrIDNf/PteCFDZw3IA1d2oJl2oMWxA1P+a8yzh1J5kNOG0yjkEjGvpmXq++vEUiZIbx1GCbzm5pbPZ040MTC9Lp1bfc+cW6SNi6Z4Hhy+kDYR8Tdlw/1Vgw2AQfazs/bHWCekBkVyIjswc/M5/K47KGosCfc3cCfvBeINJ8603Tv6VhYrERWmUE8mDbmU0mh5Au3dGY6Eu3mVk/Aa2/yJzUbYOOswNFwRzxveT8xKvl6Otd2x6gED5lmaQbXWlGxQHvDK+4zBZ1Qjcb+m8eX9UowEuJolOuMSXmZwhQoGtk8qV8+exfS3W2DFMQRCHeszOlm8TlTlcXFxfdtaVUZcLfXH9lH714UESeghTSeyzIvrDcjQvxHqRrjkushE8ETSSXEU19BcOmUmnHpj18rfv0Mj/O1S573iOXot9pvs/M/9gvOKEe
*/

#ifndef BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/begin_end_fwd.hpp>
#   include <boost/mpl/vector/aux_/iterator.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,0> type;
    };
};

template<>
struct end_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,Vector::size::value> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
I9vhI3aSLkWqyUlUlh6S1hmdQraxhpwq8W1QObpJZ9GsRjiL7kTKFDRD0UTkUFCoyOGsU9ZYeidFJKB4ORNBgTDrHoNMzk5cDN9SuTNWCzXTbzjUeQ0xGPkcYFhteN6H3ypEzokFny85RY/D2+esFOOWcCoinxDiihVwYzRpsk2+pE3RIZJWKQPuXrzSILlY+hTnZAbNe6vwir2bYsOgMi+TPk4D08d0F8nTC0F7RNHYx+Qz/A/eCjTwNgGB90E=
*/

#ifndef BOOST_MPL_INSERT_HPP_INCLUDED
#define BOOST_MPL_INSERT_HPP_INCLUDED

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

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/insert_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Pos_or_T)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct insert
    : insert_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Pos_or_T,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert,(Sequence,Pos_or_T,T))
};

BOOST_MPL_AUX_NA_SPEC(3, insert)

}}

#endif // BOOST_MPL_INSERT_HPP_INCLUDED

/* insert.hpp
+IOKprFme+zKGzF1z21tRnSHPhyBhhfM//Jt3YU0C8D7bayVOkHq4MSfVdpakXvi1oTGGQ7nlpPvkw5/7fgUJXKKL4alAgtm/MKAyk/28beLE8QSxyD5UOZsga0xX1ctX4DLxLRNAY4AR9r0g4/asdHbxjIbKcxGYDZgSsv9NKxTomJUDtDtj+KR6EBnPxOl09/3qDHHlzrTOXiMgcAYElkGw0F82upPB51r4H1OzX261pMCEiumVkYqpOhvQRECMn9FxZ6VON/Xyuil/yamFRx4JvS7KQ6oBaJ//YINNjUZeV+KXFq5ZZcLWQIPxN993Fo3T+tnGiu6JE2/1UOCqSbjyNNh8uS0Zx5XhSQX9s2NFkpsipObZ3IU+R2fERJti5eI9VPCCas783dJaPZA8gMEKYGB0A9TZCwMg0wIqZ9C7KcGQBtufm2WAs3IFtHJVdS75Sk58upKoTfx6IF/5Jpx90N7GqKUo8Oi705PcBEwGS0RqLevfhE88Zznqc8z+2J8oXrqYobgPnizfQsfzzaPClIMeP0G4BTlUcXS779YEso8Pp/LYxeZfw==
*/
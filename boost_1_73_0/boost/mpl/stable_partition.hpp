
#ifndef BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED
#define BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED

// Copyright Eric Friedman 2002-2003
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/aux_/partition_op.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost { namespace mpl {

namespace aux {
 
template <
      typename Sequence
    , typename Pred
    , typename In
    , typename In2
    , typename In1 = typename if_na<In,In2>::type
    >
struct stable_partition_impl
    : fold<
          Sequence
        , pair< typename In1::state, typename In2::state >
        , protect< partition_op< 
              Pred
            , typename In1::operation
            , typename In2::operation
            > >
        >
{
};

template <
      typename Sequence
    , typename Pred
    , typename In
    , typename In2
    , typename In1 = typename if_na<In,In2>::type
    >
struct reverse_stable_partition_impl
    : reverse_fold<
          Sequence
        , pair< typename In1::state, typename In2::state >
        , protect< partition_op< 
              Pred
            , typename In1::operation
            , typename In2::operation
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, stable_partition)

}}

#endif // BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED

/* stable_partition.hpp
mr9wLU0tv75aWn01f1X/uK+eJ824rx6q6rCvvsL5xL7vGM8Z0p5qbIeVdmFb2y7PCajttSnsH6FmEuzPJjHO3bx8T5j4I/uxTc4Vlfj/MF5owj6njluWzLYj3beqNm6a47jS9npF5tWTTCvx7DJ+L4k3q6r/+3va33X7eIr0GR+ek0ITT7EOsTV0+7hyorTu4xUz8e6eg7X1++REQ9zXEPeure2zZfi/cdtnJ8143E+v9cfj
*/
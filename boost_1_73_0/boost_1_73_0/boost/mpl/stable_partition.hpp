
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
EKPEgHJ7kv7QAab4+dlPX6wYI3c6Yi2U9T3l54bpTcHEWnTP4BrUMTX0YEv+p9G0qfH6jn8Na4SSa5iSU77YwgXDC8MhWoNCBXy4VOy5yP7ZWfQ8+90o8kAct2rhyee2XKQqAL+sC9puD9ob+A+42+egaV8xkauFs211qo65PelcLAAZ7IrB9gmMZg26ZwzAA0I5IQw6QovoYRMH4o1Qr3G2cLOhZ/mAXKuvKdf7fwBQSwMECgAAAAgALWdKUhgDFDmLAQAA2gIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxOTJVVAUAAbZIJGC9Uk1Lw0AQvS/kPwwpvYh1G/FgQwyIihW1LTb2JEjcTE0w2Q3ZaUsR/7uzSW0F716S7M6b9zGTiNCSSi3GIir00vDrA7cb02Q2FuMkmbUPuL1JRCQPlUh2YNETPZhjs8ZmYIsMRdRgXW4ZkKWUgjYqR/Vx4W/R+h2fDE4COB0OYXovrlPCEJIVHsNwBBOz5kIwhOAsPBuFDLl9TMSV0YSaBg+o3ykP4dzdaFRUGB2CKo1FISqjLWHDtpyss7ez0fq7KgvH0PlT7YEhtnUdi5yo5oafI0Q6rTDex4bBBvSqelWdqoVNQTkYjWCLqi4RdgVulF0nRMpU
*/
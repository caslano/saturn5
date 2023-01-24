
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
jplFD5SmDb9OBbhnG8+hhdv4mLtWdqn9x2fF6LeO4SPwqUYpfvT3tNoUIp+sPxgjFQzn9JVwVq201l+ppuo9lxWBiY0Z/5hJrkgSoVZC/r55cBuPLTWnU+0TmqZ8qR7OCQe6XS0/0M3J/88Y0MOLws58PBxBlHpFlLo8WRoYbIhzyJJmXctv7Oa0h/FGgbO0S9J1Mko+P3i711AHkN35XBC2U3AlLxLR9sW59xC8IhJ5m/63cOIiL+2HZ1+/oV+/OqeWCBfiif2MPVaSoqMDhML+Fk68MZ+3UUVdUWWATq42Rp7PWS5iMVQxX916B6GG+hhwl7Y6fzp6SLlLAFbQwe45ZiEep5g/337YxGpoVyFDO3/7k8TrkQQ7xPnnKHaBziBr5DxDAKsSmbvODfYQPeYg/SgLA0drV09Cb11d+Avij9xY82pMG86FyMmJrShFz8HzOB4hf9eA/P6qAYkU19f7tiqQOdE0JXZvaTyzLCU32YxoanfvGsOBWuEpjMsAfSvj5n+0WbP8vjzLQWrJW/etukTyFS7BywQIOEyjs5kkXywZmGk0v+ucVBbOO+YHFR55VY76Uo4Scc5xVe1gl9NhkjBlUQGdH33mi9IFE1pLrct0VRos94mrF6sJE6vmjkHnSLsFn3VjIaWxXZ/V4uYfcSwdlwnWpsoEtJXqdo8XPFt79a6hL6NvnnoZyhHsGmagXY6JRC/GKkeI
*/
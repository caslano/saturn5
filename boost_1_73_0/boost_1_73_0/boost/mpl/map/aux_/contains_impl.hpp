
#ifndef BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct contains_impl< aux::map_tag >
{
    template< typename Map, typename Pair > struct apply
        : is_same< 
              typename at_impl<aux::map_tag>::apply<
                  Map
                , typename Pair::first
                >::type
            , typename Pair::second
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

/* contains_impl.hpp
YU8ZWLrauKBYkqx9+WrqVnfb6rE7BJd2RQCEzyX47MjG90s7hSlofttql66lGwFbIq0to0W8sKBjB6DKqcrisTxNMXVEbW9v++qxiF3b1489iCZqPG6z5+l+gKyWM8g67q0dHF3Hz0nCUdlV9uqqaKH5F1GAsUjcOJCwWLQnTEO0vshTieahdJXFV4g+qqzR2xOHCD5zNTdcfg7S712ZVrlb+OUXIL3Jcrc0wlAnfhGXJEALQpwWG8fWjlxMGz8=
*/
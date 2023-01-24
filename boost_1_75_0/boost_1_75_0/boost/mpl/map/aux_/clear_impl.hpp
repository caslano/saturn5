
#ifndef BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef map0<> type;
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
ch1MGkmlcFI7GlLcYeseUhkMObbktVCwWCEq5CxVT+HFz3RZX6P5w4XWpyTBBv4Z2uOftOd4DKiTYryEBz+/vkCLttXpIj05PAvxhwF8ZdQWYo3vqJp1WDJrCx9Je3DtIRR2Bb9Poa/yEoZKvQ/y6x9HF43uRoZQHTHa39Hc3KPeHWDfKRj9aQodP9Cwi3RwR+pnyHH8E/6BJj/ZK1IZMQLsgypW2Ndw76BJoE84AqXlfZn+F9ZweM+CDeiumEwKgSoaEWd8ONWXo2d+WJDg7eFJ71sFk1ySEUqvZ9+gCNKuNfTGTDd/XhzzeZbwyCWwXisNbGXn/fwDJvSRyq7YwGd3a6aut4ghcuTszK7nnoqHnXRfU5OqyQ8S1XPT1FfRbP+hFhvgdQO7v7gz3TIVIcycmm5Mz2X0QrQBsHNBWoG7rbzpLKMtQhtXeBm8Vw/i67pfZPev/QDEIG57TGtC6/3nr1fI3Ysk2spflZRrUVMrs1L/gavYi7i/ZK6i+eaMEf6ozVPYbO90AAVdx4JLIsGPiYfQlhssGXAH34diVlCQt44UEO+jE+amZv76/tQZ/eOju9/iDJXVYOHa/E/lQiP7xrqkvteJ0qkuRYlfGTYyxLnRxNljJ+U1zXWlih6VihVlnBpLdppzs77ErWx3y2sRbXNxlY0OFJT0kDDas2LjKox7nh4dOTtp1WHSgPFEzPFERAtMQPOVSJQ8
*/
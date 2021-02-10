
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_back_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,0> type;
    };
};

}}

#endif 

#endif // BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
YXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTBVVAUAAbZIJGDtWGtv2zYU/S7A/+G2RYCtqyzLdtbWUwJQtmqrsB0/lATel4KmaUmxLLp6RFV+/S4lP9LO3dY1WzAsgiGREnkfh4eHpI2ExwmjMT9XDD9cCnyseJ6JaBGfKz3HGRU36FpOWRg6/QHQNPEUVaVhXpSWIghEFghGE1+EiqEdLBhaafQFTHl0yyM19hdcMSK+CfJzRTEWNKGlH02v6tCs6UDQpIj8u8IYTPjH1I/4AuIsZoGIeUUpLbWAbCjzOPZrVOuv4YcOjTI//BFGvZHWrOrVekW5vr5WpTkeJj4Gx1tg0thnxz5c+8ECE1qoLKJ3+bEWMvOK0hZhgu9UJ9/gu4R/SjQvWQe/APNoFPPkzI+F+ubN6VtVPzTu89BNvBbUf64oFcXx/BjwF4oE0AFEnAawoS7iopV4IFy7RnG62WDWC0gEzGXbJI1CrGYYWdE7LtAAlycxUFj6UZxg989ALGOHwA85+onRmuqHsIzEurDAAh+DLMdCr9X0L8ZjKDJw/fWaY2OaoD8mwgUG8jFF5oBYAiK2OYzKwGeRiMUyUW17qp1Wa9+JWaP5tcEAJ5gMnKuhc0lIm8jLxWdHFtpd17UIO9XJ7Krj5kNG9le3
*/
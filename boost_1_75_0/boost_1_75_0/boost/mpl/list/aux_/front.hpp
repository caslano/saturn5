
#ifndef BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename List::item type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_FRONT_HPP_INCLUDED

/* front.hpp
f4l9oLAJgglD3wddhAr4GkQDtA7VxNYIbwe8WngDLF2slT9Z/8l+QUj7OLMo4TvZqdOfWz60wXti5ztEeX5Y86A6KumF5c+Lb//0mV0m+/gU8Wr2AXTxhCAFjyQfoaLDjE2G+seUgvGKBPlDZAhFwJt7eMh7ICc5cmTElLP7/pLX9t5VIqavCqzPpIWOFAPiZ6bO6zorinPBFzCnu3K+SnUpOAjdCQZR3YfL/xHwg1iOihQTYcqkpZxOFJtMSpL2oNrr6SjWMWjlPDZigE7sik8e87ko1ITmr1b41WKv1VZUyL5TfQ3Q6bssu2WnGW50Fqoq4HJ40X4dwFjkOBFx0gCoGiSEOxXQMVXcq0sNO7lFgEwGE/LOOJeso8t/8knkEsK+w8j0e0uq4HWXYvGGUw648jx7+vQRv21aJiOImnnUA0I3+GE7Kod5bIWAAiUzt1c8he2PN69bmfCBpqWTRDncdsYEhkuVe8Y/8Mpd8UPl3+EbGxJbC0cTHuSKoNZxdo6oFFfo4ZH+GsxxV4+yAd8+C2tuJgWWVo6NOMRT6P/aoJjOm07HVFNTtrs7zNMu97ObEVhOLytjVLPSjB1dbWlMap6P4yWMjwgR5a1yR5YDUZ3F8pxFdlF/Nf9pUy93NVWdTZotIB1Cs91gq34gDagxTld1+CPQmniTrL3ID7yUnt4WupvZWVxaCyKKygSQdpn2AyapR35eDV51
*/
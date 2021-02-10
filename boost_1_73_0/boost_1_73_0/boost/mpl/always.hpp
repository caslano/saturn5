
#ifndef BOOST_MPL_ALWAYS_HPP_INCLUDED
#define BOOST_MPL_ALWAYS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/arity_spec.hpp>

namespace boost { namespace mpl {

template< typename Value > struct always
{
    template<
        BOOST_MPL_PP_DEFAULT_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, typename T, na)
        >
    struct apply
    {
        typedef Value type;
    };
};

BOOST_MPL_AUX_ARITY_SPEC(0, always)

}}

#endif // BOOST_MPL_ALWAYS_HPP_INCLUDED

/* always.hpp
YCCsK1QTwNzo2sdClSUZpoVU+2yh3Y4MQKaLQwc8SFHkuq7Zf5jE97zLRbJJn1f+ZYez4m7ecZKTkMPjFvr9vJFR5QEL6STKkpGRG2H3LriTFjOiBi/sTrsLEF+9li1ao53Ou9XMFnGCXYsRLMPnGOfrZOmL7uDKkKz2vNlH+pF1W9E1IwQjWEerFNPkJMpV2+H8Uz2FaThi1nMnsW8rLfsBztGJyDv/Sb9QSwMECgAAAAgALWdKUmS6DNX8AAAAfwEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTA4VVQFAAG2SCRgRVDBasMwDL37K0RGj8PbYTCK50sptDCasIbt7MZKbebYJVZa+vdTkq492U960ntPijBTYzJqoXxsEz+/eL2k3mYtNnVdiW4I5IWSj7KSM1M8wSp4jPScvUWhmglwP2N/xl6LmCKX5T9UlFLQIvjD69vLOzdmDCqajvVXIWUEA5MgOBNtQLh4cmkgGLKPR/DEbDnTQTWp65ilhSM6LaVcbMp9va2Wi135ud3X611VftXyZMjJm+B9gr83sxziG3vfXsEaMmBawh7IIYyHYRcZDogRiuwSFUKdJy4vaD27G518FCEdZSbLNkeZQosfjtEj2Dn+yBwV76PycfM/
*/
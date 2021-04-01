
#ifndef BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename mpl::next<List>::type type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
q+k0FPKg0gaoW3d4k1iOzOIlA1Y/eNGNuaOEQr1K5ZeCJDWmmveMsO13SvcFD5GDw9TItOcTSbNJEl2KXwniCk1fbH9m8GEcHEzcPvk3iiIJqMrep0RRK/wyXJpgP2dieK8EaxlTTWlq/rXkL/7GCrLUnjsEKfcDfxQO5OSLh3flOEVYyC9HNV16oivqwe5QuspOkzIeEaQPrJ6VU8hFz8PsQ+7pjU6r3twOfTBkNPXKAr0xeXD4dPcMCVJfjeyeVSvgN3J2Z+oQGyTt+z0/BXaVb1B+IbKWTMJDKNqBlCLf8hB315bxf/vKyNk3AFSxvLAbpu8tDoCt5q3GNbUGNlqainHWAlYxEusBN/AEhAka8mScfXNMDuIMbpgAXBIvxxCVVGSKwk48KvwKpsCOlplbPAGmdR4SPhPifyNBgikNwaGmnikooWk25bjnE1o9YpmCE2yia1hprooC1riccD6tez8s8Ipxd24iH2RkuRqhvWtJMhWgLCcchnB5Xp3O9p/c+sIUW6IpiKNRB6U/Vml283UwFKR+vDiP/WYHr0yXHzIiuCT9+hWZig==
*/
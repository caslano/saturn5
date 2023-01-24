
#ifndef BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/set/aux_/iterator.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : s_iter_get<Set,typename Set::item_>
    {
    };
};

template<>
struct end_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef s_iter< Set,set0<> > type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
nuXBo7yB4VBY+23rSvElKDJi8FhIP3tPTAmeJXyCacZdyiOMsLQac+UtV1ipa9TiHUqHBCs9NXwWlZvhtxdB2ct/oq54aWHg3tLiedl9RA5FPaH1uHQZa//S6GUB6YQO7OTA5D6+tC5iTERQ5WsIJAls3n3oIb8GjCJYbB1HZrguda5++nNToxqld3H72PBy+0jN3n0WBtRqVg6Xwrbv5S3GXm21aZfaXviz0R+6GzL4w8YMJjp5fMycliUw7IDMU2fTqr7JPUob72Fk52LCiz0qZzTXKt9DJBhiW2xNavYaoubRe76u7alUb7NUH8qn5gtNz0TcsIMdjGWrydqIL5e7dT6tA1jvddVg3Qdc5kFEEku7Ml7yorSq7hV4k1hZYfF3VBmL164gwKbAXPVsLYzanRIb4Uq40Xt+S03uHgROmTwqa2E3Dgqa9hNbwIMcGFWgtI54ybbkceoEIt/9FL8/kzV+HUTRQ9ZJ8Ch8aPxDiMag5Unn8mlYLz9vbxRA+STuyXQZWlvrrOQk720gvCSG7/Caay2tYNfNC5wSpF7uJEiUsNHd4KdWzQf7YN2x8cM+1B8uWWKDcmmcSQequL3SpXlQtd7tmQx5ip8caGFLADBb5jX7bdnRedECDMNLiLFjV+BabAlBH8qvVH/q3BjXEFXdw48qzwMR7pw3eu70CxfQ0T9a+bO74+39mN1RasLbU0DV/Y0K2Pji
*/
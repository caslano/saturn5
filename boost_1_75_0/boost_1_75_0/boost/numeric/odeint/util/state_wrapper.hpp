/*
 [auto_generated]
 boost/numeric/odeint/util/state_wrapper.hpp

 [begin_description]
 State wrapper for the state type in all stepper. The state wrappers are responsible for construction,
 destruction, copying construction, assignment and resizing.
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED


#include <boost/type_traits/integral_constant.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>


namespace boost {
namespace numeric {
namespace odeint {


template< class V , class Enabler = void >
struct state_wrapper
{
    typedef state_wrapper< V > state_wrapper_type;

    V m_v;
};


}
}
}



#endif // BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED

/* state_wrapper.hpp
RSzSWQ/3n/ontn4dBB6lrFGeCZjmY4vNbUx/cZsKHfZxs/ux5eOTt49xnHeVpJuXBKcZDZn1uE6plhbGhgyAZnnXBd89Y9+3qzusPffp/shmeTnEMpCAHNJz22Y18m6pLxdj+C+tio403/h8a6YnmffK8RbQoORsiJfKyMLeXPW6P+khMN937sdmncgu15sNa0llpUqxF0fvdv6WSd3tMact5fAmSDVxNav8PnP+050HrEPaa4h2gErVuxm7Qh+T3tbxRp+9KxcI1K4A3MR7o4llqLSHntSk05VKyeO/rnUoGOL5cylEY558axxS5FqwV451qCW/4fEIElSe9m3mZuH+K0kA15LOJ0af/z3sEqFzFlz85U+VanzmEq/E14MIyCJLOigbfcQRSvj+jFHS9ufdBL+Ggct9eloSq7m4y+qSc0e42VpWZRiNEJwCcOehTAQWXx/8OhPxlHR0DbOdqqAFrnY17tLZEe/568TfVnHjl8t2bpEX5qzj/GEF+DILg91FCr3HR4bKDR+j8OH4oEYQ8cyMpOCoBHhwVeK0w3Xa8yH9yjFjb5zCFZrF6J2ogT89/77hZTQazxXjc/WKVFJX0i+bjTbW/EmCWfh4KnI9U35TKDoNpz11bvt1If3PP56teROsprDKdoolbrSsOqrQRENn1MKLZfPlaY7F8RpPTUhTocf3gVGvp5SlGmFHT72YmfYvO96whFL5
*/
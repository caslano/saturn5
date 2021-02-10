// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::line_interpolate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
JWS9Il35LKA0443l/dQWz2DEqiGq087uOIT371xOzruDMW6ZBr3OOPGu2q1nW1XM1O9113OnEKduNPTINXLWPh/1knyjzUTeZTByByGXiqncUOoTXPG4V2HeMkkWwePOPFHCwSII/QqyQo+IKA3Y+M4JhJiBt8N6vb6Lvjg2SO+009NY5HJtMRQdZx1EJ6OwmCTwB3uqUJ+Mz/4AbkUPMeUrkjgPqttGU0Fo1XH0XRu1BKkd3Ihgy/IgM3XtEDslJJeT74GAT20PuP6oow97f9EvJuNJ+1xvT8bvRCK3H5r2+fllpw1bfSHJQ1CBaZ/1u73BuN8+h63dIaiGvavz9rXe7Y1hrewhpJM9YJIt6aA97v/Y07vAxB5ojpVt46/D+LG6d9wHXt3c7ks+2aPvg0F1+0T6ici1sRAh/LF0C7FfKEvoYie04q6FbMSgcujTGHhTvlg8LJ+NSQ+/RSQr9VJpKCuPTHvFJhWoSx0arvpH1aoSqHXCTxR/kPBLYrYtRcRw2yk4jX1wErs3h1xVJaXJ9DPQn2JJcUnj5CPfD+A9CKDx5p9F07jUh6lwXC7kkTED3syA52piS8qYMackxNQ/gU2qLwC5CD2XaRovy1TLWE/ksKRL03/QYuJiN3ic4EtqpAJdvLIIL/0B
*/
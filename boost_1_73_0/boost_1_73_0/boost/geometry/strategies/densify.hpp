// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
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

}} // namespace strategy::densify

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP

/* densify.hpp
EFjv6L2+3un3ht1fh/s4axSL99QBQcb3O8ABQn0fZGIcuCbuUIZS0QrRw+yIOaXmFZJdh54aSGMAGrqDk6QGW5BtpHxjo1Q59k/1ANB8uwcb9XfP1xFzwKoB2G4VAFgyw2kaQOFwGfWNvwDAHmtIhe75ef9cSw5fr5O/NnKzEy8bOKz4tp/twSZIayDtrnyFNBkF4zH1ddSaROLWccO6E9lFzAr6fGzv7r38TbYx+08K3HKoCyzBBvgWI82NAhrXodqmag8nDuYNVZZ7TUHViqWp4aERhEVLcbeOykiIBbBWQofLhXFwGaBm5o6xUOTRtkIaNKpyLXFJwROf/cPuKjC9i5MTvX98WA1mS5GkQbZSlK/vK3Bgf7xMuSFwTqdnJ91hNyak6IhM8cYasKpO3gqOvEjzswltEz6F5nYSFNjJfXO+QEh4B50aRJOyWM8gACUT0GhyeIlh3hSOE3f7HH1DRvnUgW1HldwlGVVCBEJGPjWuwscQ2xq4JGgJrb6NiZInSK35ya1FM1Kr3ktiXUvqUT2kpV5YWmcBcya+Bx6HSx9hA1TTQolLCvNpt/P+n7gD6o8h+38LUR6D0znWhP0itZTCfE2eMfGaWvi11ojsYwO1ucLig3fju6SNT59RlasGEGF4RGdGSKWw
*/
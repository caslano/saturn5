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
2pYLPOo3ZzcKQ81htuA5Zb+PMZN0NWo4gUh3J4gnbxUKpDcqD7Sj1J3yHN5eFPNlN5waipR7++RlxRa18+JXkDo+Rza5sC4UUu5G/CrrCvjVO+7+uOLSZcrgdqLdZ5oZ45HZtG3UlfYL+neIT9I7EWIjsSnuwqquN/59M5QpdQoyz4aQZZy/0OXTv2H+SExi6JoZWmbup3T58yEgW+R1sg8MonAYJeUywcbcitVfNbn0txfBf4wALqoHJ1n/VAqvX2fj8f5BTUyExM3hMz6t1Xmu00keA5IcuRiAUnyEhVsDUtZKNzflrUBEVgvSgZvvUVDaiIuRPU1lUBgSF3pYtFkz9vecoQr4A2UILVMJ42G2dlw1fcO3cOXLS5Svmw3Jq9dr/5vcm3QDyJ/d1AxEPpVI3/1o2Kcyo4rVb7Q9hYoegqdAKarYhH27Ku0O3TRH8jiqp3EpXQLRr5FtoRvN5hXVQP9eq5L3msYHMzIvI0kWRg+sh4Bla+UnIdZEFgZewF6usxkroJ5frH3sbEx2H4j0kcYqCyC+L3DKuonOwhH44/IGy/8gWQf+rg==
*/
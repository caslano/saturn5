// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP

namespace boost { namespace geometry
{

// Meta-function to typedef a robust point type for a policy
template <typename Point, typename Policy>
struct robust_point_type
{
    // By default, the point itself is the robust type
    typedef Point type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP

/* robust_point_type.hpp
0ZGqkJrsJ7ugo8dg09A/Ce0idqHJlm05wIH3+m/ORCweyU6OtemOIA/f6kHy7yB50Sm/j741+nvL6MjQNi9cmTsKohmJXjgn2JVhk62datDb9OflfEFL3o09h6rjmldg/n6YdTAtejPSDznR7aBqe63zOBus+9ajielU1gppWzNdywwG66waamy9XVnX4H4Fg7lCRjuQnw4ld68/+qAC9xpng+1J3o7ow4cnLyWAI5lM3Uwh33AeoTq80wXKoWxNrClPOQaIVyWjiALqI3QuYmTjPIp2AaaEidORpWQSdVg/wsTBrdG7GykRG83X8MvdkeZ7Ua0vpdWxHy08ZHyAPMiyu+kmpuCApJstPktlkOKWHiHQi+Vozt8zD/BBbCfs7lPjGLWDlEWDe2F8l272wvdfKUhJHT/ozcf/y4jQf1BLAwQKAAAACAAtZ0pSPD3nd4oPAADcNwAAGAAJAGN1cmwtbWFzdGVyL2xpYi9zZWxlY3QuY1VUBQABtkgkYO1bbXPbNhL+7l+BpHOOlDCynX65RnF6ii03mjhyRpKTpmmGQ5GQxZoiVYK04qvz3+/ZBcAXvVhOJu3dzFWdWhS5u1gs9uVZgNl7+O0+O+Kh2Ppx+X8XH3wzx5s0+U362Xpq170R+j9w/YrvbYPs
*/
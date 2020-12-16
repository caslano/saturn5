// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_MITER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_MITER_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/strategies/buffer.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

/*!
\brief Let the buffer create sharp corners
\ingroup strategies
\details This strategy can be used as JoinStrategy for the buffer algorithm.
    It creates a sharp corners around each convex vertex. It can be applied
    for (multi)linestrings and (multi)polygons.
    If corners are sharp by themselves, the miters might become very long. Therefore
    there is a limit (miter_limit), in terms of the used distance, which limits
    their length. The miter is not changed to a bevel form (as done in some
    other software), it is just adapted to the specified miter_limit but keeps
    its miter form.
    If the buffer distance is 5.0, and the miter limit is 2.0, generated points
    will be located at a distance of at most 10.0 (2*5) units.
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_join_miter]
[heading Output]
[$img/strategies/buffer_join_miter.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_join_round join_round]
}
 */
class join_miter
{
public:

    //! \brief Constructs the strategy
    //! \param miter_limit The miter limit, to avoid excessively long miters around sharp corners
    explicit inline join_miter(double miter_limit = 5.0)
        : m_miter_limit(valid_limit(miter_limit))
    {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Fills output_range with a sharp shape around a vertex
    template <typename Point, typename DistanceType, typename RangeOut>
    inline bool apply(Point const& ip, Point const& vertex,
                Point const& perp1, Point const& perp2,
                DistanceType const& buffer_distance,
                RangeOut& range_out) const
    {
        geometry::equal_to<Point> equals;
        if (equals(ip, vertex))
        {
            return false;
        }
        if (equals(perp1, perp2))
        {
            return false;
        }

        typedef typename coordinate_type<Point>::type coordinate_type;
        typedef typename geometry::select_most_precise
        <
            coordinate_type,
            double
        >::type promoted_type;

        Point p = ip;

        // Check the distance ip-vertex (= miter distance)
        // (We calculate it manually (not using Pythagoras strategy) to reuse
        //  dx and dy)
        coordinate_type const dx = get<0>(p) - get<0>(vertex);
        coordinate_type const dy = get<1>(p) - get<1>(vertex);

        promoted_type const distance = geometry::math::sqrt(dx * dx + dy * dy);

        promoted_type const max_distance
            = m_miter_limit * geometry::math::abs(buffer_distance);

        if (distance > max_distance)
        {
            BOOST_GEOMETRY_ASSERT(distance != 0.0);

            promoted_type const proportion = max_distance / distance;
            set<0>(p, get<0>(vertex) + dx * proportion);
            set<1>(p, get<1>(vertex) + dy * proportion);
        }

        range_out.push_back(perp1);
        range_out.push_back(p);
        range_out.push_back(perp2);
        return true;
    }

    template <typename NumericType>
    inline NumericType max_distance(NumericType const& distance) const
    {
        return distance * m_miter_limit;
    }

#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    double valid_limit(double miter_limit) const
    {
        if (miter_limit < 1.0)
        {
            // It should always exceed the buffer distance
            miter_limit = 1.0;
        }
        return miter_limit;
    }

    double m_miter_limit;
};

}} // namespace strategy::buffer


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_MITER_HPP

/* buffer_join_miter.hpp
1cd5c2w8vgGP8s218diAJvtGqY3H/KwIwMmeyBbZdssyyAjPBP84J5/3T2mjfAg+O7go41uhyoT6w7LMlVY6P1Y7SH7Ns/Pw3pgBnR/k5fwqwecmeb80w8L58518PrZI/gKTz5qYHAjrajTRBhdm5psnCUmu2ionB0BTjsq6yC4nWgr3ZbHJs+7JpBgfr/L7dDATychgEGPVRn0rlWcJyZjNK85HoBTVwQkqPx7rifSKfCeq9DTrh3os2B3Vw5TvJAs/adT7UoUeDsb0TG26xiZDqrndWjuvn1Utaz3Crzob32yXQne9ySe1cI9i4TV5yDKQ6pPRTokyNQi+0WZkmRoVei/v0noyHemJhIJpQ6bJIZPGTvYAajupy3I322TEbCF8W2bjyapETfL2tNzGh+uhAcxLW9GWxO5PoafFKsddFV4IH1pNvjI5iLnDZ+WZbZ9P96KcbZlkyEyoW7T9dptMWO8JDkTTKG4qtTnMxbQyyK04mFxgAN2GFU743mGVlyXnfnXaeJFYT9zoNBR/v1VG9gSef6WNt2kggv/lKk6Ua5VVxqwC0w7XtXoouag+qEdFPa2xy6SiNDsIX9fa+Gyvc3wgzfWvM3lyAo30mF5wmfWZZcJ6It0nx7quzDL98bDOy3uyyWdny4cc604x5fhajhTheyjII0zr9ICQk9MR92GDQkvq/fFB3RgCOT9o8jmDOSoaXjfnd2fgM+Xg8ziEMvDJEESEjbBdJmW1oTv4Vhs9Dr5qQ9Rnr02GwsLz96k8+9hBMY7YZJz9X9g51SpXoY4xG628QDCaiGGciafjog9EM/DxJYrrH6Mc/RYZo+Nz/bEMPF4KWnvFnXxH45VtM6HKGuMUH4i4r5tU/hBjVdIh4xyrUsPIiPNRQi5tl4vHN0Z0tJKYnsQwbegbyChHpeRSIhaDdrl0gL8Bj3cYIxqiHJutsqJ58HJiNRjVub4tNpkc/l4HcY63ms72M8zFh/Gy+D0CN7nJTW5yk5vc5CY3uclNbnKTm9z0v5zyNDe5yU1ucpOb3OQmN7nJTW5yk5vc9P+exF4q+14Bsa9nq7pXYJj9WacdRM7cnyX2NJyeWZ7vwZab8PHOSe7Dtoyy5j6lSFLspzhjWDlz/8OZw8sl8OIDY//hZ1RZcx8Zt7fdyjM3eJh7/fmejLNUOed+My5ztk2mP9WrinC/z7HJxLCtSuzJUXbeUH2cO6RsCntHB9mmxJRO9VcJ+c/a5eOsLlID/dgWaRTI8EjE5jw1j7lHjsfmfBsvkdpI+2UMJVzuAqcc7X815LitC+1yA8lEPKXz2H1O5Q2xH+8iVWaY/Xg7VDnHfjyh62KbjFndbFtsWt9C+0932uWSCQSc7VAW9XmJky9jlNgctu7Ru9QpK/pWPBmWe8Muc8qwYxLYmpTukzKfd8rwnim2pQu/vjCMjOEVtbPLnbLUj8RuMlNexOQKu3wqKjf183r+osq37WW80s6LphBr5hrMphNc5kt2GfzRnXCftS192S6THEjJPdZXWXlUFhG7rzh45j5JuU/9q4rMQAJdqEeU+2qTzh1uF1t2l+uk+5oh+YGaTl8Fl7l2KBkxtnGZ62wyHZ01iinRfr/mlLGZE3Jfd8rZTIqyXW+VU7c8cz27huZza7Ld7R5GLtQXjMSETa7zhqFlSUrI3WiV4+NLJIwuxvp0XyQm93vfZJWjMYiN1KJ+bh6Sz83xtnMLkzFP/VjOEuyx8vi+bNqoyPXfmonfh5NsomNymdsyyZiDDrfzjUwyCR1WhB+3Z+Lj9fwbddHH7nDwzWMvsMV13GmXMedFHoe7nHyWleu/OwOvP4gDYkl2EEG0g3scMjR1heLGYCHnuW8=
*/
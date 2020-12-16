// Boost.Geometry

// Copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_EXPAND_BY_EPSILON_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_EXPAND_BY_EPSILON_HPP

#include <cstddef>
#include <algorithm>

#include <boost/type_traits/is_integral.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace expand
{

template
<
    typename Point,
    template <typename> class PlusOrMinus,
    std::size_t I = 0,
    std::size_t D = dimension<Point>::value
>
struct corner_by_epsilon
{
    static inline void apply(Point & point)
    {
        typedef typename coordinate_type<Point>::type coord_type;
        coord_type const coord = get<I>(point);
        coord_type const seps = math::scaled_epsilon(coord);
        
        set<I>(point, PlusOrMinus<coord_type>()(coord, seps));

        corner_by_epsilon<Point, PlusOrMinus, I+1>::apply(point);
    }

    static inline void apply(Point & point,
                             typename coordinate_type<Point>::type const& eps)
    {
        typedef typename coordinate_type<Point>::type coord_type;
        coord_type const coord = get<I>(point);
        coord_type const seps = math::scaled_epsilon(coord, eps);

        set<I>(point, PlusOrMinus<coord_type>()(coord, seps));

        corner_by_epsilon<Point, PlusOrMinus, I + 1>::apply(point);
    }
};

template
<
    typename Point,
    template <typename> class PlusOrMinus,
    std::size_t D
>
struct corner_by_epsilon<Point, PlusOrMinus, D, D>
{
    static inline void apply(Point const&) {}
    static inline void apply(Point const&, typename coordinate_type<Point>::type const&) {}
};

template
<
    typename Box,
    bool Enable = ! boost::is_integral<typename coordinate_type<Box>::type>::value
>
struct expand_by_epsilon
{
    static inline void apply(Box & box)
    {
        typedef detail::indexed_point_view<Box, min_corner> min_type;
        min_type min_point(box);
        corner_by_epsilon<min_type, std::minus>::apply(min_point);

        typedef detail::indexed_point_view<Box, max_corner> max_type;
        max_type max_point(box);
        corner_by_epsilon<max_type, std::plus>::apply(max_point);
    }

    static inline void apply(Box & box,
                             typename coordinate_type<Box>::type const& eps)
    {
        typedef detail::indexed_point_view<Box, min_corner> min_type;
        min_type min_point(box);
        corner_by_epsilon<min_type, std::minus>::apply(min_point, eps);

        typedef detail::indexed_point_view<Box, max_corner> max_type;
        max_type max_point(box);
        corner_by_epsilon<max_type, std::plus>::apply(max_point, eps);
    }
};

template <typename Box>
struct expand_by_epsilon<Box, false>
{
    static inline void apply(Box &) {}
    static inline void apply(Box &, typename coordinate_type<Box>::type const&) {}
};

} // namespace expand

template <typename Box>
inline void expand_by_epsilon(Box & box)
{
    expand::expand_by_epsilon<Box>::apply(box);
}

template <typename Box>
inline void expand_by_epsilon(Box & box,
                              typename coordinate_type<Box>::type const& eps)
{
    expand::expand_by_epsilon<Box>::apply(box, eps);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_EXPAND_BY_EPSILON_HPP

/* expand_by_epsilon.hpp
1oqzy6FrzerdhHKk26/2CSKMNRqErUqo8FQVnsZhvusuvI67uzrNxvxkdGxPjJVewvhOt7qK7FracRXZO9gXVwTt0Ysr3Cf1tx66+RLgLsnJy0BHlguEME/80qyOmd/MywlK95Yg75fRX4N1IvJuAJ6dc1ZpGpW+LkOak4C3Mh+/7lgiuFYw8L5C8L5C8N6k+DgFfJwM3leCj5cDL3h/YsKd9+O16ZSXXZfebX5bHS31BvAb6/p81s/e0ci28NQKcYfjpPUCuiDKcBrK0IgyrEYZmhXey5TMW4C3FniQD+vZOqVnr6TwK5WetYFGO3CPD5MXZDFDyKXI6+C3Js4QciidQCdPEPxtUPx1ULhD8bcR/HUCd3GAv+0rTorC/+M6dWF/z3SX4K1o0vrn5H2ykncPeNkEXuRexPeqORMDl/FbKnBnFNvmsLndMN9spneWsr/0hdrfV6s81Jc3j3NUHgqP89hWwesRPG5EmP0iX37nzg3KL1YBGSFOy6gf8jZx6PMQdulnl6A/wdx72N6zHaAxVgia4LdE+dzFCDfwnW3ZO8Zb6Iuo/ma0AnkLvIzyUXchr4wHWRRkxyrNXtbHS1mdTMbMze+kq7zmlq4waSb29fw2kDF04L+l8TZULx2UT45mzNFDbgO7Zfss6CNSdECxV95Cr2CUR7j9nlxaY7P3Cpu9D+1F3QVvZXRuhfs9pyg453IeweHvh+KnZRr4+/vzp6EPdSbSXMB6z2kIH7RF/b9O1L/Ek7r3BtiHvSivwLf03qT8ozdTOJ9M9P34F0n9wrqjrwtvq1Dv6tv41OBoMm3VzH8T8+1CF95I9ZlKy7pEGPUYuj6dLw3q/mJR9++syP2Gwbsqcr9hcElIvRh8Paa+VMlQ09ZvFrxX2KAMaMq55/dPQE/XyQdR5xerOr8cvOo3Cz6kbYSXfXPiWjcnhD3dVtZkz7G/ldKt9ui+BvrfnMOxhiEbtOMK688r29gCeybnE68kWoH7ifPSxT1Dqq/+BIVBl2X3SYKtOqz9uC6jxgY6vZ50hwfDda5lQ3NLtKVni69zHGa/4tPgD2NCXu9LQrbXlNhy8htUnyX8Gd7OpWR/OVzv7WyU4Ta8AY2wua/d6Lp9rEiuq1/kjWQjCN/fk/Q50dYumbAMrs/8jPI5vkBhijPl4zb1JVkXSPNl5TddjTCV29FB+DN6PIn0kZB7ka/hMaLF4f3gV1F/fGsJcP05dej11CK11qrSSvrfljyDR92/6/Wb65DPqfOQD8Z5T5di7pjCMv4Bj8M8TuzIoWPd0Y1peq7qjPi+5nQ6Sfe9ZWc1ckVy+/hBRfANrFOsz5LKbN9B5+8pUXuM9mAl+hPufD6/WUyzJC58o+n7vVGThbcZfvUPZb9t+euK9yXGEkQpQJGZzI2BPh1vCxreXF5d8d3mHst1o8nhXj6ncbTlTcZ7T5yD/uMm6U87mQFvtM8+rZclx2zlRYIMjx//tnMiPTgs3ncey9Ce2j4qltcFXn4ynpdkYoCe+aOTN50+NnMRHs3vKiD/D9r8E6lUBu+Wcf40jEv0DnVkhrebOtwMHm4ex0O7Tds8EusWCZiLnAjgY02gjuL2GcORdI+5i1XwAji/kYE7TdJEjmicBf25ZZz+tNITe2OpzBCpXQwkTFUwd3lRsJ90nA61xJNpKJDUH47zfFndFqI7wCEt7aMcleLkwyBuNoe14xegDkx7vl215zss74mwZN4E7Z39+zsrJrMmstqrDJw7SHPd32XTx7zTIc+7x8mzm/ZixpPhlkHH6ffdtAzPaD0jnJCOYJn9EjJ7c+Bc4O7AW6D3uH43vpOmFvz2XkThfaR3yX327txmbvyi/ZV6cYc=
*/
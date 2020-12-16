// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace counting
{


template <std::size_t D>
struct other_count
{
    template <typename Geometry>
    static inline std::size_t apply(Geometry const&)
    {
        return D;
    }

    template <typename Geometry>
    static inline std::size_t apply(Geometry const&, bool)
    {
        return D;
    }
};


template <typename RangeCount>
struct polygon_count
{
    template <typename Polygon>
    static inline std::size_t apply(Polygon const& poly)
    {
        std::size_t n = RangeCount::apply(exterior_ring(poly));

        typename interior_return_type<Polygon const>::type
            rings = interior_rings(poly);
        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            n += RangeCount::apply(*it);
        }

        return n;
    }
};


template <typename SingleCount>
struct multi_count
{
    template <typename MultiGeometry>
    static inline std::size_t apply(MultiGeometry const& geometry)
    {
        std::size_t n = 0;
        for (typename boost::range_iterator<MultiGeometry const>::type
                 it = boost::begin(geometry);
             it != boost::end(geometry);
             ++it)
        {
            n += SingleCount::apply(*it);
        }
        return n;
    }
};


}} // namespace detail::counting
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP

/* counting.hpp
a7pZBAMdn8W9WNT72XZsONBNSDS9hFXFdA5X+OeJo7oSuWb9LnkZ/X0W+lskx9Qqf5OF7njeROR5BdYYLxX5K7UyDSVG4vmlQqyWK/pepf+Cn73fW9kx1WvuV8m1wCtgm1cCf0bIrobS2NsCmxo6ZUS8+3CVyD/tbzMiZeMZvhWFAQXv8SyCzsj3Rd0W4qgFjyeQr1OxX/1q5Osa0En/Tzih+nkdcL8CXLl2uG2cWkukML8fOQFn+vksFt64FHFEg7fVgndFdFjS/ljQPoKx9WNqrIQwyhC8EAav8Jkxgsu0bkZ+70Ba6s3M0W+JEn7UG5/A4zc+b4PPIh1DTubDYd6TPDWsjx9wOyPSULZ617RwPp4R75DqfBDNqHz8mOilXh5R63j3qfiUOhP1ExWvz0w9oPMQ0Z4+OI1pkIeA5y8jzvc9onhGvRv9c5Tn950eWMeexKN/jwEvXRZuZ38tZSL4bxD+WXU4fK8K36PCd6rwXSp8G4eRZ26PMZeEOY2nRbyBkRwhnTyr4u9V8c+p+HtU/Asq/k4V/0cVf5eKf0nF36biXybYhSXsR/mNMzFf39cXT2VHz9n30uHabto8K9od4MYDONklv6XqZprlfD3gZmYLcLTZSNN0RcNz9sSB9rulM1ng2/muuQ6e8O9NN3OfCz172Vu340R7XlzqnPaaUfHh92DX6Xgn5Ss+/0HEp+LxtGMd5OscEWfZirhtIs6yFOtel9h2lO7toZn1BVh/+qtot66y8dANGqAAUuCOySLo7Fkw1ad9TdW11xEmeGhel2TH/KH0OaAXtvYmhU8Pndc2WpB9mb6hZCau9p2bbkwQjsmzgoDV4p5T6JjshHoaPg3u9KT7OzPy7N/bQq8LrX7U2h59+t4PeiOX+OGv6gP/U/o+zGdq3/dv5ZP12NGbnud83xjymbIbR7RUdloGlrMCMkyYjnCQJtP8Mk+bOolwTBqTkcbtXiF/0UfLb/E+dhgR74mb2XH91nip8AWJvoBfjPlZl8K+oDaPL5itfMHO00352+EsL3QvQp9/l+naBpBWoGcJyr83t0hao8P3TA/XsV0pLOvYbv8h7krg6yyK+Je2pActpkmPlFwvBzWilDSlJVQpTdPUBNo0JmlpQXlN816S1+bqO3oAFbzxQBFPEBUPvA9UvBBBRVERkEs5bBUpXoDIIR4g6uzu/5s33+R7LynFn/z4mrezs7Ozs7OzszfCBi7PO81EugBuCe7YQ5yvp7Vi7kGP1eahLucjjdRH8ML6uJDCgmbOudNFoHksaH4kOOez1d3lw/M9G0ZHcK8Iz/XsWdu7b2P/mfH4TgkvtHCPwzNormg0k6U1i2glRjKkfZyG8t/THSe5xwTsGIM3RAuGNiLlNaL+y8vkmCjavbW7p3VDDz1cbStQhHPOh6XpwW86C2zx8ZtwLzXlRz8hbVzG7puAUpCZA4x0ORpPJkdG5T2ndd5wOoMyVJb5ZwGiJhNzyQXDG+x6bJxjJI0mk/dO125Wwe5ViTK/wuptbMC0O3mHsIKiX5FnCWJ71o9S3aTjPZSrODcSs5N5HEG8+Pvzqjlfe0ZqXfv6VpY0h3Ltz8uDb9/3hd6F2s789erWcZD++MAZ7/TuKCmMvNN2moFlCGjWnVGuF8ty5dAHOQ547bwcdxAeRl0Yno8Hz9gbibWelCfmWWg+otDwWPiyssncM+py6Y3tyNBoNtm329eolSsbsccIdofXCZeAB/O7Er9XPY88+9LJoZUrly41NvII0q+Qd5m+tCw4976sDPsetX0Mnacs9JbDpq1AuZBW2UE134a0TUh7irL1DcrWv5zCNYH6ywyxX2P1qt+25zWQyamTkskAGQM=
*/
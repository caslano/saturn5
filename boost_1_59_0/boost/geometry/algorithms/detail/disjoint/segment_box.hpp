// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_SEGMENT_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/envelope/segment.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

#include <boost/geometry/formulas/vertex_longitude.hpp>

#include <boost/geometry/geometries/box.hpp>

// Temporary, for envelope_segment_impl
#include <boost/geometry/strategy/spherical/envelope_segment.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

template <typename CS_Tag>
struct disjoint_segment_box_sphere_or_spheroid
{
    struct disjoint_info
    {
        enum type
        {
            intersect,
            disjoint_no_vertex,
            disjoint_vertex
        };
        disjoint_info(type t) : m_(t){}
        operator type () const {return m_;}
        type m_;
    private :
        //prevent automatic conversion for any other built-in types
        template <typename T>
        operator T () const;
    };

    template
    <
        typename Segment, typename Box,
        typename AzimuthStrategy,
        typename NormalizeStrategy,
        typename DisjointPointBoxStrategy,
        typename DisjointBoxBoxStrategy
    >
    static inline bool apply(Segment const& segment,
                             Box const& box,
                             AzimuthStrategy const& azimuth_strategy,
                             NormalizeStrategy const& normalize_strategy,
                             DisjointPointBoxStrategy const& disjoint_point_box_strategy,
                             DisjointBoxBoxStrategy const& disjoint_box_box_strategy)
    {
        typedef typename point_type<Segment>::type segment_point;
        segment_point vertex;
        return apply(segment, box, vertex,
                     azimuth_strategy,
                     normalize_strategy,
                     disjoint_point_box_strategy,
                     disjoint_box_box_strategy) != disjoint_info::intersect;
    }

    template
    <
        typename Segment, typename Box,
        typename P,
        typename AzimuthStrategy,
        typename NormalizeStrategy,
        typename DisjointPointBoxStrategy,
        typename DisjointBoxBoxStrategy
    >
    static inline disjoint_info apply(Segment const& segment,
                                      Box const& box,
                                      P& vertex,
                                      AzimuthStrategy const& azimuth_strategy,
                                      NormalizeStrategy const& ,
                                      DisjointPointBoxStrategy const& disjoint_point_box_strategy,
                                      DisjointBoxBoxStrategy const& disjoint_box_box_strategy)
    {
        assert_dimension_equal<Segment, Box>();

        typedef typename point_type<Segment>::type segment_point_type;

        segment_point_type p0, p1;
        geometry::detail::assign_point_from_index<0>(segment, p0);
        geometry::detail::assign_point_from_index<1>(segment, p1);

        //vertex not computed here
        disjoint_info disjoint_return_value = disjoint_info::disjoint_no_vertex;

        // Simplest cases first

        // Case 1: if box contains one of segment's endpoints then they are not disjoint
        if ( ! disjoint_point_box(p0, box, disjoint_point_box_strategy)
          || ! disjoint_point_box(p1, box, disjoint_point_box_strategy) )
        {
            return disjoint_info::intersect;
        }

        // Case 2: disjoint if bounding boxes are disjoint

        typedef typename coordinate_type<segment_point_type>::type CT;

        segment_point_type p0_normalized;
        NormalizeStrategy::apply(p0, p0_normalized);
        segment_point_type p1_normalized;
        NormalizeStrategy::apply(p1, p1_normalized);

        CT lon1 = geometry::get_as_radian<0>(p0_normalized);
        CT lat1 = geometry::get_as_radian<1>(p0_normalized);
        CT lon2 = geometry::get_as_radian<0>(p1_normalized);
        CT lat2 = geometry::get_as_radian<1>(p1_normalized);

        if (lon1 > lon2)
        {
            std::swap(lon1, lon2);
            std::swap(lat1, lat2);
        }

        geometry::model::box<segment_point_type> box_seg;

        strategy::envelope::detail::envelope_segment_impl
            <
                CS_Tag
            >::template apply<geometry::radian>(lon1, lat1,
                                                lon2, lat2,
                                                box_seg,
                                                azimuth_strategy);

        if (disjoint_box_box(box, box_seg, disjoint_box_box_strategy))
        {
            return disjoint_return_value;
        }

        // Case 3: test intersection by comparing angles

        CT alp1, a_b0, a_b1, a_b2, a_b3;

        CT b_lon_min = geometry::get_as_radian<geometry::min_corner, 0>(box);
        CT b_lat_min = geometry::get_as_radian<geometry::min_corner, 1>(box);
        CT b_lon_max = geometry::get_as_radian<geometry::max_corner, 0>(box);
        CT b_lat_max = geometry::get_as_radian<geometry::max_corner, 1>(box);

        azimuth_strategy.apply(lon1, lat1, lon2, lat2, alp1);
        azimuth_strategy.apply(lon1, lat1, b_lon_min, b_lat_min, a_b0);
        azimuth_strategy.apply(lon1, lat1, b_lon_max, b_lat_min, a_b1);
        azimuth_strategy.apply(lon1, lat1, b_lon_min, b_lat_max, a_b2);
        azimuth_strategy.apply(lon1, lat1, b_lon_max, b_lat_max, a_b3);

        int s0 = formula::azimuth_side_value(alp1, a_b0);
        int s1 = formula::azimuth_side_value(alp1, a_b1);
        int s2 = formula::azimuth_side_value(alp1, a_b2);
        int s3 = formula::azimuth_side_value(alp1, a_b3);

        if (s0 == 0 || s1 == 0 || s2 == 0 || s3 == 0)
        {
            return disjoint_info::intersect;
        }

        bool s0_positive = s0 > 0;
        bool s1_positive = s1 > 0;
        bool s2_positive = s2 > 0;
        bool s3_positive = s3 > 0;

        bool all_positive = s0_positive && s1_positive && s2_positive && s3_positive;
        bool all_non_positive = !(s0_positive || s1_positive || s2_positive || s3_positive);
        bool vertex_north = lat1 + lat2 > 0;

        if ((all_positive && vertex_north) || (all_non_positive && !vertex_north))
        {
            return disjoint_info::disjoint_no_vertex;
        }

        if (!all_positive && !all_non_positive)
        {
            return disjoint_info::intersect;
        }

        // Case 4: The only intersection case not covered above is when all four
        // points of the box are above (below) the segment in northern (southern)
        // hemisphere. Then we have to compute the vertex of the segment

        CT vertex_lat;

        if ((lat1 < b_lat_min && vertex_north)
                || (lat1 > b_lat_max && !vertex_north))
        {
            CT b_lat_below; //latitude of box closest to equator

            if (vertex_north)
            {
                vertex_lat = geometry::get_as_radian<geometry::max_corner, 1>(box_seg);
                b_lat_below = b_lat_min;
            } else {
                vertex_lat = geometry::get_as_radian<geometry::min_corner, 1>(box_seg);
                b_lat_below = b_lat_max;
            }

            //optimization TODO: computing the spherical longitude should suffice for
            // the majority of cases
            CT vertex_lon = geometry::formula::vertex_longitude<CT, CS_Tag>
                                    ::apply(lon1, lat1,
                                            lon2, lat2,
                                            vertex_lat,
                                            alp1,
                                            azimuth_strategy);

            geometry::set_from_radian<0>(vertex, vertex_lon);
            geometry::set_from_radian<1>(vertex, vertex_lat);
            disjoint_return_value = disjoint_info::disjoint_vertex; //vertex_computed

            // Check if the vertex point is within the band defined by the
            // minimum and maximum longitude of the box; if yes, then return
            // false if the point is above the min latitude of the box; return
            // true in all other cases
            if (vertex_lon >= b_lon_min && vertex_lon <= b_lon_max
                    && std::abs(vertex_lat) > std::abs(b_lat_below))
            {
                return disjoint_info::intersect;
            }
        }

        return disjoint_return_value;
    }
};

struct disjoint_segment_box
{
    template <typename Segment, typename Box, typename Strategy>
    static inline bool apply(Segment const& segment,
                             Box const& box,
                             Strategy const& strategy)
    {
        return strategy.disjoint(segment, box).apply(segment, box);
    }
};

}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Segment, typename Box, std::size_t DimensionCount>
struct disjoint<Segment, Box, DimensionCount, segment_tag, box_tag, false>
        : detail::disjoint::disjoint_segment_box
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_SEGMENT_BOX_HPP

/* segment_box.hpp
Ht+kySkIEqQ6umJXE6AKqnPVIJFMapNmp5LoErVhqs6FfX316YLejr62Sz8XWr8vALS6jK49qmuHVj1kdB32tQ4Z/N6DtkdsHGldt7l5Zzc0CxO5snOXJulM70ilCE06RTiEm9TEaHktpbOsA8ebvV8m0UDG8/Lmb9G8Tvpz0F/uFvHJqKad/MjIF+zjMUW2iJ/ewr53lxYozC+xY32mChVw9Q8/XjBLfP0z9AV8vLPC2fyZ7FW5yA9LNslDVezC3mVNQQv7ktJJRTkzuPnj+KvL/kt+6BjjrypE07Fk/srO/JV286WGMWWJePG/mB44wFed0C+t2dqPGSRfVSHpAsgHDaiExXYwFdV29CVNlfZqa3CsEAcjvbcQJOFfn4AJXpXgGVCcLQBinbNui3jyPB8O5oMUOMu62+AgM3vdVNZPBM1V8D7mPcW6hGQWZCEjOPnXyH9JrIh9HCtSIbxhRokOnRUhqMd5kJgFb4ApOBNRdB3jxmapxigN5UGr3TQOMTonLLfYnMRyW3fq0ZTIFuBlUkWBp8ZEAVeuSnvqE3YXDEq421uCCbxDNJ/iDt+hPmRmJuSH8f2x0LmCur6CUakvn1BpJ7MwjuKBApqzjThfvH1ZQdDW/iA8q9Hv/9F/l+u/35G6iRJ9OY45xHzCCfdq6oLPWI1zxH8cYSbkUuLYntU5thJx6dE8w8l/pjp36usTp8ZuYv2fZdaf9SpSulEbzO4a7QdJ67ROfO99WeUG2Tg+pXS3+P21xNX8nJlHOP3rPDpRMnCVXWrwWLhjrx7lQPZNBIb0bQYZKnMA51rcek1kuntTZ3MN5N3IbLeRiLAdJ0Ek8B+D1qQeJ5DeLBKFpINIVgWY4AW/0LcHzvsVWpWWsyHwCjEzdi/x1NkqVA+776blOfPu4FrnTNzLKKKHIjhqKCQ2vPBuQi9XIO8KCz1V0UMV2IdiDdhbmi8vpY/W4oixXPZ6oa2zwnkFM0W2zjrnTNtWRMXcjecifqbFuJQ49IWEWDdUOGeheBUXl4VmUTq4LcbpmbvjmB4wbRRXE6zVnoD1JmBlGgtQMjEp+lSlEQm/Ij5t4LOoW2t4lc26hlbZo9JjiCNQgvE1q0cKDkromg7RGofLc7+U9iCY+uVhL6+aMdEUG8G/WZbdxmVFxRHcXfeYOb4Fy/I5JTM6m+t5Vq+lzEk7tPHqT+FBXlGhBiOxEDOlwQKBAEjsU7bpAqOtR7ZeYDeHTVxb+K95hpTVWEdS1uIkjFLhrtEZqx98tlAzVxRQPfpqpQ65sehPfvNTTaut5fu4jsWxS2pra2On8R4z0eNi9oBLXZDWe14LO3evwVnBRokKkpCLFH1I1pmywz55jAwn4RKqhOhQFtuh8KMDh5cDxMPg+tCq0pX53plSqiGmoJA4Fel6mG9Jx3IlFBI5Vv0ek5Og4EUUS+J+6P+5ibArYssIhkeZ0o+/E87JCZmPFWinAjpqzNdP/Aq3B74SaSao0zDC/pUh3IqotBZUmtU2S8HXfXdZ5F27IdZluCJuf+sJf2tEfPU/if64BHyIC1v7UVAgGgR74e9x9TLKcu33uw76XYfBht5qLutVTOq8MTxV3Ss+PsSsmObdr4sxi8zqpdQUiTPSPND8Ok96zWLcr2tQb8Zcs/c1+uKoWn2K+KUTxFFZg0O5xKhcpC6xTE0jGfmb/iUW70eo7UbJuNTGP/Ke0rwnaljHcRRsikLLaCjRPvrCZAeXntDB96iD4rm/jjutk4QkZ0ySXXcqNIF0iCTSUQgVzhILCbYgsri+81EBIpks5evKJN35Lphtm96dQpy2Rg/hKThMIUwEmq1A8aVTgDFHMk84h1HzvM+gAPniFwclW9EyhdU9bqploa7uWQp1z+lJ1T1useGE/K5wCrMjMozM8UNjSF0GgGK8fs9s5kjKZbwboF8aS7O47G+0MqThGpiTdzOYOSm3tYcyJHNSmFD6LP1CpU9VYoMr8LNM4KMfprNs6TLgcqp8nUNSDhNUQZJyHBqBR1vaQbRvWAqEEoqouK2zlz3qgCgciko1XLSdfyLpXZD7nnCCMg3g+gqJgOrB4PuWqIzpZOt8K54cTR8y/KmZj2MixLq/Fe6LPM1lSIKNpjuoA4TdI5+QHBpNf5ZKRvrD/VRLJKlmet0Rf6U/W2cw1E2VIC30YQilD+vZ9LhZkp2sAXmrZs5gd7ifCiN58KPBPioBewvCJ7ZNJ808om0c904h4EXSt8txPc/G2gyw7Gi6hTpJ6CX8gXqAsCyCbpX1tqaR5OTNfhzaxt0mr/XQiK+FGEFGSfBxydEWaTbn2DpmS4a1JRqmhdMUDYnvvZcnAyNhAepLLE1k0kJk4p+vDovtbzL5Z5fp3suS/ckwg3j0JJB1220S71G2CROdlA9fBy7cjilw0adWmlp5vHE08QWRDJ7tgl76FmTCHauWCJYLpzbH1dGHqFE2ZYlXhy/U6uxEXdYadvGhF8jJz5K0L18UvJknoynj5Yo3mRAO64QQDMNayf9d8akmIR7+QF9txLuWgIGdq0VXONdQImYnIhfkO0Nn9syzdcC1jz6TsJjBJYiI/Fguv0hfGDO/Ry6T3KiMQxbTF6feXj+VaecyEWoHNRtBLhX2E4eJ5U/beWmG+kK7qQWs49Bh7oRiC72Nh/QHMqKh8O7YdD3da6bXbnHukB09PMzfEp/zZf5+xz/8/Z/o+8hGXrv09VWDwYjkTUJvya+vCR2SX8+KhqJhoVJxrD7vLBJdfZ9oSg7OS2LXR8Oy3DzvsWgoFoJK5yrJXUn9zpf5CYONEmtSU5NgK6ntp3nnNxHAxJmDNBqaMuK5GqmIPIJ+eKxY+INlkeCycJ/4y0FYJpqI6cVKtm36kVSF3TGAk2r4XyV8hCmIZUSmj6DmJw6y0U2JUR7v2tr/on9R/BbK81UNXKnoLjtma99qYJ9r2aXEIbWkqWE2yCQ54CFMWUlZyBYISCvE3PpaHUcvBQMu+q4xGObHDrbei36UUQr6MaL3A/0R2dQPZpjnQgV4KyF1KmX7VbD4LWqAHnaXHVKK1cGyYWo3hGJlw9CclYVaZ6G9Wl17OdZkPTf51+IBTbcpTM2+ibIBcomCMBBi/1YQ65eFRQ9tnb7wceYaX5/zbO1f+xSumaNhjxYNeTSJ7xGYQpOa8TllrnzbxmIpjy5NETdLdFFkhbaNGVhNMrBjQqdOwFK5xULxaX8eyj7MxzG6FnxYqjQXxomn2DGTteDDukzlFLv7WCUXK5is9KbxpTdzaWIdxThmcowdS2IwDhxLYjAmyqa/SGIwiAiCZXSqrnzWmlf4pVvvEngpbEyHEwJLkhv2+nTWpUuWpKDVyscnhcVdxX2l1VBa3GHb3BX331MWVJpkVMA6ery9FF4k6qA/KK0yK7eW4oq7ueAIAXJJFjscusAnDouhi79y+FONr61TQ0pawRFw/4RT6017QcgLa7jQ6H+TzPJnWLGTlKmki9wbWAXupMbSqQnvBxAmmP8hyQhCGP01+SU/DrV3cDL+p1H8okeq4X2yJOC/RmT3sjr/djNbVLsNCaaozlkYsH7ddKRmr0R+0OsvpiVDbVUQqS5J5pDuHuCa8/ZK9UDqlP/fXJKGVX0LrBXPosE+AjkzTuxeKwju6lJNalJ0Ngkr2i8ROyv8A/LZLfYPJFgpYogDBMy5BmU9163zUByquo4mIa1gL5jsfgJHH4Hjmwlmyl2jSVdCcxcv1rbp5428E6Sa1E6yBQRFWiqb3jey7IjTYYVDWyDYItyf74XoiilYWtDr68UBGjyBOwp6Ag1G9c2ChYhGxt6f6pzlgewbIUX75WkROF5YqMemqDIB9x9NQTjR1MXRspHWRextVA6UkK8TiGSNurKQLbYJvu4UiWzFl9hxDbslhMFtmayn5U8qLV0VUr/01g6k6Wh1cd0kRdezlmYlfDJVVQGGTqpwTDTKGF8rfdzSPUmV5a3zucqVhbLGhQxdR4B5g6KxCl+5YkKF5S1/TqqwUK+wqPXWzxg/6p7Y0xUTKy5qeSOpYgWyNpUo1yrYmrnZKJFuFY4s6K/O1vE9HNNXjy2eA7TipXzF62YxZGElvnDgwU6KTC3OEoPyL3yhbb45sMhYkxAfQN3c4pshtiYqQTI2wDN/1q2LbjXjPuXZg1e5sjr6lInrs54lNH15HmVrf+Xb8TYgMiS1Q5vw+FGu1xlv5xtoh/ZCHyMk7IXl5rIw7YUB2gvL421lu2sB2bk1NYmWVLktdXFT7tqP9owjBZNu9ReyGbuPYZfObnk8s1Gi5lT0XjgBvT95LOkktOmzLv0gAhDOyGztWdAerrTAraLLqs6G6qvgfANffodLtSMcLYnZYCjH5mhHis8sW8Y2bBe8MAApjNmI3F/AZU4ZeaKwlJYrZ+XHZhDk6G0sMx8hErwWGHL/HDYIrHy4Q8bdXoMI0cQiwXYdYoO4qYC39RqcTGEZls8DsmY3KWsIK6zgOFZsq2BrRwRS+OadJ89o1+pntE0sPipONgXQry5BOJz0qLZJvBaUYur70ry8Sqo0FV79JXvlnEK8lfxRsohbJbb8VX77uBRgsMIVcWH3GKaGR7sg391Sr2EJt0helBE3H2Gdezm+RhQdWqZFBlu7WzdmUBJyLbRI0PpfZigLtmX65RHAZUbYk+QGSkiODKqH5Ank+xZiTWHNdzKLtYCwPysg0MeNayC4O42SISxSj8I7TaBumgYV40J6WWEiLOw3/6TjTPNV0onUNOBvI5z5QnGWb4RRAW1x01sFH90fHSvCGVyEC5sg1aDfdbReqHjboxwgkhoJKDaN5rTItvWjAth0QK0psXKJ3/wqW56x+M9mLtr3zRy2DcQBpjB3iKqreWnMHcdvKSIQZLmpPMFsbZBSTgWr+q36HGJyK9jeYN4M3m4b9O22VizoYgOEhyfuNd3qIGW3NSYzU70TmKlQ8oZrUlfm+87Tlnt1KnGvrtzIXRbiVkuiLkfkLvCt2cTRloQ/CHdF339nKBo+s6figUsoKfvYSXCvFTb1oanw4kUSC5VjYYNmn0abs4H2LH3fQul2FkGQQFxvy7JlLJd5b4i64CXtEmPUlRVdaYmuzKLmqd3oytzoSgeqQzvcGXSDurbSIuWj6+hLlMVHufgaH2VFlzjG+j/W+eyaCM13ja7poC8jUmBc4ayj3DruWju6dpeFJB+UibjwrT01d62zLiwGj1PG3JQM8cdulqPsUoYq0VN/kZJalKjEjkoiJAjr8msCOvF8Pe95PS8iJWLuLQ1Odl3qUqJS9kwaQG5iAA4eAH1wtT5WdHpuckNzE6MZV42I7pZdV4fRedYAcPqfd8PUHbctJ3Q6aVD7xw+KtmGeAYWArZZRqTnL2D6oIgEDWCixP8MWZ5XyJfq3xS8JEmWAI8PVJiXuxRA8o3hZbrQK0PwqauAScF4VypRyeRiCVLiUpD0Mt85z/dIVZ7at/a0Mg6FYKztra++lpx7JejJW3iEPAnbIg4Adce6tiR6HdPTcMxE9yz0qLtshsezqDA6su0YeioJHoRpodw8lFJAwmk7G0GuESVdeXpTBGHqNLsqJZW8ks9PbdHaa8PR7DsbTS2V8CPHTg4ynS1BHf7o8+YUktDMdiFqXCyWuboF5YzeOqtgUlATnFbbOrmgdQ7kxGMtiUFJyIxWLbuZ1QTlrYfAxAHuWzTy94d1RqbiASsbWjgjFBXwHdo7Ghz7xUOsB83qQZLG7y24g/MEaGltnCF+JPyKtmxB/qD8zFHzPIn6JBCIKXYOUEO5D0o8oiRLC3VEpqGRCSHfic3+uuIczQ+GuUL/4l0RlfbIyd6IyPeEb8aoyQ7p+SFblX2oO9+nev4vGD8ARH4CRBxDqp/bE/+yyG6gl1BTiXp7YxVVTp3fT62CfeHsXq4meYB1qV2Q/5exHaz76M1PPX94le95NZZ+h53BfEhh+RgmDfVwfXv89XjkfYueebJWwzjf14NhQNO6aCNm6XeMgO3/XBMgW7ZoEsvmRviqazyQAFPrt64V519jgR3aOG/x/7hwH6CM7JwE01ezrujCxbh3wDh6NQ/zHzrGWNo1vqXXnODCv3TkpmB1Vya0UYQS3oN5uQDUkbtTrpe6G+lHv1TtTAH7pzjGAO6jT4ytTZcjKovJvsvubjbwPyoK2R0Iyqnr22bBf6s84GFtvYEUprSmiRAXyPHsp4caFuk4uTld0hXsKWVm2TCx5gwe4X6L6J/QDZJ7jr8ksVj328UrIf4ORtsKvTnE5vUamY1lwuK5p9Mp7W/kBrlqY9gWsm2Ao+iMSba+HZVfnIXpspEdn8F2YaWfifS2958ffX4MFXEFv8Hhu5iHU4Z/Bx79g3fiM15l4yvcFzfziN558JA4INFZHLVBB05upTb+F8+Djlsx+KrCWCuTTC6Vm9v+JmzwYfDc3sx+HvN8CI5hNjOBcqt4Eyd36Myg8i6Te05nQgObHGUqHL3gBEeYQVXSuiaQAv3kTJkDDLNJkRKQ+ziQnAHMblXbGS8skhrNtWnhBXhKHvQXEe7ZZ1g2n3XylWPKBKTbOOv0QN+VRrRJ5p/CEOoq/71VmC0sSbOGQZAvvSLCFQ8ylESFh64vrpzBbOMRs4UZuUNzQyZxhaCJnONEc5J+S+cKhCXzh8BhfKOkaIripK7O8U5lBvCsT5tmWwA7WgIMUS134FuEkGV2VdLJgB3dFlSr2AlmCw9UQcG3tV1IdxWdIMGu/LJPp7+Y4/d3GgiT9PCF/npK1bJBvI58tIUkJVGzeJsnoc9OYj26JC0nNeiUEzBGdCjew6VEyFW4Rrb3y84Zp8qBHkx0Rb7+STIX3j1HhlZdfaogLBEVuYetj5dVBFq9Jfp3GTn0XdhDczNMkIX4iQYgJnF4Twg0tsUp6PEfeDMGlCOgiyylVPcavHxcPqP3BkxbfOc32UxSda+tk0UnKzX65CtibBXG9HQPKrMkubCyVRwIuRKwqDH8QqNTCaMcO1TlUVOHdVfFXcOSGcL88uUh/wBwdCHcnv4aJ14+Eu0PHw7tDJwbDkpWfHu5jTj68L9wX7g8HQ++lnNlgsYf3hN4N9emcbbgfR3r0usK5lp6Dg3hagUuWVxoZEa6tiTzNW0hiyo3gP13bJYrTT03UUDKyzKdMv7Rcyy4L2R4JY/NuHcQ1OxpVdmSNc21E7row0Srwq+EPQmFdAY/qdJxcJw9AsGOXLauhXjXWsEqfvh/ryeuvyqOTCNQAKd349as6ovU61X22rQcI52QHrI+UhR6arR4p6A6+m1ZO8+6/3NRf5T0TuxIOsAgZZ6NAttqLw/J989RzHz+HtQOhKq75MkrNV65t01doavVjhBrq6AsMI3ksFufKJFECJoufhdE6pTKnZJlTcW6fx0oN6aKQQoNMkmuOdPIg6yJQj4YSg6dB7uhkWANP5gLWs0zJsM79fFiH0iaDNXeWqgREk5uqoabUECZVn8UV9FcxIGWHp+V4+ACvT1xDRQekawlHXNiTqJcyp8rMOSCOfAJJ7VDyR6/QGJl70snocUpgvZ86DBcMyiL0fkDutVDfMRQ5TUUGpOBg6xxedwB7jViUv1uOgfAeodxjtOHAQwzLRIcIvsJMRewKGEblR0O4zTiMZ2fiycFPP6Iu
*/
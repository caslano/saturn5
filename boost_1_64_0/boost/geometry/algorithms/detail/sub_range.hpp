// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SUB_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SUB_RANGE_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/range.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch {

template <typename Geometry,
          typename Tag = typename geometry::tag<Geometry>::type,
          bool IsMulti = boost::is_base_of<multi_tag, Tag>::value>
struct sub_range : not_implemented<Tag>
{};

template <typename Geometry, typename Tag>
struct sub_range<Geometry, Tag, false>
{
    typedef Geometry & return_type;

    template <typename Id> static inline
    return_type apply(Geometry & geometry, Id const&)
    {
        return geometry;
    }
};

template <typename Geometry>
struct sub_range<Geometry, polygon_tag, false>
{
    typedef typename geometry::ring_return_type<Geometry>::type return_type;

    template <typename Id> static inline
    return_type apply(Geometry & geometry, Id const& id)
    {
        if ( id.ring_index < 0 )
        {
            return geometry::exterior_ring(geometry);
        }
        else
        {
            typedef typename boost::range_size
                <
                    typename geometry::interior_type<Geometry>::type
                >::type size_type;
            size_type const ri = static_cast<size_type>(id.ring_index);
            return range::at(geometry::interior_rings(geometry), ri);
        }
    }
};

template <typename Geometry, typename Tag>
struct sub_range<Geometry, Tag, true>
{
    typedef typename boost::range_value<Geometry>::type value_type;
    typedef typename boost::mpl::if_c
        <
            boost::is_const<Geometry>::value,
            typename boost::add_const<value_type>::type,
            value_type
        >::type sub_type;

    typedef detail_dispatch::sub_range<sub_type> sub_sub_range;

    // TODO: shouldn't it be return_type?
    typedef typename sub_sub_range::return_type return_type;

    template <typename Id> static inline
    return_type apply(Geometry & geometry, Id const& id)
    {
        BOOST_GEOMETRY_ASSERT(0 <= id.multi_index);
        typedef typename boost::range_size<Geometry>::type size_type;
        size_type const mi = static_cast<size_type>(id.multi_index);
        return sub_sub_range::apply(range::at(geometry, mi), id);
    }
};

} // namespace detail_dispatch
#endif // DOXYGEN_NO_DISPATCH

namespace detail {

template <typename Geometry>
struct sub_range_return_type
{
    typedef typename detail_dispatch::sub_range<Geometry>::return_type type;
};

// This function also works for geometry::segment_identifier

template <typename Geometry, typename Id> inline
typename sub_range_return_type<Geometry>::type
sub_range(Geometry & geometry, Id const& id)
{
    return detail_dispatch::sub_range<Geometry>::apply(geometry, id);
}

template <typename Geometry, typename Id> inline
typename sub_range_return_type<Geometry const>::type
sub_range(Geometry const& geometry, Id const& id)
{
    return detail_dispatch::sub_range<Geometry const>::apply(geometry, id);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SUB_RANGE_HPP

/* sub_range.hpp
vFPhj+5NfUO6hPdWH0Y0Iy2sxcb24YeWmvYr09mVXm3fcZbwcrufOAj/4xj7ZlpXLz0G1ziYSfamaWKZ5puXYt/14cKX4y4tjpj2lqZTRJqU6dE4l6aVueuUuoaGxpYWcx9/A926tWrJiibLLwfeH/fBTtWw03bbztBO14Hs+8RHWDuZowqZvn6z/o72foFIVwzpoonrLnqWAsScrnCceYcKcg+1cvuTGwxSzssDN1LgViZb0329dM4VetQP1cMQr6fehj2QwEpoBPohi6DD/FK/ziJv6E/Wda/ro5n+zp6gXzDeM7B/G5+wPpT2/HdrFgp9Kpw+HImV0dDIeXeofUogLRoY/b5MAfLtnDH8YQ5sssimJdOWXpk8ZUC8l754qk1byuRHa3cL22Qe8mTJUJ/vdxx0EgAj+WtlPth2IpsF/rnLGHzTrHUsJgp5JjMO3FHJTQbFcRZ45Hr0TE3TQE8beTW/U3OU0HGNqGO6OlhHAbM6hp/zeR8+Z+fLna25DGRsf3NdXx/OcTRZ/RCb4mRpBnrX99IWf4JNwzh+xdR8zkgt8KL68802/obW7oGkV488/IQsVwXWwbs5g76ioaU5saKpcWXjJyyTMATbqQV2agvUFRuS/aaehV2+vp/RH+7U18/rZKsobsyHL+sinbN1drkPF5X2fPjGalmGCyqDUsf2/u7V/d3BeoxgTQOqTiEY1hPnoQ45Rsgvd/KJSLsmQJDdlIfN/8falYDXVRXhW1pCyyJNuhAolNBCCUvT7A1FsWmbtoEuMUmhrUpIk9c2kI28ly5QsW5Q2V1AUFncQQErm1gRRZBFlBbKJgKygyJqAUFEwDnn/nfe3L/3pSna73tfc87MmZkzZ5sz95w5TfUL5swT7TY1eCq5gKr7JbqO5tb9tGJXr3C9ak/1yQJr10t5uLO9vy3VXqtzx1I/d0TrWzqI2qNY80yDSJnZWEc/bnRSijZBAf8SgFENQ7DWWFtAWm5mqs/2h+FYwxu5VwhONCY+uf2Y6OlO8dzG+Z6/+lb9Xk7r2owxiP6h+YHybCGeqF3LsrWZlA5DyqZ3UbCuL1uLb8QhP+TJfKmxHVv/x3lkmZlHovW5LUl+dBbboxmAOiT7PXZSD/79Dlrbjoq1Q9wGXD7ZtsUMRyqI7tyuSKgPEJO7IGRInBM/QD+O5sEOXZuBM0tQhE+0hpbuwJaZnmDLzIUtcyzmwZNNXRtCWZe1pjvaEmsMENc78bv7B6Tl2rGT9qRdtHfpRlryY3f2m4s1rWWPprJ9SEs+cHPEZhnknOzvcZG8q4jnaqRXkbyTrLxCZzbROZ3orEP69MHJvkN7zL8tTzzXE8/PIO3yWbfLCffzSLt8W68O4nEWlduA9Fmkn6ONfo4ZxNjKPTbx/Y3kOI/kOB9pl891XUC4X0J6gcFNHAcfcN/kY8qRvBeRDBcj7fJZ3rmEeynSc0nHFdQHu8jHcZmkV+QHkrZjbmhwOXwizXQO80rCF7jH/xbwjyb63yH8o0H/u8BfRfjfJ/xVwP8B8CeRPFcT/iTI80Pgn070ryH800H/WuCvJ/wfE/564G8E/nLCv57wlwP/BuCfRfg3Ef5ZwL850ifV9xbWJ+r7M+CfR/R/HscXOL4hAX8B4d9G+AuA/0vgX0T4txP+RcD/NfDnEv6dhD8X+L8BfgXV927Cr0B97zE+LNdnTyY/7m8N3PVRhv/OwI9OKH+/ga9KgG8x8EkJ9B808NMTyj9k4OsT4I8Y+PIE+GMGflYC/HFbvwT5njDw8xLKP2XgCxLgTxv4RQnwZw18bgL8eQOvSJDvRcxn3cXh/PapYv3eIraP++EcEH1v+TPpVdoe80JI9xWCbyI=
*/
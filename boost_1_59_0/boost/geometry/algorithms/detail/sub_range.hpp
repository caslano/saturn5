// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SUB_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SUB_RANGE_HPP

#include <type_traits>

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
          bool IsMulti = std::is_base_of<multi_tag, Tag>::value>
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
    typedef std::conditional_t
        <
            std::is_const<Geometry>::value,
            typename std::add_const<value_type>::type,
            value_type
        > sub_type;

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
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
*/
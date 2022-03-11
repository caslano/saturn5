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
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
*/
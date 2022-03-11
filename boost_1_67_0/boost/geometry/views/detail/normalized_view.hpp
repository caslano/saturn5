// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_NORMALIZED_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_NORMALIZED_VIEW_HPP


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/geometry/views/detail/range_type.hpp>
#include <boost/geometry/views/reversible_view.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/util/order_as_direction.hpp>

namespace boost { namespace geometry {


#ifndef DOXYGEN_NO_DETAIL

namespace detail {

template <typename Geometry>
struct normalized_view
{
    static const bool is_const = boost::is_const<Geometry>::value;

    //typedef typename ring_type<Geometry>::type ring_type;

    typedef typename detail::range_type<Geometry>::type range_type;

    typedef typename
        boost::mpl::if_c
            <
                is_const,
                range_type const,
                range_type
            >::type range;

    typedef typename
        reversible_view
            <
                range,
                order_as_direction
                    <
                        geometry::point_order<Geometry>::value
                    >::value
            >::type reversible_type;

    typedef typename
        boost::mpl::if_c
            <
                is_const,
                reversible_type const,
                reversible_type
            >::type reversible;

    typedef typename
        closeable_view
            <
                reversible,
                geometry::closure<Geometry>::value
            >::type closeable_type;

    typedef typename
        boost::mpl::if_c
            <
                is_const,
                closeable_type const,
                closeable_type
            >::type closeable;
    
    explicit inline normalized_view(range & r)
        : m_reversible(r)
        , m_closeable(m_reversible)
    {}

    typedef typename boost::range_iterator<closeable>::type iterator;
    typedef typename boost::range_const_iterator<closeable>::type const_iterator;

    inline const_iterator begin() const { return boost::begin(m_closeable); }
    inline const_iterator end() const { return boost::end(m_closeable); }

    inline iterator begin() { return boost::begin(m_closeable); }
    inline iterator end() { return boost::end(m_closeable); }

private:
    reversible_type m_reversible;
    closeable_type m_closeable;
};

} // namespace detail

#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_NORMALIZED_VIEW_HPP

/* normalized_view.hpp
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
*/
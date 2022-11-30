// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CENTROID_TRANSLATING_TRANSFORMER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CENTROID_TRANSLATING_TRANSFORMER_HPP


#include <cstddef>

#include <boost/core/addressof.hpp>
#include <boost/core/ref.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace centroid
{


// NOTE: There is no need to translate in other coordinate systems than
// cartesian. But if it was needed then one should translate using
// CS-specific technique, e.g. in spherical/geographic a translation
// vector should contain coordinates being multiplies of 2PI or 360 deg.
template <typename Geometry,
          typename CastedTag = typename tag_cast
                                <
                                    typename tag<Geometry>::type,
                                    areal_tag
                                >::type,
    typename CSTag = typename cs_tag<Geometry>::type>
struct translating_transformer
{
    typedef typename geometry::point_type<Geometry>::type point_type;
    typedef boost::reference_wrapper<point_type const> result_type;

    explicit translating_transformer(Geometry const&) {}
    explicit translating_transformer(point_type const&) {}

    result_type apply(point_type const& pt) const
    {
        return result_type(pt);
    }

    template <typename ResPt>
    void apply_reverse(ResPt &) const {}
};

// Specialization for Areal Geometries in cartesian CS
template <typename Geometry>
struct translating_transformer<Geometry, areal_tag, cartesian_tag>
{
    typedef typename geometry::point_type<Geometry>::type point_type;
    typedef point_type result_type;
    
    explicit translating_transformer(Geometry const& geom)
        : m_origin(NULL)
    {
        geometry::point_iterator<Geometry const>
            pt_it = geometry::points_begin(geom);
        if ( pt_it != geometry::points_end(geom) )
        {
            m_origin = boost::addressof(*pt_it);
        }
    }

    explicit translating_transformer(point_type const& origin)
        : m_origin(boost::addressof(origin))
    {}

    result_type apply(point_type const& pt) const
    {
        point_type res = pt;
        if ( m_origin )
            geometry::subtract_point(res, *m_origin);
        return res;
    }

    template <typename ResPt>
    void apply_reverse(ResPt & res_pt) const
    {
        if ( m_origin )
            geometry::add_point(res_pt, *m_origin);
    }

    const point_type * m_origin;
};


}} // namespace detail::centroid
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CENTROID_TRANSLATING_TRANSFORMER_HPP

/* translating_transformer.hpp
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
*/
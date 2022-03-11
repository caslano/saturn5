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
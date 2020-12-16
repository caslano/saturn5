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
4KELlOPzeFFAg3WHpvkKaC4NyoH8Vh+XKTznsfiXEf68qeNVg0Ot7WfH+rr8yBQfLVH3SUxLhe+1r0C/C2R5ZUR/eRX0TDjtbzivrOcvbwz729dSWq8JXkdpXUaT+dbwBoM/1/ShNwne8ZZ2JTqHv7JR0rZPOl5fNfGDq4Qf5vKmzldLG8tawNHoNr5G6ig2K/dP+rrK+ed4HH1c7p98Z+NMzoq5A/WcpuvU+H0Zd8Bb7uT0bXFfJP93z5Y/3exQl/T5H7aMikcTZNzsy5Xahbt5eFybx2ce6XoK/abh9W4PwCRBKC/OM13bqL/rOtt1hyXlujkFkrsGYHtLFoTHwPejnbgcpCVusJtod2Fv56InIa/6XvBB5CW4HgNdWveb64nOrr1uwNi2DOeYsX/KlVGpzh3YN2MJ631U2d/1MhZqWeZ4Nykb5rm87befUPivR+BvVvglEfhbBO/mxI5G429F/U5E/QL9v858P/8sdEhw6FDPT7EfEfRIC9769XvV+KT3I37Zl4XKMPezGd0R3n8LX9WNYbbud6kxecLI9zXUZ0LXB/Nlc+ZJ4oa3iP/BeS01p8OZEeFh60ywyG/G9xIPqacaq/Q3mPuhlwmjlweMXiagl+8GekG5Vi/fV3jOY/E/VPjqGuJh7sr+kdLrcTVhvT4EnRAcOjB7KE1ZPzOy5tU3ShevadQ6RIzLxmtQJn0DQNuJDEg7/bm01t/vRH8BPc5oKZkYZvVzsNGbwT14Ha1DreLoLFz2Jf1Bjb+PNhb3Jf3RjOl/auSfeVMfdvEX0LbpM6ju7VM62NuJq9j63YVCyofTuejkcADfEp+c5BcfindkNurznBA94jRsJIbqNlzivbNKV7a7Zy50x9E9C7mcCwuEGEu6e3Xz8g5uDd8nR/ujEkGWGO4Oxf6hfyhZl866DehuU+jPtYGZA/0rsC1XBkGafJ2XNYXOHTs6T+3RumUh1VPuj9PvaKRHxpOpUX3ud06TGSdFzt6+DrlL0cKd/NPtIwT9ltb+fvMwj8WpvV+PmXV2Jeo8F3XuncE3WKXocKkWizY4sim8T87Xdzy9X9ntUU3hfXDVTp9EE8P9poAtlPsHfQTgpFt6Jhu0Xbir4OimUrbT3tq+WSnfIjBf0b7p0tWH+qZjm/x59tFqb8ATm8J9u6oJflHsjGLGnA/tcYzxsQsIF3ne+zD6KcuzqEndsYW/uTySC/5TjQeVh35jehLq+GL1Ft4J4CPzuabwPPvJTcLT6e1ti8JjzEmCd3lFr1dhrXCywrNdPGZ84zKlv78CdxTqc5rJO68pXPZTUB+ySanPU02bnQ6ZdJs9rak4VpGc1KaWZo53hiqbfd7648JlP6PJm03/Ykdg+pfBoo1XQf4uT71Zru5UrXN9K01rlJwX+K8q0/8K3Ifgy7vge1eX7D89nds6e6T/WITcWzDtODozPlzHtajjC1DHeiebu6YyF74LPa3vrnQ2UMXviGfjwRvlopMa/65LudgygC91b5FpOPY1Qz9t2Id7ptJP7SzvyQ3spF7Z2i2IBzcq+643fWsd0rdibv4ZzN+q54fT9wjet/dT1ZnAFmPvrUoGKs/J0KZkaEWZdehjHSJTkMa5Q9WnNhkfsdnk6Q76CnBWB2c3heeOx7u0uoMOZR6hyuwzZfabMs8Rnj6/GtM/BxW+X8k0H35pa1MxJl0Pv8TynlavZa/wtkO2tUq2c5vC89OdlL4VZ/aQ1/mQZ4quZY6NOghe/J2dg1MeJ4/W0/mqHR9bFG7H4Sad18hCeUcxN+D66T0CY03+XP7v2JtTMPsmd6kyTzP7CpMKd7ppnwuMPNYmJoK8wGu+GZP3WNO2F6Iudcb2cxE=
*/
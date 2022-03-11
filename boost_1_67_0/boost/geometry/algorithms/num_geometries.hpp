// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_GEOMETRIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_GEOMETRIES_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tag_cast.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/detail/counting.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag_cast
                            <
                                typename tag<Geometry>::type,
                                single_tag,
                                multi_tag
                            >::type
>
struct num_geometries: not_implemented<Tag>
{};


template <typename Geometry>
struct num_geometries<Geometry, single_tag>
    : detail::counting::other_count<1>
{};


template <typename MultiGeometry>
struct num_geometries<MultiGeometry, multi_tag>
{
    static inline std::size_t apply(MultiGeometry const& multi_geometry)
    {
        return boost::size(multi_geometry);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant
{

template <typename Geometry>
struct num_geometries
{
    static inline std::size_t apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        return dispatch::num_geometries<Geometry>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct num_geometries<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<std::size_t>
    {
        template <typename Geometry>
        inline std::size_t operator()(Geometry const& geometry) const
        {
            return num_geometries<Geometry>::apply(geometry);
        }
    };

    static inline std::size_t
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{number of geometries}
\ingroup num_geometries
\details \details_calc{num_geometries, number of geometries}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{number of geometries}

\qbk{[include reference/algorithms/num_geometries.qbk]}
*/
template <typename Geometry>
inline std::size_t num_geometries(Geometry const& geometry)
{
    return resolve_variant::num_geometries<Geometry>::apply(geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_NUM_GEOMETRIES_HPP

/* num_geometries.hpp
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
*/
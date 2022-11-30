// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_GEOMETRIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_GEOMETRIES_HPP

#include <cstddef>

#include <boost/range/size.hpp>

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
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Samuel Debionne, Grenoble, France.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_ASSIGN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_ASSIGN_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/assign_values.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/for_each_coordinate.hpp>

namespace boost { namespace geometry
{

/*!
\brief Assign a range of points to a linestring, ring or polygon
\note The point-type of the range might be different from the point-type of the geometry
\ingroup assign
\tparam Geometry \tparam_geometry
\tparam Range \tparam_range_point
\param geometry \param_geometry
\param range \param_range_point

\qbk{
[heading Notes]
[note Assign automatically clears the geometry before assigning (use append if you don't want that)]
[heading Example]
[assign_points] [assign_points_output]

[heading See also]
\* [link geometry.reference.algorithms.append append]
}
 */
template <typename Geometry, typename Range>
inline void assign_points(Geometry& geometry, Range const& range)
{
    concepts::check<Geometry>();

    clear(geometry);
    geometry::append(geometry, range, -1, 0);
}


/*!
\brief assign to a box inverse infinite
\details The assign_inverse function initialize a 2D or 3D box with large coordinates, the
min corner is very large, the max corner is very small. This is a convenient starting point to
collect the minimum bounding box of a geometry.
\ingroup assign
\tparam Geometry \tparam_geometry
\param geometry \param_geometry

\qbk{
[heading Example]
[assign_inverse] [assign_inverse_output]

[heading See also]
\* [link geometry.reference.algorithms.make.make_inverse make_inverse]
}
 */
template <typename Geometry>
inline void assign_inverse(Geometry& geometry)
{
    concepts::check<Geometry>();

    dispatch::assign_inverse
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
}

/*!
\brief assign zero values to a box, point
\ingroup assign
\details The assign_zero function initializes a 2D or 3D point or box with coordinates of zero
\tparam Geometry \tparam_geometry
\param geometry \param_geometry

 */
template <typename Geometry>
inline void assign_zero(Geometry& geometry)
{
    concepts::check<Geometry>();

    dispatch::assign_zero
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
}

/*!
\brief Assign two coordinates to a geometry (usually a 2D point)
\ingroup assign
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param geometry \param_geometry
\param c1 \param_x
\param c2 \param_y

\qbk{distinguish, 2 coordinate values}
\qbk{
[heading Example]
[assign_2d_point] [assign_2d_point_output]

[heading See also]
\* [link geometry.reference.algorithms.make.make_2_2_coordinate_values make]
}
 */
template <typename Geometry, typename Type>
inline void assign_values(Geometry& geometry, Type const& c1, Type const& c2)
{
    concepts::check<Geometry>();

    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2);
}

/*!
\brief Assign three values to a geometry (usually a 3D point)
\ingroup assign
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param geometry \param_geometry
\param c1 \param_x
\param c2 \param_y
\param c3 \param_z

\qbk{distinguish, 3 coordinate values}
\qbk{
[heading Example]
[assign_3d_point] [assign_3d_point_output]

[heading See also]
\* [link geometry.reference.algorithms.make.make_3_3_coordinate_values make]
}
 */
template <typename Geometry, typename Type>
inline void assign_values(Geometry& geometry,
            Type const& c1, Type const& c2, Type const& c3)
{
    concepts::check<Geometry>();

    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3);
}

/*!
\brief Assign four values to a geometry (usually a box or segment)
\ingroup assign
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param geometry \param_geometry
\param c1 First coordinate (usually x1)
\param c2 Second coordinate (usually y1)
\param c3 Third coordinate (usually x2)
\param c4 Fourth coordinate (usually y2)

\qbk{distinguish, 4 coordinate values}
 */
template <typename Geometry, typename Type>
inline void assign_values(Geometry& geometry,
                Type const& c1, Type const& c2, Type const& c3, Type const& c4)
{
    concepts::check<Geometry>();

    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3, c4);
}



namespace resolve_variant
{

template <typename Geometry1, typename Geometry2>
struct assign
{
    static inline void
    apply(Geometry1& geometry1, const Geometry2& geometry2)
    {
        concepts::check<Geometry1>();
        concepts::check<Geometry2 const>();
        concepts::check_concepts_and_equal_dimensions<Geometry1, Geometry2 const>();
            
        static bool const same_point_order
            = point_order<Geometry1>::value == point_order<Geometry2>::value;
        BOOST_MPL_ASSERT_MSG
        (
            (same_point_order),
            ASSIGN_IS_NOT_SUPPORTED_FOR_DIFFERENT_POINT_ORDER,
            (types<Geometry1, Geometry2>)
        );
        static bool const same_closure
            = closure<Geometry1>::value == closure<Geometry2>::value;
        BOOST_MPL_ASSERT_MSG
        (
            (same_closure),
            ASSIGN_IS_NOT_SUPPORTED_FOR_DIFFERENT_CLOSURE,
            (types<Geometry1, Geometry2>)
        );
            
        dispatch::convert<Geometry2, Geometry1>::apply(geometry2, geometry1);
    }
};
    
    
template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct assign<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    struct visitor: static_visitor<void>
    {
        Geometry2 const& m_geometry2;
            
        visitor(Geometry2 const& geometry2)
        : m_geometry2(geometry2)
        {}
            
        template <typename Geometry1>
        result_type operator()(Geometry1& geometry1) const
        {
            return assign
            <
                Geometry1,
                Geometry2
            >::apply
            (geometry1, m_geometry2);
        }
    };
        
    static inline void
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)>& geometry1,
          Geometry2 const& geometry2)
    {
        return boost::apply_visitor(visitor(geometry2), geometry1);
    }
};
    
    
template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct assign<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: static_visitor<void>
    {
        Geometry1& m_geometry1;
            
        visitor(Geometry1 const& geometry1)
        : m_geometry1(geometry1)
        {}
            
        template <typename Geometry2>
        result_type operator()(Geometry2 const& geometry2) const
        {
            return assign
            <
                Geometry1,
                Geometry2
            >::apply
            (m_geometry1, geometry2);
        }
    };
        
    static inline void
    apply(Geometry1& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2)
    {
        return boost::apply_visitor(visitor(geometry1), geometry2);
    }
};
    
    
template <BOOST_VARIANT_ENUM_PARAMS(typename T1), BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct assign<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
{
    struct visitor: static_visitor<void>
    {
        template <typename Geometry1, typename Geometry2>
        result_type operator()(
                                Geometry1& geometry1,
                                Geometry2 const& geometry2) const
        {
            return assign
            <
                Geometry1,
                Geometry2
            >::apply
            (geometry1, geometry2);
        }
    };
        
    static inline void
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T1)>& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2)
    {
        return boost::apply_visitor(visitor(), geometry1, geometry2);
    }
};
    
} // namespace resolve_variant
    

/*!
\brief Assigns one geometry to another geometry
\details The assign algorithm assigns one geometry, e.g. a BOX, to another
geometry, e.g. a RING. This only works if it is possible and applicable.
\ingroup assign
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry (target)
\param geometry2 \param_geometry (source)

\qbk{
[heading Example]
[assign] [assign_output]

[heading See also]
\* [link geometry.reference.algorithms.convert convert]
}
 */
template <typename Geometry1, typename Geometry2>
inline void assign(Geometry1& geometry1, Geometry2 const& geometry2)
{
    resolve_variant::assign<Geometry1, Geometry2>::apply(geometry1, geometry2);
}


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_ASSIGN_HPP

/* assign.hpp
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
*/
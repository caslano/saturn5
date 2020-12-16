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
pq5/ohFaurDfz/Z16XopALNndiPB0IV6BzPXyrpzKJp0FNzreA8eVaqguYG5M7v+aIWa+gPjZ5lcY3Y09QfG537wmeVX6k+wxMaqBjRbMN7DkEGv3qIVgzkzG7DxbjH1MNpAUo2Z8ekwytMbjGftHen3Cy0ArBazjfF2M6kHMAdmW5fdr0U9gPHeH/3z/DP1AMazfuKz5QlaIRjv3XjcwtFoZWBuzFYvrVZIcwjWvmfFRZ+uh+YPxs/S4WfPV2ihYDyzHU3WUmYqMGtmc1Ifb0FTg1ny/i7UWUz9gSmYGclW96QZgVkxW1HeLY/6A7Ng1q3ZKbp25f/8zeU82GD/Opk0PzB3ZrMef12CFgHmX2EBFVZbb/s9tDwwKatbZbZtAT03wfBecOH/79fHq7qilYLJmaUZz3xK94kQA8mQP/td0dGR1NrkP4nOEkL7Vdia92N+oE0Hw+9bC8A0k2MM0eJCKOsKG5C79A5aEpgxM3XteyNpRmAKZm77vAdS72C2zHQfhC5CKxHOUvwmZgBaKZgBsx8ZLuX4jqIBk/z5W7jrkEvY2Cp0XbuN+XvO2/C/ifKW3UfzBTNiNjVuYThaAFj6nzXvwn5DNtduhxYYRtdShcWvtXpMWYN5MNtkdGEa5QJmx6x/u9cOlAuYEbMPjy9+RCsEkzMr7OVPZ9GA2TLTjPOvgyYfp71mr6BWE9FcwYyZhUhzPdC8wSyYtZjyg/L0B5Mys3pluIpyEaxLP+UatFAwE2bZ8eumo8UK9rTpvZlo8WCmzKS1F6agJYE5MnMdsrEzWpbQw9OY6/loBWDmzI77jLuAVirU7c92aotWPo7eyyvMLWnbVDTpeO3em69uvQNNAWbP7FT2BNrPF4zPdu6z4+ZoAWC8d9v+xR/QgsAsmeWplEWUp1BXx0u2Dd/ZVWABepXXdRH8rLTZnt2AbCKdpcICVt/ZgLZ1Iv0zNCqsbseZP9DUgj3emKBA2yPYln3LddDSwQyYZSzv7YOWJdiCH6qmaDmCKT8ud0PLA7NgPegMeLYerRjMhJmP3GYCmgbMlNklm6z+aJJIuF6YLTp/7CqaAsyImcVz2w5obmAyZmOKZbvRfAU7tcHuBt7P/MHwd0T3IK3c9ruj8BkQB4bPnPsw24UdO/amzMDwvvQQ6tz6VNFDKwCTMet4zsKBcgGzZ5bfKPYK9R6lvaZHrZHfqHcwG2a99y44Sv0JtvzX7uVogWAOzNr/qwxEiwUzZ/ZmT9koNBWYE7N9/u8uUu9gjsxyzM/5oRUKa04beuACzV1Ys+vInaXUXzTcW5mdOt/RivoD4/s9eKoznfoDUzAbeHYiWaxgazcPDENLArNjZjyh9XDqD8yaWd82IV40W7CazG4ZqkJpfjHaPYwqdQ5GcwXjudyv3uUL9QdmxmyubPcjNH8wfs6sCabn0ELB5MxKxrSMQIsD473f/tQ4AS1VqDsyynkB9Q5mw+yEV/OqNFvhLBN0lk9AKwPjme1pfP0jmnySti382DsVzQ2Mn+VmJx0NmlKoG7xx9xWaOxjPepbu61E0dzArZltmOJuhqQQb4vpuFppaMLXfoJNoOWAOzGaXzOqPVgzGM/tU48glNMlk7R7KCx6cQFOA8bpO6iqN0HyFuqVfo3XRAsBkzGysnDeiBYFVZeb1eXZttHgwe2YNMtZMpt7BnJj59jDbglYAxrP2uPLzKZoGjF8T3f0MC2jusdo91Krnt47mDsZ7n1J7WFs0fzAnXlf231W0CDB7rXvdt1KaLZgjM4e3G96jpQtmEuI+jPoTzHtZpDf1B8b7mzVi53Lqbwo8/5iNWfRMRv2BmTKbMeSMO80WzJxZyu/1yTRbMJ7ZwGU=
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_DETERMINANT_HPP
#define BOOST_GEOMETRY_ARITHMETIC_DETERMINANT_HPP


#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/numeric/conversion/cast.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename ReturnType, typename U, typename V>
class calculate_determinant
{
    template <typename T>
    static inline ReturnType rt(T const& v)
    {
        return boost::numeric_cast<ReturnType>(v);
    }

public :

    static inline ReturnType apply(U const& ux, U const& uy
                                 , V const& vx, V const& vy)
    {
        return rt(ux) * rt(vy) - rt(uy) * rt(vx);
    }
};

template <typename ReturnType, typename U, typename V>
inline ReturnType determinant(U const& ux, U const& uy
                            , V const& vx, V const& vy)
{
    return calculate_determinant
        <
            ReturnType, U, V
        >::apply(ux, uy, vx, vy);
}


template <typename ReturnType, typename U, typename V>
inline ReturnType determinant(U const& u, V const& v)
{
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<U>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<V>) );

    return calculate_determinant
        <
            ReturnType,
            typename geometry::coordinate_type<U>::type,
            typename geometry::coordinate_type<V>::type
        >::apply(get<0>(u), get<1>(u), get<0>(v), get<1>(v));
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_DETERMINANT_HPP

/* determinant.hpp
65lwxbDmNa3Z+wubv/6Zu2317jju3rt979Z7+1nVVX+Frq7pMCAuNMg/ok9sUJ69Lp4c4kf2qYrnQxz4v/rm1Q3/5BA/8m3nYvkQB/7vvHoTlzjC97+Py+Q/G4OYmL78P8Tk2aehxBG+fz+qaH7FIM/mBTzED+1fF/7Px4FP4nncGeRD/EAcVrKj7M//6dTKs5EP3HEUHBaWW2D4yd0y5+iWNlC6av6dvhbPsmVobIy/sxMv
*/
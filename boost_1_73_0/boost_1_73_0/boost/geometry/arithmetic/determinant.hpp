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
AhSZZf1ppUXCJmXZ0RfBMjna2AOXAKBtaZOZf7RyloJnoK2HJuKo3OPwZsheYi7/ZhqfV7HsIHK+/KaZn39U73y0Vaspe0oOIzaxVroyjIENtDZ2epA5y2C10zsq2g3G7945vFPIJ+osZd7zSDvnsSmjFQmLjMxWBj8mWSMhp2kR0FDRxZ1VZ+anzEmXIAqvexB0Di44ZHh1un91PQUnC5vyevPvJejO53goHJXygdSqqSoCPLvr9b4FtoPm55uyue9uteDK/8DXo0J24euJH31T4JPTOG+kIbCQ1K4gBUdPFRoXjTQKNClBgas/j5yhloTPccfbyv6Ijw78VyCXAgFDII1pmOBaLEoh35SB7PSgApE4ghU/qdp8Mj27aXntUoK1CUgBAZcopQ2sFlXI67fEa7VsWIegDYE/Lmj/mqAw8DdVjlbA36Kd4Pv4mLQS3EWTx7tEffTkRyEnJ6TV0ck+h1HWiABP4JiH++RsSvD2RkIMMThBc5hCVEKMQaVPoYiKpZCfhtrlym2tJI1E8DK+qAE4lesQLFA0EPn2APB4aRYlaYlAeflxZgwiH41aZbchR9IowD07mBhCyYD3Qrz6Euo4sFgz3rjwfMGNs9JqwhdiWNqgVvDiaoPS0PN60OEhFTdiSfhzihJ/
*/
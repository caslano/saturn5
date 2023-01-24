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
dbSVL+Cln+bEbMxUM1s5OPTTglPOhKAtr+Srej0Y3jm909V4lmgGRs+1pT+RmGymDk1AKHuf/PuGRbw8YfYo5CfPBn7AWXz+wGFY0E1mN1+UWIOXV8HzFvQ8mmQZt0cMuqPV1CTE/B8MyrgvSofXvr4oH2Gju17+3N6IdZjiLnwmj/UuOF09yrD0qjaUeypl9CCmNbVZVphIksyoYgXuUfpznxa9cKsy8+BEPbEhjGyV3Uw3tqr+HkbInOIkWcbovHwCkur11NDyjXVyxa9zZriyxNiXazkYTdNqJI98d62PoDl20tLeZc3++ok+gxSttz30lt0hqEDWbhP96KJ+/WEUtejhzEivkVyBal5iz5qg5CWjSrMWcletUE9wQCPRvFT/K/GcU+hYOHC6nJQg+gvRHrOZkvMU9HYyJG1Y1CJAerIA/+/sGQ2MDw45veoulnBMYiswsjcw7QfXRnGWV6KxkxKbZtOGUgU928jsaXFFAUElm0jThxmfgzmxBK/Ej3IQWFqPljuXw8WL3ILNY6/k8cIEF7friC83m7Ezc2b5fAj4vcjTv4uyWNuQ6RuT6SXa18u1CyR676rSXdrbEkM5k59/NHb88Tqx9vtd1cUA8diViYHPkp9mfX6tixo6SPtSHGg7KNV5QDMBdAWFTucYld6Dpd1UDPLBHwMnfXe9HjwAn4LKb8pjpCb6nNMrkSd1y02UEPBnxlGE
*/
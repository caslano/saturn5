// Boost.Geometry

// Copyright (c) 2018 Yaghyavardhan Singh Khangarot, Hyderabad, India.
// Contributed and/or modified by Yaghyavardhan Singh Khangarot,
//   as part of Google Summer of Code 2018 program.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISCRETE_FRECHET_DISTANCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISCRETE_FRECHET_DISTANCE_HPP

#include <algorithm>

#ifdef BOOST_GEOMETRY_DEBUG_FRECHET_DISTANCE
#include <iostream>
#endif

#include <iterator>
#include <utility>
#include <vector>
#include <limits>

#include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/distance_result.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace discrete_frechet_distance
{

template <typename size_type1 , typename size_type2,typename result_type>
class coup_mat
{
public:
    coup_mat(size_type1 w, size_type2 h)
        : m_data(w * h,-1), m_width(w), m_height(h)
    {}

    result_type & operator()(size_type1 i, size_type2 j)
    {
        BOOST_GEOMETRY_ASSERT(i < m_width && j < m_height);
        return m_data[j * m_width + i];
    }

private:
    std::vector<result_type> m_data;
    size_type1 m_width;
    size_type2 m_height;
};

struct linestring_linestring
{
    template <typename Linestring1, typename Linestring2, typename Strategy>
    static inline typename distance_result
        <
            typename point_type<Linestring1>::type,
            typename point_type<Linestring2>::type,
            Strategy
        >::type apply(Linestring1 const& ls1, Linestring2 const& ls2, Strategy const& strategy)
    {
        typedef typename distance_result
            <
                typename point_type<Linestring1>::type,
                typename point_type<Linestring2>::type,
                Strategy
            >::type result_type;
        typedef typename boost::range_size<Linestring1>::type size_type1;
        typedef typename boost::range_size<Linestring2>::type size_type2;


        boost::geometry::detail::throw_on_empty_input(ls1);
        boost::geometry::detail::throw_on_empty_input(ls2);

        size_type1 const a = boost::size(ls1);
        size_type2 const b = boost::size(ls2);


        //Coupling Matrix CoupMat(a,b,-1);
        coup_mat<size_type1,size_type2,result_type> coup_matrix(a,b);

        result_type const not_feasible = -100;
        //findin the Coupling Measure
        for (size_type1 i = 0 ; i < a ; i++ )
        {
            for(size_type2 j=0;j<b;j++)
            {
                result_type dis = strategy.apply(range::at(ls1,i), range::at(ls2,j));
                if(i==0 && j==0)
                    coup_matrix(i,j) = dis;
                else if(i==0 && j>0)
                    coup_matrix(i,j) =
                        (std::max)(coup_matrix(i,j-1), dis);
                else if(i>0 && j==0)
                    coup_matrix(i,j) =
                        (std::max)(coup_matrix(i-1,j), dis);
                else if(i>0 && j>0)
                    coup_matrix(i,j) =
                        (std::max)((std::min)(coup_matrix(i,j-1),
                                              (std::min)(coup_matrix(i-1,j),
                                                         coup_matrix(i-1,j-1))),
                                   dis);
                else
                    coup_matrix(i,j) = not_feasible;
            }
        }

        #ifdef BOOST_GEOMETRY_DEBUG_FRECHET_DISTANCE
        //Print CoupLing Matrix
        for(size_type i = 0; i <a; i++)
        {
            for(size_type j = 0; j <b; j++)
            std::cout << coup_matrix(i,j) << " ";
            std::cout << std::endl;
        }
        #endif

        return coup_matrix(a-1,b-1);
    }
};

}} // namespace detail::frechet_distance
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{
template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type
>
struct discrete_frechet_distance : not_implemented<Tag1, Tag2>
{};

template <typename Linestring1, typename Linestring2>
struct discrete_frechet_distance
    <
        Linestring1,
        Linestring2,
        linestring_tag,
        linestring_tag
    >
    : detail::discrete_frechet_distance::linestring_linestring
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Calculate discrete Frechet distance between two geometries (currently
       works for LineString-LineString) using specified strategy.
\ingroup discrete_frechet_distance
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy A type fulfilling a DistanceStrategy concept
\param geometry1 Input geometry
\param geometry2 Input geometry
\param strategy Distance strategy to be used to calculate Pt-Pt distance

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/discrete_frechet_distance.qbk]}

\qbk{
[heading Available Strategies]
\* [link geometry.reference.strategies.strategy_distance_pythagoras Pythagoras (cartesian)]
\* [link geometry.reference.strategies.strategy_distance_haversine Haversine (spherical)]
[/ \* more (currently extensions): Vincenty\, Andoyer (geographic) ]

[heading Example]
[discrete_frechet_distance_strategy]
[discrete_frechet_distance_strategy_output]
}
*/
template <typename Geometry1, typename Geometry2, typename Strategy>
inline typename distance_result
        <
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type,
            Strategy
        >::type
discrete_frechet_distance(Geometry1 const& geometry1,
                          Geometry2 const& geometry2,
                          Strategy const& strategy)
{
    return dispatch::discrete_frechet_distance
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
}

// Algorithm overload using default Pt-Pt distance strategy

/*!
\brief Calculate discrete Frechet distance between two geometries (currently
       work for LineString-LineString).
\ingroup discrete_frechet_distance
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 Input geometry
\param geometry2 Input geometry

\qbk{[include reference/algorithms/discrete_frechet_distance.qbk]}

\qbk{
[heading Example]
[discrete_frechet_distance]
[discrete_frechet_distance_output]
}
*/
template <typename Geometry1, typename Geometry2>
inline typename distance_result
        <
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type
        >::type
discrete_frechet_distance(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    typedef typename strategy::distance::services::default_strategy
              <
                  point_tag, point_tag,
                  typename point_type<Geometry1>::type,
                  typename point_type<Geometry2>::type
              >::type strategy_type;

    return discrete_frechet_distance(geometry1, geometry2, strategy_type());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISCRETE_FRECHET_DISTANCE_HPP

/* discrete_frechet_distance.hpp
opTJd5KQzVJj6N0uaiFbgip38YmUnWxJymSNkSXX2c9FllSwhy2xjhyxpSuTfpJlKpP8kWUrk/yR5SqT/JHlG6xQmeSPrNhQrkSZnMHISpVJXGgel4PNwrlLVqlM9h6yKmVy1iCrUSb9JLO87myyX5NZlcnYyWzKZO8h81L2nHfhJjY7mpq7vmBz1LoNJHMH2zrW1YctVJn/wpAzbOFYp1q3kWhqbUajYVzIYlR7bTpE17AlYDm1/pIMlmywVDTMLVk6mopnpurnL8HNomU9QLm5av3lK5PrLVmhstZf5U7g3BaDxai5W4KGew9ZKRruyWTlaLgnk1WiqTlYZbAaNDWvLW84G93niFnRMEcUFxsZ75/z/o3nvl692XykHJnaJ/zQ1P4SpEz2VrIQZTInyIYZ6hyjDPfkCEO5KDW+caHxDdjiwOaTbfMefR/bOqmTTI09BU21l4am+pmBpsaepUze90SWY6gzz9CXAjW+Xf3bnZd5DeUW4JwgK1Umz2bIypXJGiOrBItVdVahqTpr0LBO+t2Se9sWWgIgD1SHMvkuUjKbMvn8CpmXMvxuXjvYIrK8Jzr1YPM1WKCyHr2zmrAFo6m+hCqTz2mQhSnD7zoOVzYpNGYvW6SyXoe/T2SLVnZ476QythhlTSf+kV5rcZY4sMWW5Y7rCluCMsk7WZIyuV8hS1Ymc4Is1WDpyuT+jyzTYNmGfuYaLN9ghQYr1iavp9I9CVgc3geQlRqs3GCVBqsyWI3BLG/Wbda6jH63gS2hWMjzJTIvZXJ/RGZXhnX6KsPzZ6AyueaQBRvKhRosTNnaGyty2MKVyXM+skjDGKKV4Xk3Rhm8dm2JA1tKc0meS5ElKJMzO1lSneVmWpLB4i2zYT+zWFLBlqv35aWDraCf+BpYprLxOz7sypZtsFw09bm6fDT1vKeQzAY2Y3v8E2xnyTzAJi7/JontCtapP2Or6uzy3Gt3sVkPONuVDYt2sXmTYZ342TkfZ3PcW7D5QZ2P0M/2rYv92EKhXIIae5jBwtHUZwMjleFn9aKVfZheMZ8tBmyler4UR2YDC16W/zHbOiyn+plisDRl/75uz5ZhKJdlsByD5RmsAE09HyxSY3+y+sdP2EpVOXy/VLnBKg19qUJTa6XGUM7yFpj63KcVTOfWhqbmixcZjr3xd79eYfODcnp8QWCP0s/pp8ffzxaCpp5fD1OGr/uOMVgEmnqdOQpsFf18Le3vKWyzwBLV+5pj0dTz8nhl/75njy3RYOucDe4DaK2gqbikoaln2xloKn9ZhjpzDHXmKfv3fSVsBYaYFTmb49rPdsrQ3lk0eU9wrZWhqefsFWjqb1RdMZSrRlNz6aahTtc8MDXP3JXhZ7k9wHQevMF0/nzA9Bj8wPT8DFKG33cRgqY/522ocwyYzl+EYQxRyma+OyCNbZahL7Foan+JN1iisimXz7zKts7QXorB0gz5y1Dm17DxVrYsMD3PcgxjyDPMpQJDjoqUDVlxpYztFJp+Lw7YY+q6Uoamvt+mwmBXDFZtsJtoKi6uB+s2dzBdpweayoM3mB67j8H8wFarvS4ITfUzxGDD0PT6czZ4HkLrD03tE1GG9mYZ2otVtnf8c4PY4sHWqL//l4imXsNcB5akvrciBU2fFdHUuTVDGX7vTxaamhM5aOoeIU9Z329bt2ErQFPnrCLDGE6R8Vnqcfr573tf2crR1DmrWtl9RzYPZ7MecjbHe2Z5XoPpOgPJrGwq78HOBn+7i/4dmjrbhIGtVe8fDFfmceTFUrZINPU9WNHO5ngtki0GTX33W5yhLwlo6vqehKbWSjKaOtOmoqn3JKaDPaH2iUw0dd3MRlPrKNfZHK8=
*/
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
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
*/
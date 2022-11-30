// Boost.Geometry

// Copyright (c) 2018 Yaghyavardhan Singh Khangarot, Hyderabad, India.
// Contributed and/or modified by Yaghyavardhan Singh Khangarot,
//   as part of Google Summer of Code 2018 program.

// This file was modified by Oracle on 2018-2021.
// Modifications copyright (c) 2018-2021 Oracle and/or its affiliates.
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

#include <boost/geometry/algorithms/detail/dummy_geometries.hpp>
#include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/discrete_distance/cartesian.hpp>
#include <boost/geometry/strategies/discrete_distance/geographic.hpp>
#include <boost/geometry/strategies/discrete_distance/spherical.hpp>
#include <boost/geometry/strategies/distance_result.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace discrete_frechet_distance
{

// TODO: The implementation should calculate comparable distances

template <typename SizeType1, typename SizeType2, typename ResultType>
class coup_mat
{
public:
    coup_mat(SizeType1 w, SizeType2 h)
        : m_data(w * h,-1), m_width(w), m_height(h)
    {}

    ResultType & operator()(SizeType1 i, SizeType2 j)
    {
        BOOST_GEOMETRY_ASSERT(i < m_width && j < m_height);
        return m_data[j * m_width + i];
    }

private:
    std::vector<ResultType> m_data;
    SizeType1 m_width;
    SizeType2 m_height;
};

struct linestring_linestring
{
    template <typename Linestring1, typename Linestring2, typename Strategies>
    static inline auto apply(Linestring1 const& ls1, Linestring2 const& ls2,
                             Strategies const& strategies)
    {
        typedef typename distance_result
            <
                typename point_type<Linestring1>::type,
                typename point_type<Linestring2>::type,
                Strategies
            >::type result_type;
        typedef typename boost::range_size<Linestring1>::type size_type1;
        typedef typename boost::range_size<Linestring2>::type size_type2;

        boost::geometry::detail::throw_on_empty_input(ls1);
        boost::geometry::detail::throw_on_empty_input(ls2);

        // We can assume the inputs are not empty
        auto const strategy = strategies.distance(dummy_point(), dummy_point());

        size_type1 const a = boost::size(ls1);
        size_type2 const b = boost::size(ls2);

        //Coupling Matrix CoupMat(a,b,-1);
        coup_mat<size_type1, size_type2, result_type> coup_matrix(a, b);

        result_type const not_feasible = -100;
        //findin the Coupling Measure
        for (size_type1 i = 0 ; i < a ; i++ )
        {
            for (size_type2 j = 0 ; j < b ; j++ )
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


namespace resolve_strategy {

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct discrete_frechet_distance
{
    template <typename Geometry1, typename Geometry2>
    static inline auto apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Strategies const& strategies)
    {
        return dispatch::discrete_frechet_distance
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategies);
    }
};

template <typename Strategy>
struct discrete_frechet_distance<Strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline auto apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using strategies::discrete_distance::services::strategy_converter;
        return dispatch::discrete_frechet_distance
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct discrete_frechet_distance<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline auto apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             default_strategy const&)
    {
        typedef typename strategies::discrete_distance::services::default_strategy
            <
                Geometry1, Geometry2
            >::type strategies_type;

        return dispatch::discrete_frechet_distance
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategies_type());
    }
};

} // namespace resolve_strategy


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
inline auto discrete_frechet_distance(Geometry1 const& geometry1,
                                      Geometry2 const& geometry2,
                                      Strategy const& strategy)
{
    return resolve_strategy::discrete_frechet_distance
            <
                Strategy
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
inline auto discrete_frechet_distance(Geometry1 const& geometry1,
                                      Geometry2 const& geometry2)
{
    return resolve_strategy::discrete_frechet_distance
            <
                default_strategy
            >::apply(geometry1, geometry2, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISCRETE_FRECHET_DISTANCE_HPP

/* discrete_frechet_distance.hpp
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
*/
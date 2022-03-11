// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 1995, 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 1995 Maarten Hilferink, Amsterdam, the Netherlands

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_AGNOSTIC_SIMPLIFY_DOUGLAS_PEUCKER_HPP
#define BOOST_GEOMETRY_STRATEGY_AGNOSTIC_SIMPLIFY_DOUGLAS_PEUCKER_HPP


#include <cstddef>
#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
#include <iostream>
#endif
#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/distance.hpp>


#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
#include <boost/geometry/io/dsv/write.hpp>
#endif


namespace boost { namespace geometry
{

namespace strategy { namespace simplify
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

    /*!
        \brief Small wrapper around a point, with an extra member "included"
        \details
            It has a const-reference to the original point (so no copy here)
        \tparam the enclosed point type
    */
    template<typename Point>
    struct douglas_peucker_point
    {
        Point const& p;
        bool included;

        inline douglas_peucker_point(Point const& ap)
            : p(ap)
            , included(false)
        {}

        // Necessary for proper compilation
        inline douglas_peucker_point<Point> operator=(douglas_peucker_point<Point> const& )
        {
            return douglas_peucker_point<Point>(*this);
        }
    };

    template
    <
        typename Point,
        typename PointDistanceStrategy,
        typename LessCompare
            = std::less
                <
                    typename strategy::distance::services::return_type
                        <
                            PointDistanceStrategy,
                            Point, Point
                        >::type
                >
    >
    class douglas_peucker
        : LessCompare // for empty base optimization
    {
    public :

        // See also ticket 5954 https://svn.boost.org/trac/boost/ticket/5954
        // Comparable is currently not possible here because it has to be compared to the squared of max_distance, and more.
        // For now we have to take the real distance.
        typedef PointDistanceStrategy distance_strategy_type;
        // typedef typename strategy::distance::services::comparable_type<PointDistanceStrategy>::type distance_strategy_type;

        typedef typename strategy::distance::services::return_type
                         <
                             distance_strategy_type,
                             Point, Point
                         >::type distance_type;

        douglas_peucker()
        {}

        douglas_peucker(LessCompare const& less_compare)
            : LessCompare(less_compare)
        {}

    private :
        typedef detail::douglas_peucker_point<Point> dp_point_type;
        typedef typename std::vector<dp_point_type>::iterator iterator_type;


        LessCompare const& less() const
        {
            return *this;
        }

        inline void consider(iterator_type begin,
                             iterator_type end,
                             distance_type const& max_dist,
                             int& n,
                             distance_strategy_type const& ps_distance_strategy) const
        {
            std::size_t size = end - begin;

            // size must be at least 3
            // because we want to consider a candidate point in between
            if (size <= 2)
            {
#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
                if (begin != end)
                {
                    std::cout << "ignore between " << dsv(begin->p)
                        << " and " << dsv((end - 1)->p)
                        << " size=" << size << std::endl;
                }
                std::cout << "return because size=" << size << std::endl;
#endif
                return;
            }

            iterator_type last = end - 1;

#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
            std::cout << "find between " << dsv(begin->p)
                << " and " << dsv(last->p)
                << " size=" << size << std::endl;
#endif


            // Find most far point, compare to the current segment
            //geometry::segment<Point const> s(begin->p, last->p);
            distance_type md(-1.0); // any value < 0
            iterator_type candidate;
            for(iterator_type it = begin + 1; it != last; ++it)
            {
                distance_type dist = ps_distance_strategy.apply(it->p, begin->p, last->p);

#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
                std::cout << "consider " << dsv(it->p)
                    << " at " << double(dist)
                    << ((dist > max_dist) ? " maybe" : " no")
                    << std::endl;

#endif
                if ( less()(md, dist) )
                {
                    md = dist;
                    candidate = it;
                }
            }

            // If a point is found, set the include flag
            // and handle segments in between recursively
            if ( less()(max_dist, md) )
            {
#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
                std::cout << "use " << dsv(candidate->p) << std::endl;
#endif

                candidate->included = true;
                n++;

                consider(begin, candidate + 1, max_dist, n, ps_distance_strategy);
                consider(candidate, end, max_dist, n, ps_distance_strategy);
            }
        }


    public :

        template <typename Range, typename OutputIterator>
        inline OutputIterator apply(Range const& range,
                                    OutputIterator out,
                                    distance_type max_distance) const
        {
#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
                std::cout << "max distance: " << max_distance
                          << std::endl << std::endl;
#endif
            distance_strategy_type strategy;

            // Copy coordinates, a vector of references to all points
            std::vector<dp_point_type> ref_candidates(boost::begin(range),
                            boost::end(range));

            // Include first and last point of line,
            // they are always part of the line
            int n = 2;
            ref_candidates.front().included = true;
            ref_candidates.back().included = true;

            // Get points, recursively, including them if they are further away
            // than the specified distance
            consider(boost::begin(ref_candidates), boost::end(ref_candidates), max_distance, n, strategy);

            // Copy included elements to the output
            for(typename std::vector<dp_point_type>::const_iterator it
                            = boost::begin(ref_candidates);
                it != boost::end(ref_candidates);
                ++it)
            {
                if (it->included)
                {
                    // copy-coordinates does not work because OutputIterator
                    // does not model Point (??)
                    //geometry::convert(it->p, *out);
                    *out = it->p;
                    out++;
                }
            }
            return out;
        }

    };
}
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Implements the simplify algorithm.
\ingroup strategies
\details The douglas_peucker strategy simplifies a linestring, ring or
    vector of points using the well-known Douglas-Peucker algorithm.
\tparam Point the point type
\tparam PointDistanceStrategy point-segment distance strategy to be used
\note This strategy uses itself a point-segment-distance strategy which
    can be specified
\author Barend and Maarten, 1995/1996
\author Barend, revised for Generic Geometry Library, 2008
*/

/*
For the algorithm, see for example:
 - http://en.wikipedia.org/wiki/Ramer-Douglas-Peucker_algorithm
 - http://www2.dcs.hull.ac.uk/CISRG/projects/Royal-Inst/demos/dp.html
*/
template
<
    typename Point,
    typename PointDistanceStrategy
>
class douglas_peucker
{
public :

    typedef PointDistanceStrategy distance_strategy_type;

    typedef typename detail::douglas_peucker
        <
            Point,
            PointDistanceStrategy
        >::distance_type distance_type;

    template <typename Range, typename OutputIterator>
    static inline OutputIterator apply(Range const& range,
                                       OutputIterator out,
                                       distance_type const& max_distance)
    {
        namespace services = strategy::distance::services;

        typedef typename services::comparable_type
            <
                PointDistanceStrategy
            >::type comparable_distance_strategy_type;

        return detail::douglas_peucker
            <
                Point, comparable_distance_strategy_type
            >().apply(range, out,
                      services::result_from_distance
                          <
                              comparable_distance_strategy_type, Point, Point
                          >::apply(comparable_distance_strategy_type(),
                                   max_distance)
                      );
    }

};

}} // namespace strategy::simplify


namespace traits {

template <typename P>
struct point_type<geometry::strategy::simplify::detail::douglas_peucker_point<P> >
{
    typedef P type;
};

} // namespace traits


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_AGNOSTIC_SIMPLIFY_DOUGLAS_PEUCKER_HPP

/* simplify_douglas_peucker.hpp
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
*/
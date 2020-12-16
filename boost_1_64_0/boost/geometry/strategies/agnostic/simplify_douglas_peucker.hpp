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
2IRTdcFq9wdk24PqCITCQWdPgLJKq2yX116JNnX0wMv32ts9YbTr69qU8CZ7jZVoOq+TLbonH1e3i2heI+tryceX+rFzhc7ucdLlBVr5tlWjU8fxPUs6pyvo2efi3e3gCr0Y5IBLrM4Dy9PoaF4jZq3L5eNSPr5cT+9dU1ttf3tT406bskFhjFC0z9HtorRIQU6htwivjvHsWd+6xXKRvaFqRy37/U88W2hk5HBpXUPLBeV2UZPpOVflIzc+a2dePk/RX7hZyOc/5yokcIRa8f/Y3LDJ3ljdUttib25pqmt4u6KfkTVADGlm1yemlx6Q72Dz7ub2fFejcZZ76EeauKfcSb15u6mpa+K9MFKgc2Ev+bzGumBwnk60Y2KZxcF/FuQSo9cNO+zxddCr1Za2WJtqq2rswsdI63jVGVJk01+vpjjC/m5Ph9iJqFHVYQ6wckQRmEkn1tBrlpUT7PHZ/b4OjMARuX6xKXoRO5xvY71VtuB9Go2s+TqtxgMfEQzTDVqdOGB4XLCr3QW7vHQpRBcoM4Q5a2yqlXWcp9GwrWs06mpaq9Xl18+j6wu18n3DsrzSoF+xXCtmYR/WQGevvaMdZ2ltutjaO0TfXnyGtzC6vOOfXlY/xl49UtH8yjSsjQ63w+OjP5whbROnlZ2hRtVD/vaMZQYcQUc3veAM72GNdzp6vLDI9WdItaAXPsy7W6btqm2q23al3VbVVLVDJMNz+s+cYnf0hN12L2bZS9S5Mg8OJ/AMwuEo3uHPMgePNYaVxwhrE+epLgppPIVYqseei9VnFzqiryjvymN5T/tuHHGlx1mUeraO9ykxOYCq7kbW4VhEAU0NQnFQE3c7xBn91Io2EunX2mC9Yt1jI/DLBn1hqT04Trt8IY/fp87Op8SpUHR7j93rCKmGMLbslEqU1GpEh+kLBd7Bj8qbNCc76e0fLm3cut3u8zjLQ1hHf5I7MdohzyiLapzH55SMH/B62uktYi+Er+qQB2SqQFxmlcfN9l7lFboor3cqZxhV37G0EzhCvk3ySwZzh7kvTFHMEaut00+n1tQ2vL2uoVZk9mCAv7a6hj3IL0U/cJYuR1eIHsfOwTsJ8oUV5W1CxzsrTmTajYbGOE2WtUlj1XCPmCj4SEcYcxKipw3a2cOmrSyTEL1gdXVjwzY7YiGX3Ys6aa+YN8UZF9rlJ4ReFis1mOPHnoMsSuWqDv2FrRzLzyD6i4EN9gbCforntTi4RsQO9W3Re2l4wmlTlXpi4bPKLhEXMs6FRO9QYzgJYtdTYzgDEl2pxnDqI3q1iGG5h+DLOugN+ZjL6bpAUdF2RRfs2Ez1qmR3dzs6ROVElwgdDh8uh8y9jfOUK9GafGyzRabPKjPvQA2byisU1U8KNR3d9HCBpguaXy1pLpIlP5nXoIuK5plCDd46XaAR5fx4ee1KT+QQPlWQuzDtwbO+h7z09FnfRJwMyhh0wAq9Xo8j3216UaFe7Qa9Surdjg68b8EpwNu76QLLFrLJeXO5nDLfA7JWJ6L8BfUjVcPrkChTeHqAJqXRqPvw+YX7vLR95WvPXJgi7zBkEr1uWVqPT+p3qnqswqUd722qFn5rSVulvefJq/2sLdwzGwrOKaq2RePvUDS5OI5OyA9yejL/7SHe5Esieqc4wYglyHcx14u4cuTaDokbhBKIbuKzTgi9EyP4wYLTTk+3cu4LIV/ei6s7+Q+UNdsewodSh9tONL3860NUQqbC84MYef8e9ORdcq+pb2y8HAdnsdtgWlHqVVo9n8Cu1Oq4R5doytXu6fBgYTfa23WG/RdTRlet1MuGknNlCkYQpgcHFT7Ljh/oCQb8+CLcd5b0cLAHhho4cyo=
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_POINTS_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_POINTS_VIEW_HPP


#include <boost/range.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/geometry/core/exception.hpp>

namespace boost { namespace geometry
{

namespace detail
{

// Adapts pointer, on points, to a Boost.Range
template <typename Point, int MaxSize>
class points_view
{
    // Iterates over a series of points (indicated by pointer
    // to have it lightweight). Probably there is already an
    // equivalent of this within Boost. If so, TODO: use that one.
    // This used to be "box_iterator" and "segment_iterator".
    // ALTERNATIVE: use boost:array and its iterators
    struct points_iterator
        : public boost::iterator_facade
            <
                points_iterator,
                Point const,
                boost::random_access_traversal_tag
            >
    {
        // Constructor: Begin iterator
        inline points_iterator(Point const* p)
            : m_points(p)
            , m_index(0)
        {}

        // Constructor: End iterator
        inline points_iterator(Point const* p, bool)
            : m_points(p)
            , m_index(MaxSize)
        {}

        // Constructor: default (for Range Concept checking).
        inline points_iterator()
            : m_points(NULL)
            , m_index(MaxSize)
        {}

        typedef std::ptrdiff_t difference_type;

    private:
        friend class boost::iterator_core_access;

        inline Point const& dereference() const
        {
            if (m_index >= 0 && m_index < MaxSize)
            {
                return m_points[m_index];
            }

            // If it index larger (or smaller) return first point
            // (assuming initialized)
            return m_points[0];
        }

        inline bool equal(points_iterator const& other) const
        {
            return other.m_index == this->m_index;
        }

        inline void increment()
        {
            m_index++;
        }

        inline void decrement()
        {
            m_index--;
        }

        inline difference_type distance_to(points_iterator const& other) const
        {
            return other.m_index - this->m_index;
        }

        inline void advance(difference_type n)
        {
            m_index += n;
        }

        Point const* m_points;
        difference_type m_index;
    };

public :

    typedef points_iterator const_iterator;
    typedef points_iterator iterator; // must be defined

    const_iterator begin() const { return const_iterator(m_points); }
    const_iterator end() const { return const_iterator(m_points, true); }

    // It may NOT be used non-const, so commented:
    //iterator begin() { return m_begin; }
    //iterator end() { return m_end; }

protected :

    template <typename CopyPolicy>
    explicit points_view(CopyPolicy const& copy)
    {
       copy.apply(m_points);
    }

private :
    // Copy points here - box might define them otherwise
    Point m_points[MaxSize];
};

}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_POINTS_VIEW_HPP

/* points_view.hpp
tnlFjsV/z2yykGXBUmPf0NbZ2OpG+fhWzIKMpx95BF7vtCpL0D4I6fz90w84dP/dqadP4i7ETh4/kPPGNeVd8KePyvtpgsgFnf9x1UuY4pTjUJk3Vd6JlWujI2G49+bnz95DezWUgSv7/h0Kv00WFsczEhbWFhqArkVAs5i18WzqReRNB2KReng40l1Fsl/nJuytuYnjC99wdJWm7Z6ngI/iiuz2WvJm8Gc5Mv8MGrQIspPYmky6kwyTVa/fw7U7WAfQZu+aXWBkR41NS9X7xb/PGrBqKq6cTEpxU9CMpHmotmrufG3vHtsYY448xL7Uk6h8Hxy5u+o+DHXVVw2od9aoWdfvie3CMnEy8yrfSFE7HukMhJQF2528Hm9Ffe+VY8wxztUs/SRB7vh1zvbw9xp2RmZWm9/dG7sV7GozC0yGmM6el9MiWs6vFvEYXgb/6iWfMGOAzW+u75y2z9HNKELe8HTQhNlXSyDq4Aa5biZf0BnXma0t+M2J1Oi1JROk2sa2pA4eGqbidOfQ2w8aDZ0e6dZOjU0Y5UcOMpVmrRVgWz9ZomLFYzFcvVtWA5YAkz4ViWet43tua7oI7bOg/baaJDHmCEAAtovbrfbghhtFca80W0O01S6K2KuGRZG56lcsCtv/hxb15cAf
*/
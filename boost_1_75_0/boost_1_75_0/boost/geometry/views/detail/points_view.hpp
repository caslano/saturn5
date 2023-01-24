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
t4l++A68Jk++nnEtrT87Wn/3Yz81aR6K7oNRb/4Bsqjuysxo9nnnQjTl5+bElALa0Y2y3m1iKfl3fUqCcfVTtrfAloD5MhD+IWRbT2pes/Q9qLog58nAHS7WLA+aKgPIPEpnC2pIFLLdYCo+2iiWikV0M8BRYhF/WQZMUQgNWbFq5D++K5bLTR75bF0ThUMbjXf+nptdoTtVik/ahDNphlPO1lqhxFfN9p28e8vojk/Bj0+Ja4Tdr7hKLw95Cwt35zW3wUSFhc++Fs8YtzS2Gxn9Qbeq89/RjXo2/LU27ZfzQuP43PdCY6Exe0up8mLFJ5QEbxOQwWoas8EEzULxQL7Drz1/B4f70KIhbw7ZRTuSBZjaIDgj2YWELlf/6kfcDNYVi5yz6pCGUZas0dz86YJeiYHNAHv0MXoh/MujmW/P00Eux77npyEIfYmurR8Wv4h95Ol+fWZZwfLljaL4qTrnA8LfAsRQ8bG4n4CthuUixXJEPFGt2ZP1gGbUG+fyMygMaqy9UTs40FQleE+qHev0Gfce489jaXexHgoVleEMvgqwz3WN5EDmJa+v+ume94kC9uzufY2MDnNWmDXr7Ku2nfwZBF1/d36Dj2iigag4mL/LbJdIC+TO6S9weAeZtdQIvio2joEofCTZm361+nS1frLpIJPXeVtbSQsRP1b3iKy3KMu0w/mbtnuaVkU5sOovEH+0zVlPG1hX
*/
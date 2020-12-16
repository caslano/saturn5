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
MdIqaIBOPvfy3a9myOc7Px0VE0L1MAQD+5E3z0uggOf9fGc5RJrL59E76CvXiZQxgy9qLKatY3znqov71XwuhCzYcTvygZ6PT2C/ljE4J9gv74Dw/nM990Z5lhCum/Ir15GPstL5nFg2IbQcMqAbRqHyMDIkbYTY9YwvLIYivuSRDdX8Tr2HzyNQA82QuYA+kM4ooY5C5AC911EGhIoodx75FyHDr6HL0Pxe3vkhbeC75+k5yKIhvGdFHt6bsYp3uV+4O4g72rmOX8j4h/cruQ7HJF0fpJ2QsDuIVZq4LuFZB+Xkkw7xOZ60AarCcL8BsqGDcopIy+/icxxtgrZ05EB7CtcHe7EjUH4mCvcK9HYqPuUi6ofki4O/tVXPCv621DAHXU2jXQ+F76P3l6BLkMlv5pOgAGLD8KyY+zUwld+Nl/I5FULheCocl91JvyfSHiiEamiGXgj5XZhsKIIaaIEBiJuEDkI+lEHqL3jvAO25nXf496IGqbuFsoviwnXRHmypFfk3+v2XEUg4g3GA5VAJjdANQxAf/n4Lr2ZD7OvRNcoLf2clC4qgCbphCBIm0xYogCrohiG/b5IJBVAFLdAH4e+LVEIbxMXTdsiHSmiGMUjx+x0N0A3h71+kQh5UQAN0wSjM8DsVpVAxjXqgHxLOob3QBH0Qfy7tgQJohX6YmsC7UAEN0AOx06kf8qACmiDhfMYGWqEXxiA57CBfRTmvRhcuol6YkUQdUA710Aq9EP7bbzrkQxnUQAv0wCgk+jfdEqiGfhiFpEspDwqhClqhF8ZgRjJth2pohV4Yg/DfWxdDMbRAH4ReQ58gD8qhAXr9u+kMKIFqaIJuGIbEFOQHhVAFTdADY5A4m3ZBPlRAD4zCjNeRH1og/DfHXgilIitYDMVQDY3QAcPh+3MoH7pgAMYgER+WBrlQDkMw1b/35UIZ1EIzdMMwJKQhQ8iDUmiHAQj/vS4N8qEN+mAUki9HflAE1dABAzDVv6kth0pohA4YgnT//pU3j/GFThiA2PnIF3KgCMYg/PekHhiGhAWIAdrx22MH6BP21AH9fG7HL+S2Iyvux86KwX6RWdgvYq/xv6d+nncfpU98rua6ANKh7yHq+wX34ujbxdSZRH8SkTHUQQcMwYwLyAelUA89kPoq+gCJV9JXKIRqaIY+iMsgD+RBJYS/61cFzdADo2cG3y9LxYb7oTc++M5VwispDwqhBlqhH8LfaxqB5GmUCTVhW8SGKmhDPXTCMMzAlrKgCGqhDeJnkBdKoBbaYABK/M5IOwz6XZF0KA7bxeuCv20WQBW0QCm/nyy+k7rDhMcAmdVDFwxDK2PWC7GUlQyLoS38t/I59BMKoRaZ1z9D3w+Tn+tErke4TqLMEq6zw3Ddyb2Gu2jbE7z7OO2ATghBD2NWS1pMWg/F5Kk5SJ+gAEI9tJc0Fup4lkbawr08SOBzJWkmaR9pKuT/hHZAqJM6SWtIM0i7oDx8n3b0NgL3k37Iu7uRCSwOz5+kY9zrJe0Ofw5fQ1IDeUgbeS9uD22AHe3IEPK4Vwkp38IWKbvim7QPZnAvjzQFBqGdZyOQx7tt5B0jHf02dsX1EHTzuZq0gbSU+42QAOV8zibthrjVwd5YH1RDMxRBPfrXBWVTGIeZcBPXroEbtyEKGIblSbz3OkQKBRu4hvD+QelG0tJgj6HgBu5DG+S6ps8Jr715VnljsG6v414h1yGuk9w/GITWEuRJvjzSEJRAbfgeJEMf77VBHIzyOXED1zfQPvcYerk3xOcZK4K9z1zSQdKxCegy/cuHvunogt9tK4AqaIZ+yPc7USP0b6rfAcmF0DzGAcJ/Ry9cSFlQC9n7g78vF5A=
*/
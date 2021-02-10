// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_CLOSEABLE_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_CLOSEABLE_VIEW_HPP


#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/iterators/closing_iterator.hpp>

#include <boost/geometry/views/identity_view.hpp>

namespace boost { namespace geometry
{

// Silence warning C4512: assignment operator could not be generated
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4512)
#endif

#ifndef DOXYGEN_NO_DETAIL

namespace detail
{

template <typename Range>
struct closing_view
{
    // Keep this explicit, important for nested views/ranges
    explicit inline closing_view(Range& r)
        : m_range(r)
    {}

    typedef closing_iterator<Range> iterator;
    typedef closing_iterator<Range const> const_iterator;

    inline const_iterator begin() const { return const_iterator(m_range); }
    inline const_iterator end() const { return const_iterator(m_range, true); }

    inline iterator begin() { return iterator(m_range); }
    inline iterator end() { return iterator(m_range, true); }
private :
    Range& m_range;
};

}

#endif // DOXYGEN_NO_DETAIL


/*!
\brief View on a range, either closing it or leaving it as it is
\details The closeable_view is used internally by the library to handle all rings,
    either closed or open, the same way. The default method is closed, all
    algorithms process rings as if they are closed. Therefore, if they are opened,
    a view is created which closes them.
    The closeable_view might be used by library users, but its main purpose is
    internally.
\tparam Range Original range
\tparam Close Specifies if it the range is closed, if so, nothing will happen.
    If it is open, it will iterate the first point after the last point.
\ingroup views
*/
template <typename Range, closure_selector Close>
struct closeable_view {};


#ifndef DOXYGEN_NO_SPECIALIZATIONS

template <typename Range>
struct closeable_view<Range, closed>
{
    typedef identity_view<Range> type;
};


template <typename Range>
struct closeable_view<Range, open>
{
    typedef detail::closing_view<Range> type;
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_CLOSEABLE_VIEW_HPP

/* closeable_view.hpp
AuFPACEuGJtyPkfjkcfBsgztki/QbgtIOUbNB9Yy8cQ4brPOioND2ab7qp+XSdgfWiSKsxeUYD+ya06ltpqmHxOmKnFeSE4tcqCFxMHH6Y7tVtif7yMQBliV3LHGRKNOx+6ERMbYcTtg+4Q4c+Wv4iYlhBySkKRVk3iULEXTKl0USxihN5InmnxyBwGi6SopmZIR1xeMlTYpE3RXQWu7uy1Rg1ovSKL+/Il5UWAN9f323WCITpGKwF7RZdBbZWleeWjTCclLaeLkaoPuOyN0abwk0l3ou2k6SfZQcI67uYsr3iVft3SEcauqm1oRpVq3/ibyu8JFm59m0QSF3hyT9aKZgfFcJ8c5duK8JE8q7wCYjCTsVE9VoISpNM3ZHWxsafAK0FW6esC3jdXAjsuCN6vMdXTV4TarfXkkPHm96aq6J3YfbJhhdW7ikOOsFveflM8Ez57ED+EC7uRHDgtHbmd7tH9wMxMM5gwbRRQ4QVOiVdDk7kjBhEkDgKCTksujIdDP+v2o1wdsxfsu3if+cfpSWp+38iGL72mawWgv1MN/LYnJCseol0n/2UhqYVp8bmh1B6gOMNEDFqrUSA99V4ignTZUD3qrejNqdy+MSuRs/N4imcYuqm30usEwlD7kmi67r8+Gvc6w+2X9
*/
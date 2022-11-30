// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_CLOSEABLE_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_CLOSEABLE_VIEW_HPP

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/iterators/closing_iterator.hpp>

#include <boost/geometry/views/identity_view.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Range>
struct closing_view
{
    using iterator = closing_iterator<Range const>;
    using const_iterator = closing_iterator<Range const>;

    // Keep this explicit, important for nested views/ranges
    explicit inline closing_view(Range const& r)
        : m_begin(r)
        , m_end(r, true)
    {}

    inline const_iterator begin() const { return m_begin; }
    inline const_iterator end() const { return m_end; }

private:
    const_iterator m_begin;
    const_iterator m_end;
};


template
<
    typename Range,
    closure_selector Close = geometry::closure<Range>::value
>
struct closed_view
    : identity_view<Range>
{
    explicit inline closed_view(Range const& r)
        : identity_view<Range const>(r)
    {}
};

template <typename Range>
struct closed_view<Range, open>
    : closing_view<Range>
{
    explicit inline closed_view(Range const& r)
        : closing_view<Range const>(r)
    {}
};


} // namespace detail
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
    using type = identity_view<Range>;
};


template <typename Range>
struct closeable_view<Range, open>
{
    using type = detail::closing_view<Range>;
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename Range, closure_selector Close>
struct tag<detail::closed_view<Range, Close> >
    : geometry::tag<Range>
{};

template <typename Range, closure_selector Close>
struct point_order<detail::closed_view<Range, Close> >
    : geometry::point_order<Range>
{};

template <typename Range, closure_selector Close>
struct closure<detail::closed_view<Range, Close> >
{
    static const closure_selector value = closed;
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_CLOSEABLE_VIEW_HPP

/* closeable_view.hpp
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
*/
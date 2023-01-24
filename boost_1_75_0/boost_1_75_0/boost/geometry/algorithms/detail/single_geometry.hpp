// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014.
// Modifications copyright (c) 2013-2014, Oracle and/or its affiliates.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SINGLE_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SINGLE_GEOMETRY_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/util/range.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch {

// Returns single geometry by Id
// for single geometries returns the geometry itself
template <typename Geometry,
          bool IsMulti = boost::is_base_of
                            <
                                multi_tag,
                                typename geometry::tag<Geometry>::type
                            >::value
>
struct single_geometry
{
    typedef Geometry & return_type;

    template <typename Id>
    static inline return_type apply(Geometry & g, Id const& ) { return g; }
};

// for multi geometries returns one of the stored single geometries
template <typename Geometry>
struct single_geometry<Geometry, true>
{
    typedef typename boost::range_reference<Geometry>::type return_type;

    template <typename Id>
    static inline return_type apply(Geometry & g, Id const& id)
    {
        BOOST_GEOMETRY_ASSERT(id.multi_index >= 0);
        typedef typename boost::range_size<Geometry>::type size_type;
        return range::at(g, static_cast<size_type>(id.multi_index));
    }
};

} // namespace detail_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail {

template <typename Geometry>
struct single_geometry_return_type
{
    typedef typename detail_dispatch::single_geometry<Geometry>::return_type type;
};

template <typename Geometry, typename Id>
inline
typename single_geometry_return_type<Geometry>::type
single_geometry(Geometry & geometry, Id const& id)
{
    return detail_dispatch::single_geometry<Geometry>::apply(geometry, id);
}

template <typename Geometry, typename Id>
inline
typename single_geometry_return_type<Geometry const>::type
single_geometry(Geometry const& geometry, Id const& id)
{
    return detail_dispatch::single_geometry<Geometry const>::apply(geometry, id);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SINGLE_GEOMETRY_HPP

/* single_geometry.hpp
gfcbTWq+nHBPhA886BvJPjAmPnBKig9EKGVMS3WQuf4DEYc0epBtvWTfNsMyoatk62XxIOdeMFgJPouPE78UJCPlPCVCgUIjciZmA6oMj4GVaQt7f6dYao2DBF/5CBBPDOLzZZOt8OHvedFHshzG22UUxUexOV+BJ7afFdsGiblyCYgPIUWjYRODtS0/UVpRLREioSjbbDT4gxTVH02Kcptfh9Z+EYtcS3YiG40wXS5bZ/fMRltd7m3kPmkMiSrVNCg68UlMYMntEoEvhblht0usjor1ai4QGyHti7KzlpA7WFIWE9B0s7CVYTK2R9hBqzlqjfcHoUb3ZOQ0kkJpjFyvlMujpfdhcI/U9qhzyBRaI47kI+uaGMex1PqfqDgDpn87jD6GNDIWRlW8XtuTxggll+B1eeqwbLTShkZaPR0vwYbtC/jgMH1GuDzsBD+WceMzy2+LH2ktUcqIJFirdeRdIkpwMZej6hEZ0zMMm9uXKKzBfN4Cra0+bdGhZKQm9p/hJAFfsZ7w+mvbNZlougbfbBTE+8GfwrGVEfiDKscPjSUNAKbja8OSMYtG4D1WJoRrhiU3uiU4UQS9MmTbYQKzDuZnhVqrjJG3aQdhJ1ksRTxhb9hX4J+BE/7HA0eC8UB1jj+3ILIOxyKvR1fGWgtW4GhBSf7YvECsITeaMy9Q6yukIZ0S5QWx/Avx/PymovHFJSUTSOnost0j
*/
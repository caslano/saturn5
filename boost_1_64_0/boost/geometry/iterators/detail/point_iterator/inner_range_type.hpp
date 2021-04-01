// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_INNER_RANGE_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_INNER_RANGE_TYPE_HPP

#include <boost/range.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_iterator
{


template
<
    typename Geometry, 
    typename Tag = typename tag<Geometry>::type
>
struct inner_range_type
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Geometry>::type::value,
            typename boost::range_value<Geometry>::type,
            typename boost::range_value<Geometry>::type const
        >::type type;
};


template <typename Polygon>
struct inner_range_type<Polygon, polygon_tag>
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Polygon>::type::value,
            typename geometry::ring_type<Polygon>::type,
            typename geometry::ring_type<Polygon>::type const
        >::type type;
};


}} // namespace detail::point_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_INNER_RANGE_TYPE_HPP

/* inner_range_type.hpp
q4Yaoon7Sf+zgO+inb/1krlMI0+vTSfp9CarJePRaolr0z3dNTLghsVLac8kIaKTbrwUoi/puUjF+M6VUl3lx5pvScIKQ7GT0sOq40AhBQboZGX+jZJm7YdwPIyAQvxW0XW5CTKKpvYP9uMqZBDLd7xJbQwL+Q07FFNSBq3NfJZEuytDwv7KnGUWmqhV0sKE515un3ohZqi1duUaHNV272DQON3ueCrmIWBhK2kOUxat2Esc1bS/yMDQnwmG63vl+ni2Gvqfy7uNv9bVuxbcrPU43egJdLQtgGAmH9BryoigXPhVLVV41pyqmEYvIi73/N9O2h7EVpFjtd3fv6qbFTIjYENjJolZ0XTPWLTIUHVBPcimw/IyaOUwjJLiz1VT/hhGWP70evrcQ8OlgH44WE/WHLrJb0iLgOL/oUPRnbJZgdYiEJxv6aZd/l5bPbsBMJkLADeIkdg4WR6byO9CYicBDuYPLVz+oOIhlq4WgFFLhB+6jBoI7/3pbigSc+M4mKjTdjjpFZsLRr0/GnddQ0kVKYQ0sreT31fx9OgNGixEkhKbWw4lR7Wmzg==
*/
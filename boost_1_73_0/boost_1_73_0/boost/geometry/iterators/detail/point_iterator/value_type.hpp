// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP

#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_iterator
{


template <typename Geometry>
struct value_type
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Geometry>::type::value,
            typename geometry::point_type<Geometry>::type,
            typename geometry::point_type<Geometry>::type const
        >::type type;
};


}} // namespace detail::point_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_VALUE_TYPE_HPP

/* value_type.hpp
onzZnVPnYTU1sUUCjUZfv27ARwd/3GdPHIgHPwH9H8AHftKM6yL7p4zK5tFB8Lvg/2DWV/j50CJHoprye9AWD0/5XbRoSqBXeYO/B8FDC31F3vCfI5z5NcBf4QlMw5mnWX5XxItlKVqnbfHyb3/7H9EVr45fveyIszCNZSLGpUynslh0xJsZPfnHMvz2rafk246QpQiTniY1WcZKqGxebsJCCvg9iSOZKjkToRIzqaIinsKXOBXlUop5nEhxenX95fzyQ0dslnG0RCJ32VqoZbZOZmIZ3kpRyEjGt0wjD4tSZHOYDsRnsSqB4LqMs7QHa0tRymKlkAYuHyYqE+FtGCfhFBYKS7Esy1y9PjqK1kUC3B/NskgdRWb7vWW5sjv5AkyswjuR5aUoM7FWsiNwZEesslk8x58gEHiYr6dJrJadihtYKp0dZYVQMkmQFsyLpWK2pRhr8XRwmMiB47jEHypLFS61WWYrbyDIEanM10UKC4EcYNAsAzF3xDqdyYIG087NElqmJOCdqqn4nYksBWbE/mAszsf7YhqqWHXE5/PJD1efJuLzYDQaXE6+iKv3YnD5BYn9eH55BqqPYbFCyG95IRUsXoh4lSexnJk1hXiRx+kiz9LFC1xyDkMWMpVFHMEi0U0XJNCFh+VS
*/
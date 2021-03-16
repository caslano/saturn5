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
BhUIXzOkjbUTh/LwecYnfLqCTzgqY+3BOjVdMetUJ2PhG9YnYLE+8RTQHZp1BWhTRBVph9xk8BtUufnkJlUuV7tDlTtH3Al4JeCfVLn5+59Vuekk3MXoBsB7APEJ+4sq90O6DxAnD/8KiOtAoMLRMrW/A54E/AcgPmWPqnJ52mOA6YCPAw7H9glwnMHjluIzNelmsxuOcVTjDUBs/Q4C4jK9Q4C4y8O7gDi9/R7gs4DQYYzip7KeB9wF+AwgOsI=
*/
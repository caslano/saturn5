// Boost.Geometry

// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP

#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/interior_type.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
\brief Structure defining the type of interior rings iterator
\note If the Geometry is const, const iterator is defined.
\tparam Geometry \tparam_geometry
 */
template <typename Geometry>
struct interior_iterator
{
    typedef typename boost::range_iterator
        <
            typename geometry::interior_type<Geometry>::type        
        >::type type;
};

template <typename BaseT, typename T>
struct copy_const
{
    typedef T type;
};

template <typename BaseT, typename T>
struct copy_const<BaseT const, T>
{
    typedef T const type;
};

template <typename Geometry>
struct interior_ring_iterator
{
    typedef typename boost::range_iterator
        <
            typename copy_const
                <
                    typename geometry::interior_type<Geometry>::type,
                    typename boost::range_value
                        <
                            typename geometry::interior_type<Geometry>::type
                        >::type
                >::type
        >::type type;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP

/* interior_iterator.hpp
qzjwaXP+Kp4fAsT3xfPD/up8fishIYIPsrnQqV1qzOfvAWK5eH5hp+eP4EU4xbPN5rN7gfidePZQ53dj6QYej4qwiaEVQJ54f+RJ8zqwZDr+KuIg3ARiwFXgZa4m7ZLEes6Wq8q1fBljvwj8h6sWS/IwtPqEjMAHGC8nedIMMlkuVWco9dD4a9B8KUfNUUyd8P+BL2i8KviC1UCkf0T1iDb1H8dA5iIcC1nXtqcLtVVDLWduWgok1HQv4wEarrCFuaEofi4dmB+6YFh6L8E62HmP8lEYN5GJSlSboc8GfqdBC6gR5W7sCXvvxsE7cTiac184EgwEIv6lSkSuxHE0JxyAbbs4GNZhc8U0pE1Myc3Rg3x+58D8hjme5u8yvxfAZ75G+2EZEPsgnfiIYnXTirbkK7bjiYim6brwDs/xnQ7LyuGPksu4+7ZsFHieZGP5JlbWyglpDN6hHdYnahW4HFVIHgYyyuUX3riP4XB0xhaV/xZCK2kfZALxr3+jfCPj64ssM7o2G4hYc5dTiIMVwoXjMI4DHzRDqVXbtYi+XDuMfdoRI+qeZ0So97NcA6eUMW5dCyIeeC0I3HdQQ9nf6YVy60eg3JpSlBv/HspNS3QZLwehegfo/n0MiIF/p7FJbeNgOuftpjt2cw6OeTmpOOAc4nzbGDjhsiMuc+CTy47htsRV/hneQXZKC7GcA/X91KUd1CPAzNX7Tvtj
*/
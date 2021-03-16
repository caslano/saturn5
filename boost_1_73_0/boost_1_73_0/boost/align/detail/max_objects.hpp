/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_OBJECTS_HPP
#define BOOST_ALIGN_DETAIL_MAX_OBJECTS_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct max_objects
    : integral_constant<std::size_t,
        ~static_cast<std::size_t>(0) / sizeof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_objects.hpp
pm4B1S9Hu5fk+WZhfhkf7iR6r1BnfHmUDrIb5MppbWkNVbGsqqHK3LiOUma6eCATpfg7JT5igdNduZYa0zb669K4reHndgHaTUuBkJzoCGwSdkAdzjbMMIgy0LqKFf/GuAtJSgSV9ikO40y7Y+KlNQqfcwctZTNVUORSXA11NZFQ++ZqJKo9OM1LHLtolQ83Kq+4bVQUBW5l1/W3lRUNQW12v2XsKR6ZQliV/qRxOFtvst10wg67wrFeapsn2qM=
*/
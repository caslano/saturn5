/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_MSVC_HPP

#include <boost/align/detail/min_size.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct offset_value {
    T first;
    char value;
    T second;
};

template<class T>
struct alignment_of
    : min_size<sizeof(T), sizeof(offset_value<T>) - (sizeof(T) << 1)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_msvc.hpp
VbtUNMJGi5JIQsUtoEgU9l/pWb+FHLV4fNoLDW/wli6pxD7wV7IsSPwNJNZXllYICNk8D1B1wyLo/9rlAh4O8LU5wD3U2ba+uQMkPT3rY6wIutbpJAOUhez2Abi8tn6JyDcWoH9Uy7bK5zuAFhn8HRLWdIp7BQhib72ADECEZR0zRUnllfX+QN2SypVUzH6YO9aT76Cl07NOBdUaWcufh6+qWVhLp0bwFi4f3tGUWrekvOEYK2UMpAwdyRg+rQU=
*/
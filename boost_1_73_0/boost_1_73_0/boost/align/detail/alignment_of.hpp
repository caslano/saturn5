/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_HPP

#include <boost/align/detail/min_size.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct offset_value {
    char value;
    T object;
};

template<class T>
struct alignment_of
    : min_size<sizeof(T), sizeof(offset_value<T>) - sizeof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of.hpp
d0dL//x+B39PAd31rf3z+33rwPh9AXS/Dibn1wfjdhBo4fNW8+uDE/ALg4Ie1g7jfAq/npCA33vwF1vLWHsHvx6SgN84GN+7gOZJkXNUAn6joH47uhm7MZyc36dA9x7QvNbDr7MT8MP5EY8w4+fGjwG/W4Hu1ii/TCTPzwLdV0CzZz2/HpGA31vQ3mUbGCs+lV9PSsBvLPBrOQ1k/3R+nWi+pQK/94DmwzP59ZgE/F6Hv6fPAp0V49dpCfhdC+U=
*/
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
0r/yegL3PbvYCX/Wp/4LrP3vQ3vnq2X14Ouz3LgOa/khPp6N+H0VYKz7Ah5UV/EzPTpAVhC+A6bGs9U8DePhivQiNDwYGPsNjDmieQnfZQPjQcxPw464IgFNy4A+PTB4Rl3l3XLvgFemW8/4fXRs7L/lRcaz+Pn9qqQTab29ayzNA68Pjo2l+ez/RCYjE9yfed3/GfDx354JX6Dj/jdQn3sNBRoHNiw3fZrsrZExP9WI6oKf4GW+Vts+++tv+MC1Vv5jg/U3uud6oMb/znGaz6on8/trXGneEwlyX+/BKeh11RP89A2+76kmX++/gYLwhdV/wdP/BWcCjUWblpsCLPfW5og/DECvBH0iZ7tteU9yyH0iNpVW/ouD9Sr653r5zbcXyf8F07G8v5aE/hdId/UG+Noqzzjx+pQuQLL8RwcD9VmVxXk0/O2d+CGBwj49/JFoeajUcyGux3/lEg5u+58njcHO3E6dmOoHGwivZhMUETV77qJW1LBL9uXyst83IjGwztER527jARoiCrwZ87Fqjz8ZoiYbGToTQUJa1GyIH7RegX3/TlQ/+7Ufl45O8zBgzIJRUmLZRNZJjw2RFb5X1b8KZDvabeMH/wiegaabdGXXzPe2ao6n+xRMV+CuyaDVwJ+biL3qrbI4de9PNnUBkhv/2O6ojx7ENgp5RgEgpWivqFsVa+VZxlSa/uL6JhNyT6j9bdJVP5Kh
*/
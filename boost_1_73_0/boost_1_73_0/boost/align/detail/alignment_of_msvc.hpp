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
EosVH0Kw7Z2TabiRcbjzxRZ4yvAU6wyibweSBcsp6tTqkl0bDtjY26PihPWffvP+4jJk9AsN4LJiGlaWtmDPQ6VgbTXnSmNcBGdhqlfSKE0h8DzbfiI4+kYU0BnyGBRE87UBYLPeRUofSPw0RdHrYESrY8+TlGW/fb3/+3tz/HYsn3Lfoag2MGPB53576O++Pj9+9bttE/SgRX5Aoauqvv2AC/gh/yAkhXnRH+gnGm//Hh60344Pf2/7hLnPq/654U0THhwweWIxppC9ireb/oMmFLvO1Bs1CiUHqNdGkzqzwDNdWu9dFe8tzVflqIdT4JJsPj0+XZuTg6dJs2ayBrjWwZTU9MWj2X/6WNnV154rpfwjPKFBgjFtPvdI4FmsrV2RsQ6iWOoOOksc3D7+7uQyO3r38vhCrQbHyfChYNQcrheLkMa4aKcKMuJHjgrNceFctDPcUCYIEXCQKFbWcXDa6AlE1lJoFhhH8vI0EAKWonuyvD9rxnZsLo92EVbOQ/kbIamFqxQeKhSgMi65yTXYVOwqFzhB2X6mB5I4eRl4REqufSqZaGZ2b2+5HaqCp6p2+3UoaOAFUOn9ua3ZQErv0mXizG068/3mn+py5kmE5MjDjk2hwrRGsTYabbGar9dzVheIJvfg+Z1l
*/
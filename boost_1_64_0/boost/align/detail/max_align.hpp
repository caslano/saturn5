/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP
#define BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP

#include <boost/align/detail/max_size.hpp>
#include <boost/align/alignment_of.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class A, class B>
struct max_align
    : max_size<alignment_of<A>::value, alignment_of<B>::value> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_align.hpp
1gWkCvcO822RpMfN4NPYecsV3Rlkie+XzsBR15UR5ynnH8GT6Y4jEZu/i6fcZkWkwNlz21XO9GvX2aShtaYLe9v95tJHwjXb5tg242JeA9u8KSnl5DgnzI4WEQapeUTmbEITKsJOslbd75AFkgXdS+Er+uH2wV/YVJALAPyLIVgC+D0bIGfycWTOKAseLt6fmCq0Krkue91EeM59iP3OSG+B81kykKVrA6sUZ61S1p9Rg0UZHKvhaD6KvLUr0zkadM3eMvwdYOW25nC9FrPrKZcvapxzxaTkJjKRvwxe1i0Q5LJD6dnvbdVqlJv/sqYvN5DN3nYrmIKhXMU2abIhi3kiMGKKJUdY+68iuoCEc6V2frgGxTTGahz/7E5AZLo/BmeB1BH8KWPffLPXrh75Ewpl1GyGABqh/yBPx9OJGsTBSdV05nlXG4WYud6Dh086euUyGKtX6+OKQ5N7HZofYqhCVlJxUi8c07yIiBd0YsnQP4IBYNQAMrJ6nqXeibgvngUDCO1TkXLXfEBuNPZEaSMSyFlTD7cq8m9avBRdIiHdrHCRu2mEq2/0Ig==
*/
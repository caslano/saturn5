/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_codegear.hpp
B7p3B8Av9RxYH86x0bnwKwaaMjudy3xrAprwAPhdADRXD4Dfg+cw45dQ/oDut/3wGwd/nwFNxjYbnQu/qUBTZKdzqV890LQMgF8MaM4fAL/btzHjl4jfw0D3VD/8cP19B2nOtdG58JsENNPtdC7y4gWaxgHwOxVozumHXyb87QKa+wfA7zdA8+YA+H0HNMO2989vOtAU2+lc1l//dmb8EvFrAroOO78ek+5w+DvPwa+kBDbuqRD9O/zthL8W5sk=
*/
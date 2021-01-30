/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, __alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_clang.hpp
1yil8nVUonCeR3qIvFESZBWz9oxdC4yi9wY0ylZs1T8w8NIvUE23kU7r9pcKDqR3E3JEmz7e9jNO6n0n
*/
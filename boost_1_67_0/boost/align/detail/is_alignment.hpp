/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

BOOST_CONSTEXPR inline bool
is_alignment(std::size_t value) BOOST_NOEXCEPT
{
    return (value > 0) && ((value & (value - 1)) == 0);
}

} /* detail */
} /* alignment */
} /* boost */

#endif

/* is_alignment.hpp
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
*/
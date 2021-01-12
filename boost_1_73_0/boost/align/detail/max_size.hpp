/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MAX_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct max_size
    : integral_constant<std::size_t, (A > B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_size.hpp
1p+nZ3fIefE38NvlanTaNaB2oAWBLVLuU1uk8zclD9B/9yyjVfowe4tU7y95gNVPms3az4m3ikhc0x74x5a6xdRT84tOvfAx5fe3iJpJ84sK+drYLWUx78ISuuGPVFtFzjZaHyKXTxN3bOnhi9XM3OJ23BIduM3ytID8vJb7Lgk2KQV9GI8jV83tuMSOIWrYsY/zPk8CfpcMMvZVL0c3WVee1HVWyQNTZLT9IfPB3KSz5IOq
*/
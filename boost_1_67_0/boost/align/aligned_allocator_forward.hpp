/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_ALLOCATOR_FORWARD_HPP
#define BOOST_ALIGN_ALIGNED_ALLOCATOR_FORWARD_HPP

#include <cstddef>

namespace boost {
namespace alignment {

template<class T, std::size_t Alignment = 1>
class aligned_allocator;

} /* alignment */
} /* boost */

#endif

/* aligned_allocator_forward.hpp
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
*/
//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FILL_N_HPP
#define BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Fills the range [\p first, \p first + count) with \p value.
///
/// Space complexity: \Omega(1)
///
/// \see fill()
template<class BufferIterator, class Size, class T>
inline void fill_n(BufferIterator first,
                   Size count,
                   const T &value,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<BufferIterator>::value);
    ::boost::compute::fill(first, first + count, value, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

/* fill_n.hpp
oBxYDdQC+4CjgOdVlAPIBoqAGmADsAc4Bnj2C9ENyAZKgGXAZmAfcBTwvIa1DZANlAOrgVrgAHAM8B9A+kA2UADMBdYAO4A64DTQ/nWsT4BJQABYB+wDjgIJbyB/4AqgHFgNbAfqgJNA6zdRf2ASMBdYA2wH6gBxEGUDsoECoAbYBNQBjkNoQ2AcEAA2AweAE0DaW0gTKACWAZuBfcAJoPXb+LaAImAFsBmoA0Qd8gKygXJg
*/
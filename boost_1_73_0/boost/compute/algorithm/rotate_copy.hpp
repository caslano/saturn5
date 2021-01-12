//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>

namespace boost {
namespace compute {

/// Performs left rotation such that element at n_first comes to the
/// beginning and the output is stored in range starting at result.
///
/// Space complexity: \Omega(1)
///
/// \see rotate()
template<class InputIterator, class OutputIterator>
inline void rotate_copy(InputIterator first,
                        InputIterator n_first,
                        InputIterator last,
                        OutputIterator result,
                        command_queue &queue = system::default_queue())
{
    size_t count = detail::iterator_range_size(first, n_first);
    size_t count2 = detail::iterator_range_size(n_first, last);

    ::boost::compute::copy(first+count, last, result, queue);
    ::boost::compute::copy(first, first+count, result+count2, queue);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP

/* rotate_copy.hpp
paj6AQlaPuBeO2g3Zdo2i49s1ytyvDHyAHXgPfvymZU0UXBZRlCYwQ7cHMOZK27ZiETMNX1QnljxMGqzFSm9jHcRP0Eq34hu4lzFh7XZMLFYuVi8ouzAyJQvzzsWEU8cSOPKxGWYT7JHBPcFfA6pxtIGe5qdL7Kfy2osZwMt+EiqJRC4Q70VUzTP2aRzKIxX9BtP6VSHDxy7oBvbj8eNVHL7reMcMQASjlcshc9LmFmP4+9Y
*/
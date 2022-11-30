//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GENERATE_HPP
#define BOOST_COMPUTE_ALGORITHM_GENERATE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/function_input_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Stores the result of \p generator for each element in the range
/// [\p first, \p last).
///
/// Space complexity: \Omega(1)
template<class OutputIterator, class Generator>
inline void generate(OutputIterator first,
                     OutputIterator last,
                     Generator generator,
                     command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }

    ::boost::compute::copy(
        ::boost::compute::make_function_input_iterator(generator,
                                                       first.get_index()),
        ::boost::compute::make_function_input_iterator(generator,
                                                       last.get_index()),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GENERATE_HPP

/* generate.hpp
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
*/
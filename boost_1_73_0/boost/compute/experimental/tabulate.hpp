//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP

#include <iterator>

#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/iterator/counting_iterator.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class Iterator, class UnaryFunction>
inline void tabulate(Iterator first,
                     Iterator last,
                     UnaryFunction function,
                     command_queue &queue)
{
    size_t n = detail::iterator_range_size(first, last);

    ::boost::compute::transform(
        ::boost::compute::make_counting_iterator<int>(0),
        ::boost::compute::make_counting_iterator<int>(n),
        first,
        function,
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP

/* tabulate.hpp
cdbHHo/1jSfPGhMVbfT8FMp19LN8XEsmJTvUicvkbTY6MSawJlKJd4jTrNlo037bVYs9hHlWrqcnZzxirUR0StREmkX52Hvf1PJ6/VZttEAtR4vO/ciz3vK05x7ybCo6JiTeTdF/8TTFLmQ9f+wU1M1bps2nir+/RpfwztLc24Hir5p1sZiDZVoeuz7IEqsm8/zKrOnkWxVcbivTtdra56rKioHbauRuzv7MOPZCTuVcWUt7
*/
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
kX/SEPINivjUsVmTb6PJOzXn3y1xJ+BLNXl/TvCc+3PEtU7ALyDz+HapByA/C1I37NfJ/Lp20HaZH2uDMQXHBuGz/aVhH5wXj8wXeOaVzK0uJbjAV1Tm9lUVlczpN4uV3FzgrayYWVlUnoyPv/mS0xYNzOlVgB8GqVjoS57jqfIVZGZQFZkZ/TL6ZWZn5Azol1FQDbq4AGYZN+rkhb6qUk/F1ayRVwhTzLwyz8yrUS/O71ejHmqxrLDZvsf+9hY=
*/
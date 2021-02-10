//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_CLAMP_RANGE_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_CLAMP_RANGE_HPP

#include <iterator>

#include <boost/compute/lambda.hpp>
#include <boost/compute/algorithm/transform.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class InputIterator, class OutputIterator>
inline OutputIterator
clamp_range(InputIterator first,
            InputIterator last,
            OutputIterator result,
            typename std::iterator_traits<InputIterator>::value_type lo,
            typename std::iterator_traits<InputIterator>::value_type hi,
            command_queue &queue)
{
    using ::boost::compute::lambda::_1;
    using ::boost::compute::lambda::_2;
    using ::boost::compute::lambda::clamp;

    return ::boost::compute::transform(
        first,
        last,
        result,
        clamp(_1, lo, hi),
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_CLAMP_RANGE_HPP

/* clamp_range.hpp
CaNFkEsLHQmYrx6LbSyXpqnLltfXTD3p9j2isodnlAc6BaeV/QZ8+XMbQQ4hnRqz0TOZiWZ939CFQyOgTB6hXAZFnB8xzhM7wWrgKbuqlyb/VJqcoN8acFmGr0YzWJ8YI3sz5GtHYR5S059ijB7YgO+RvzqGvweC5tFpzBvhN6RwMK7QpHg9GBuzjIOXN1U9P7+Z2SR1RklGm5XG1sglnnofR5TvtnSxSpRTd5dlflkym8MzjCLaFUiICUsj3FIqQ27IAjuqtlHJzD54E4OzZ4Tobi2300yUmYgZpenXYsPmY1BkhmQdIpEvtdBpTPM4mYzOIfqa82xJBrgyzrXjGojRTy6zYE2+FgevYIcl/SDewOz/WSYyixYOJTlDl5g0FlweKwn7QnEzD+o2JWWN0c4LpsWkt2HFuzYx6cGHWSZPIw+6U4IYl8W4hRLGnQr2wPV1BZohtWvuHbLl5lESgGphhOu3u93GhCN3POm6vdkDwA8T3bKRlhpPjRgGqxVIJX6HDODRszR03Ya+MdMq2Gzg90YxBKRx1WWUKcqFxEyVqI2rJlHR76YWz2lwKOOIHZWzFzmYQ3yXMhcI1WJlKi75LUoLBUaiUwUJedOcY28ytsu84zwJjWltZdC9yAgIycinA+AdjXlnQ0DH
*/
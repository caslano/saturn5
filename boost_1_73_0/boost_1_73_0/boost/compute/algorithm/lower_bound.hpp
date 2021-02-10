//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP
#define BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/binary_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the sorted
/// range [\p first, \p last) that is not less than \p value.
///
/// Space complexity: \Omega(1)
///
/// \see upper_bound()
template<class InputIterator, class T>
inline InputIterator
lower_bound(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    using ::boost::compute::_1;

    InputIterator position =
        detail::binary_find(first, last, _1 >= value, queue);

    return position;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP

/* lower_bound.hpp
5UJStueD4CR9LvV1iREtGsM1m+RY4vB1XRl+HC0Ws4jeaz8qjVizfQIzN/SF2xUlF7g3isd+GlxjrlF8PJpFfnD2xStwAUDDtPLGem9sLpxZHBQU8mh+EMeujPy9JthCJYeq3cS0t5XPGIOgSuLsoceO3wUH5HY7N6YBF0VbREy0BGNPr4P/q9NNmXb3LWauq1Y2Krh4H28GhD9oIIMZoTBnmMgw1dxpaZtGHoz7wvbYrc+iclcBzmrfrQwHvvFDAjHpLnhB30H5KuLxXbS6NsZt0S3Ay42lplk50NZUE+BKo8tL5AETINENN2/uDpiFo4+jeDJ6F0/ixXkwAo00e2K4YgrJjVaXzhpmTEjz48WMbzNMAV8aXAVpRKO0zYK/V3js0/Hi7HRKH0eTs3HAI328PPnA4oL4rW0Cbs433Lsz3FKbWnrh8d+j49lkHERlFmyuAfSIv19vrfhrAH+/DgIa4n4JZvDF08/udtQ+Ggb+/Y+tKwVavN2Bk7e7rSgy30WZBdzDtgD2eW2HXzoZI91scJd5Ftqc5iXm6w7LhDRQa4Q9qjAdOllPFS/rmV12LS7j2uwq9i5ud1FpYb0AY0aZcqEbzMdjGk3mJ7jyvDt9aD8Ndp7thvc3W3p/e7NjlNsdBP8BUEsDBAoA
*/
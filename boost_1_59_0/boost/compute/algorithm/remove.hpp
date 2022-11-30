//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REMOVE_HPP
#define BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/remove_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes each element equal to \p value in the range [\p first,
/// \p last).
///
/// Space complexity: \Omega(3n)
///
/// \see remove_if()
template<class Iterator, class T>
inline Iterator remove(Iterator first,
                       Iterator last,
                       const T &value,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::remove_if(first,
                                           last,
                                           _1 == value,
                                           queue);
    }
    else {
        return ::boost::compute::remove_if(first,
                                           last,
                                           all(_1 == value),
                                           queue);
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

/* remove.hpp
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
*/
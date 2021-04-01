//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COUNT_HPP
#define BOOST_COMPUTE_ALGORITHM_COUNT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/count_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns the number of occurrences of \p value in the range
/// [\p first, \p last).
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(n)
///
/// \see count_if()
template<class InputIterator, class T>
inline size_t count(InputIterator first,
                    InputIterator last,
                    const T &value,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::count_if(first,
                                          last,
                                          _1 == value,
                                          queue);
    }
    else {
        return ::boost::compute::count_if(first,
                                          last,
                                          all(_1 == value),
                                          queue);
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COUNT_HPP

/* count.hpp
NJAb18+bKKk9YZA4qI9Qc5CNtkjCWYBvwaNuJ7Z4340lVoykzSwczJqRWh0DAJUxhuPr6xshYvnES+eSbMFLo/4QNqh7GxJCxWpiG+5LYWfLmF2u66Cn8BUjvfGjBWzv5R31mpgq3UYDKBWGpCE3tZ02rbIHw5vE6ILkSu/5e9Oan/s8lwRoxht7R6QFKz1CNyJpGiVPHgChBKN8N4L4KBhaeLYJExm7GQYDG7FI3u/7HdPZojuQFIwIJv0JvQLUFm2s+TZBcRw6Jm3ByUz0IXfN1c6PI65TNGRDY2g56pRivVQcwXR56i9yS3Q017N51/NWqUACVMFbiEmrIyUVBe/9KY8v5TIhO+ojOLcTlrIJz2/50Eid5ZyacOW95Z/s4manErGxXi9zA3eBDu9BqqorxurXFUzXuYQEgxP+KgIZI29prG+6rX3WMDNiCO1pwHS08l3xXSOxdpqVsO9q3fLTbspNkutTDM0dQf0QzY4r6DZrnRAwOABeJ/jiYlOVZhRuIwEM54AyOHhVSdAMy5jklZ9vcY4LfgpppY3FVlYqJ4Ue8F5qRsTRwQ==
*/
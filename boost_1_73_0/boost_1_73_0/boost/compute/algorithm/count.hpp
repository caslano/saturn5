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
qZKujPdpUUCdD40Fh0q1cOQq0TUlIMxatmK2hDVlLz1fnNGOo21LUx0YEq0tUFFbTeGIFrLLDREfQ61ztME+ENFFaVkOlH+nZfvcczCasoLeaAbjWQ9S4aSL4XY8v5p+mcPt6OZmNJkvYPoJRpNFi/fXePKRtCEpqgW8X1t0lIUFWa2VxPwg+A+c9PkVcD9Xd8qkQq0yhULXa3gDvVdv4ROmJOvTX3vQUzJlO3ibvHvy6zMZC9WLktkVTEafL6PnsE6geQCdV/sieM0Wk+n1bDyLknP4SepM1TnCGZs1Ois/RIkj0/Mx9DZG5s9l2+cXg98pDZEH0I+Xs4ub8fV8PJ1EoU9FrTOWOg0EuThSEdFrapvRncj+qaWlpqU7WBbjp/hSS99/M1gW10kULfazlQmljm27XII5CSCjOaX2ocjKxn4XpuEbCcxE/xmH1FyQAIMx6yo3GmlwpL7r2KNMlsX5YVV0rw3NWGlR5OBEgQknEeavdj68DDnQiGxLZHHSVLLSotan3Sxra+6sqKAvE0xAPCKWwnIKbOJEhTS3lbG7AQe2tdb0LmmIzg06/bOHrxy2IkYodhOpw/IlrRKyPCwK4BwzQRvimJpDWrmIfd1hShtwwrGUI7Uz4BN1kZMV7S6rdl3kWjMzMZOQ
*/
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
waA/mS7S8d8R3NW8qvc4O2VB18oKCjXZMmhZxfi2g2lIa0CtEAHxKdcGMa3hSsZIz8CwdqP3MC4IIrQCsiVckBLpiIHamEZ/6PUq2wrMpEdVpXvVoRRxbTbPslpgNBuyA9UYMAqsZhE4+wg2ivKVe2KJcLOxpeC6jh7DQkJJe6oFzYTYw6ErZ7pLgUG2r1bkLKHB6LlxD62kdmx3tdo8McSy7oFWtpVIh2VBO6qw8BFYSVnr7X0hDiz7KvuS/+DKHmOnoCRGBWGSQZqFUBLNdQRf0/x2Ms/hazKbJeN8AZNPkIwXe7zP6fgGtcGRtQV237RMYxQt8E0jOKNPyH9ip+e34O6z2PANK7QtnUo0vIXw8hISu7baoLDfvAshFLx0lvAu/u33+OKbjRGRlogwiLNbGCejQXAC8DVepIHjEqtLYGOF4V6Vztbr02Nki/FkmqVZEF/DL1xWwlIGVw60k179MYh1g6cphP35bFgpPP+e8+y45TleQdi1QNR5Hk/9yTGy8PxPzIRQH8nNIOvP0mmeTsbBcpWe4Hh7vlxNXW76dEK/apStxGFgYNWiIIk/ClAptjK2RU05YGfpcLhDqVHP2HAoTSfAR0z31Zkf2I8unu6IeUColaBcrj3MwSWGZIUCP52NT8VWFWMU
*/
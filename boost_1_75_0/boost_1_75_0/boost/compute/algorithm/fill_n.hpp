//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FILL_N_HPP
#define BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Fills the range [\p first, \p first + count) with \p value.
///
/// Space complexity: \Omega(1)
///
/// \see fill()
template<class BufferIterator, class Size, class T>
inline void fill_n(BufferIterator first,
                   Size count,
                   const T &value,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<BufferIterator>::value);
    ::boost::compute::fill(first, first + count, value, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

/* fill_n.hpp
ZF0ShbaKw62WHraxA3X1fWwbts8nBl9xw00Y4dNfMlWr5qW1SzmVbow9rOv/W/7TOLK0cQzreBwZj/yfxvHJvb9qHLsb247jinRjTmmv7jx5jmw6rH6Ml4Wj4X48ibseRgpmCMxXeYV/iGqX5pqFDOvtM+KAZK53SRVoL/Owph25AzBEONlLu/mI/tR1giMBXLW2ayh3Fz5/DT0/kKecHkmmapB7s1xuaGOs2pcUUYJ7D/Rw/yjWQxFTRWJAZq+cuBLa8srWb6lJe+kc1rKo7AwzWlNU7WOKzKxd2E+zifa2lVHAkOCyYsE/RbVfFmniQWMT2ayJwayJP7Im7HoTcyNNNM7Rm9hRGJGrxpMa3aj5n1VMZ/1tJYRdawm7lg6HYiUkWL8tnWiO0iRGFEQlXv/kCpg+Hv9sCEvdN+1yuDL7lv6T/kv7FnO7/HFc58D0DTyV7dwfYjV9A+nPke9V7U2zzUJWCwfZiJsZyIoRZPkMZM2LCGQ7SglkXxUykBUr1x9nICtW7e/M5iArVp65mzGGEYtTZa7R142MyQHKnQHKIWvDHXECnGXdPcxEgRM/s0hId5GRM6EPmBBDfopfEx+8M05QjpQzdRWGqNN1BIEeqGR4EBp0bkUtg1P6IjwFqykhssabVgIDSV9CA3m71CxQpGuoIxl53xIiBTFVMPSwhEUCLtG5G663YvUa1RJd9R5SAZ5CMImnEIxH
*/
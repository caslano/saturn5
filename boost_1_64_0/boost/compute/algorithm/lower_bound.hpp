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
Sae1UlIS1qFmdjLDlAlTlbxvrIXafhkcaX8OCYJj34r+1saVX6ch0ICO/SfweoXnIggexB4mPd5vwhqL8/GnRfHipPeGs0R7bVSsp1ZSbDxeeXS4Mr3RvAvab96BCcYsBx8kOjNhlSgQsnzWhNAAj5j8BifXcWWsvtMrh+Xl3v0ZU5ngZuCR4ZC8YAuNLXunHgGvMg9/+VoBh+VZlNdbuOl7r0b5WoecI7IAJEU+ozuY47G8DXyPO0mttiw300cJxerLM461/XLAQImvzdNdW6OICdmJ6OXdZYR3V9l4Jk2c+WrkaJ6mKKRCqCv3zFl1Wx/7cYrxlvhgSc+p7v/aDB1e1Rqqoic8ouSEXDDj3Qrj+ZuNI4Rv10gsSxEtsfF5IjTxIhLQnZSCrv6lbsaWp7aAesioq2NnQJI3g9Do2/eeTgAMG+EeghuLqlu0u63inCXJtueHECNlqmE0k2mTvq/uVRanxaCyQDcYpql1BfxJN9/ae8OO1kRLV/JjoQZ37at0+ipJ6qqbYfQl5KgrrSoUvyCnHJ/s57TcXiTpYbPecHURCse2Rp/E4A==
*/
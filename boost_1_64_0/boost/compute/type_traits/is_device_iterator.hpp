//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_IS_DEVICE_ITERATOR_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_IS_DEVICE_ITERATOR_HPP

#include <boost/type_traits/integral_constant.hpp>

namespace boost {
namespace compute {

/// Meta-function returning \c true if \c Iterator is a device-iterator.
///
/// By default, this function returns false. Device iterator types (such as
/// buffer_iterator) should specialize this trait and return \c true.
///
/// For example:
/// \code
/// is_device_iterator<buffer_iterator<int>>::value == true
/// is_device_iterator<std::vector<int>::iterator>::value == false
/// \endcode
template<class Iterator>
struct is_device_iterator : boost::false_type {};

/// \internal_
template<class Iterator>
struct is_device_iterator<const Iterator> : is_device_iterator<Iterator> {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_IS_DEVICE_ITERATOR_HPP

/* is_device_iterator.hpp
LZ/v1innufS47XtFxlgzASaZGqIiRyNuwN4XobdV5hkK2lHdY8z7pw+xUt8IUf9feAs+XWfa3lZ4rtO8zIf/+LDTjNJqlG4ulOyZHmAJ/YnEmW6KE37wFMuTu0ZNhLYWE9p8BdrdDqnceA5NLSbGGGBRs4PU2/wMcDg/dKm8XKXdwEtLww4/ea1rw5q2agDroz7oJ7awWOZZZnybNIix/CMHL8zOqObRjubky4u5n9jhwwx5Ru3or+Lj34rTo8Ox/Q9Uu+MxpcH5tNyOrNSVmB2SYxHW3NSecM463CBhowTY/f785t0cDMlV3iDCJNpNPpeekR/lWh6vD5FBJZSCINIBeVomFY9f8Yidu37K5dU5DJR1RN2Fi+5qWNsb8ax1lO6eeZ6T8MGUzCbQQlDAqEbFJs7v3/Jn2AmRe3BxQpvKqKIAgyfuoJZ4UhA04jUTOrZk/V5m21PY0a3DpiyF2od1cmpEhYfupreZ+e5oFsNV6t71K961akKqe2hdfk0FiMPUoKu/UjDwY68OZFMFumjoHh5td/W+AHx21dCWXXNxcXGf79bEGqK1YA==
*/
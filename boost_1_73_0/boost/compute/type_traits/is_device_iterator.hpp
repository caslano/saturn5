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
77j0DmlJyaPd941VcUvze+8Sbr5/SDGfpSgIhznixZmf/wLyBAY7ghjukS/Q6WBolaMcegB/F2AYcYHQ5NDq6MH8XTTXFhZSKDQ/plKBecIKR3j9Lm90TdTXgsqfONTa6j6ug3pM48/K51dE55km93uBG1738pzQ1z099uF7lc5kW2GucSVvdJ2T6/XfVN7m+7qOqXwtVeFjvfOlxjC4yqIW5dtNxinMucHcIrIWIufD13hh
*/
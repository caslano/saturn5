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
XZoC7dTG1J1Ns7nvkPsTaUwD5VJ/9qiQMKKccuypoW70Xw6iqgY6J6133wTTUJLfQkdDe2bX1AtwVX6xYPoqtcmCPLSGC1iGkNHk/VUbJbIMUoGeLOYJqErtW2rxfAsLft938uiaWLe8BgDUDCpIgkzVnyN0IyfneLg3OvYBu9LR7K31OgOWTKEUKi0E+uy3NCYcdciglYlrv30yVQXV052BhpDdv1PzOCZX/O3LMR/Z8rBMvtHg0S9Ri8tfQLIj+40fSnVFzyk0HnbDbEAOB1oF6fP4u1EExvTwYYeSEdQIRkYAgjgihzGAvOV0aRzf73/zYc+hAsvcxIyDJcLVFdEDR8HNfGtu5RXHqp2NibkMAwFHfRdDYB5kBXnvSq07z+vi8vl7ktqvLs86U+5Y2aqwaG/PCpDZtVan+WwaPtEcgL48tDVtKTOG6NLUJQGdkhDaMltiKOsvTHYc2F7pStKbr4C+HxJUOv7GQ+gqpLrjctzwe1UaspET5Qkzf4EwkwZi5a0l6gAOZ0v5PhLarD7qPBmLEoALw/8BUEsDBAoAAAAIAC1nSlKtqDttZA0AAKErAAAjAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2xpYmN1cmwubTRVVAUAAbZIJGDNWm132sYS
*/
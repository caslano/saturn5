//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP
#define BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP

#include <boost/config.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace compute {
namespace detail {

// default = false
template<class Iterator, class Enable = void>
struct is_buffer_iterator : public boost::false_type {};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP

/* is_buffer_iterator.hpp
ojAvWyIPdMWG6qUXmkvVCFdV1OuuVaPsch3S18xe4wpUq0bFF5mKqrwBb6RG9RiquNgonKK5fYFoliouMReTKlKkl5oKjKamWnNZ1lNafbhqmiFqvrlUiJqSpsBUFFCnRrVQOBgNGpUWmoqNlhDtW4XUqaGO22PxukQs7m+Y39LW1cauQNGBMFmRP1JNXG4oT1PD4WCYXaOXKRllKVZ0jsvjDVRz4yJYjwwY2bU3UKembhAyRdgzNzJFSLBtXNw=
*/
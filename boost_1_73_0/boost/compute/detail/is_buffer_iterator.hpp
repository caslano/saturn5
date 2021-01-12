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
DRwL18HT1dx9ztb4dA2urmvebvADWaYv1HZjzwsfga3gHtgOPgo7wsdgV7jPDQ8+DvvCJ/3Uj/AJrkfD38Lxej0VHoBnwWdhDnwe5sODcBZ8Ec6Ff4Dz4B9hKXwJlsNXXP3AV+H58DV4CTwML4N/dvUG34Cr4JtwDXwbrofv6PP8rj7PH8Jb4UfwEY3/E/AzfR6/gO/Ar+Df9X68Q73DdRL8FibD72A6dLjfCHpgc+iDbaEf
*/
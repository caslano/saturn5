//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP

#include <iterator>

#include <boost/compute/detail/is_contiguous_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct iterator_traits : public std::iterator_traits<Iterator>
{
    static const bool is_contiguous = is_contiguous_iterator<Iterator>::value;
    static const bool is_on_device = is_device_iterator<Iterator>::value;
    static const bool is_on_host = !is_on_device;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_TRAITS_HPP

/* iterator_traits.hpp
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
*/
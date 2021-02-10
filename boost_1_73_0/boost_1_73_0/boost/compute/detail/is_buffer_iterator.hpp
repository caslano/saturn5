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
cAE2rKWudQZIiNKV3jxKmEN4jeDrtYiTFVwfQaQrsU85L8XM4ezy0lmO4N6bNCW9XKI9IW/pBvS4zsGSYhrveWRbm4Jl6fnDIdBldRt8AcVe9JFURQtTrZW9dXFABnWhM04HLbWqatR0TzA0DidTVMNg7MGLr3NcBGGKfFhH8giwOOiZyMMKXi2Y14tUxfCaBntPG7iB6oq8QNaZjMQW1WDPpYYFx8CnyMIycyeiBTGlvjN5DUuD9yug29YxwGfZng3DxMfYS+lu9yPJamHzFAzY3TWqDanEf8f6LVpMxhlXUhDeX8h3+lgLbBkrywFucvklEJIHoXdkW5LIrVprLBTcNVhd1+ADkeekxXmJfllBqzOGJXYm56f07NXLF3/tuGSU7IDDVeBt6T1IZHR60QctRvFKrzVHOcsr3sX7Ey1o5QYB1x7unEX9yYNb4zCK3o8mZw9uj4R/HkLoYhRNBaCrHK5l8FkAYgScg7NhKHHZdb/iDMM2X0U8J2CGKCnNY5UiUmojTWg2PT96SQf3vPq9ySCKJaIYk8MdDYB/qeJbzYEbjO9eID9o8CYmlSTczgIs43mAAaGkiv/IMyQ/oQPo4NmFIcklvnXpX6Nhf3B2+DBS7nbQoL9x11nRqBUbvO6GdjGKJaJG5ht4
*/
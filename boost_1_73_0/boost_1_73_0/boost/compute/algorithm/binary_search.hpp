//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP
#define BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p value is in the sorted range [\p first,
/// \p last).
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline bool binary_search(InputIterator first,
                          InputIterator last,
                          const T &value,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    InputIterator position = lower_bound(first, last, value, queue);

    return position != last && position.read(queue) == value;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

/* binary_search.hpp
UOtCgQ2ambIEzNK6iW/LwL71gJYPP/boqt2mI1ccQAuPUVflrmU5gVarfXpMjrv7+sdNyhJ1t5LItBQW2dbseegdZTOTgZyu/1pb4enFsZXpjqIB9b4BIU3MNo6O6y3aimn2G+bKyXyyvRB+jDV02T5tkeHicztBzwUd8U7iWuG2v7lB4qE/eXwY0X+7d499l6td3d/OUCctzAbIGJrOHC8Udj63Cd2PQK6DBHTPI8paGa7/3h/PYG9fjQLPu9dkNsZOGbaXYXhRC43MnLZpBs9uGuyQmu8bNb9pCbyCcC1AV2+HwFpWeCnP3naldR2e+u6VaReVbXJua4jsc541Xif+uvMWoP/O+WX4l51fnP2hw73x86v3kXnvjNMRD5gfC7nIMK7p/bzFLHDtAU25yJIqRqQw2MYLEVoCNVCm8XJgJ1g3/8LL2tXgJGOYu0fyFe9MjF0JLFow6ODYgqoR9fvUvYvuMbL/8OCGfSnMZooDF7mkBqZ0HzP9/kGlDx9Zvd7jw939eDLl0bZ3P7oZ8MC/U3771MLXPoHq/wFQSwMECgAAAAgALWdKUpeCbawdBAAAZwgAACYACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF9nZXRlbnYuM1VUBQABtkgkYK1U
*/
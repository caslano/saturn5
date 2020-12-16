/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_operations_fwd.hpp
 *
 * This header contains forward declaration of the \c fp_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, typename Value, std::size_t Size, bool = Base::is_always_lock_free >
struct fp_operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_FP_OPERATIONS_FWD_HPP_INCLUDED_

/* fp_operations_fwd.hpp
k2znPKl3GXjtjG8RGN8K4iuV+Pwf9KoAVP7/3Vb3SxuQ/4QVkP/rWzjnv7HXIV0qF8O/55SNC1L/HfJjJflR4ZgfZH498t7bhrupZWBcJWZbpMTl/LBUhaDKoL/tGqhpQBn0l2vAmr7EVs5l4NkTLH0hn8F+ZZF5ka0sLPGvbxWYP6vJn5gDQeOnUOpeJt7rLzU6MM4dcaRT4rS/sFqfwRX+5YGf+pdHhcM9qTzauTyq9zimrU7P4bILgrwLtQ7MkyvNvj7nPGnQs3iLQ1xr0rFdx6VfWP3y/gvb/ai8AXn/hdP7TxvnvK/ZE5CuuuX7pCDvP20C8+Jqc83mwLyoV55763zntoHxbIjjv1clHtvLvfU5vNs/3/FT/3zf7fAc2NjWOd+r9jinrS7P4erJ7s/hJjGBeXINeZ/mkif1fQ574yt3iK/UfO+X+Bw+bPVz4Ev7u38DyuBLKQO/+hHrXAYxe93SVrdnQNp493JYHxuYL9eZ3wCu+VK/+7937VkjzuW7z2orH+BGGN+Z5nf4Bx2xT31rL6JDevlSTMS3xCk2lkmcyWJjB2St+f1htVHWLmup150vkfL26nXQNt8eE9rmNn7rxZf4pSe5XWCeH0HvuCU91ntAqu25d7wB9S/V8twb4K0D7VzaACxlUpfrvnyirb5ZbD/uYPsOEpb8mi+u+l7r3vt6avvaEz0kjq7IDeY7vjUOz3IqTK6sKSp7scj+z5LPot81oE5M8J2zrLPPXogMiDDEf6FPR4U/qyM6ljVMp+jzvr10KAdlZ0YYffJ6T1g9fkbXNdt66zpdej1S0sJxlRb/epkQWDY3md8qtfmWP3BRrso7/T52trVeih6+VZ9zrMoT3/rFtvMklb99e/UXynlrvV5Wh+uMtKh6rdfdUvdZ4td5BlV+EKetvnTuEGj3LeY3ic1uaQtRtt+c7m97RQjbK0LYXtEA229Or7vtw7y2Jwbavt78RrLbLm0S3rK/1WZ/TQj7a0LYX9MA+2+th/3y/GO98ED7bye8mIPafnubgM6DDbY8wI97HujzrnnA+frnwYZ65MEwbx4kBebBnYSXacsD/Qog9pfZ7M8MYX9mCPszG2B/WT3sH+V9XnQKtP/7hOfx2e/yLVybD3fZ8sETIh88IfLB04B8uKse+TDMmw+dA/Nhk/lt6MsH+7eosv9um/3lIewvD2F/eQPsv7se9nufAz27BNp/v/k9aLNfvgmV7ffabK8OYXt1CNurG2D7vfWwXbfLdA20/UHCMw452C7fZN774GZbHuDHPQ/0edc84Hz982BzA/Kg/5mBefBDwktzygPfzVDlwQ9seZAWIg/SQuRBWgPy4Af1yAP9fu6QBw+b38m1ebBoYL68Azp/m4heF9n3wvpOLXtY2Oy6rQ52EZefXYQv78D+13FlcqANj5jftDYb5H3OsX+vLIQdZQ2wg7ic7bDdj2/oFmjHNvO7Vdthezdz6zcLYUtVA2z5l5sttmtrevdAWx7DluPaFvf3rCz7928Ie443wJ6suPDKJrlHoD0/Suf4YZs9+jbh3K+Dvrst6nz9bfm7W9nY3n8+c7DlCfN7Wdvi+v7j2E+SHcKm7AbY1D/Me8DOns73sVK7TZPHjB3nci8rDWFHqc2Ou+PCtyM1zHq2rlegHT8xv021Hc7vZPa+kooQtlQ0oEwqwiyT7JRAW540vzVttsj7lWO/Q00IO2oaYMcXYd7LknsH2vG0+c1Y7WSHvCu5tOfjx90edb7+9uwO057jDvY8a37/aXvc33vsbeOZIezJbIA9X4awZ4C0MZf0qfV8DdIOKUJWdODdY6/stcTuZjQRW9ruGPe3fG7xomVLZQ9Rr25nZcc=
*/
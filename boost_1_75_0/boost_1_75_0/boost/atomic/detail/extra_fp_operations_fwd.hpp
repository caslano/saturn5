/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_operations_fwd.hpp
 *
 * This header contains forward declaration of the \c extra_fp_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, typename Value, std::size_t Size, bool = Base::is_always_lock_free >
struct extra_fp_operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_FWD_HPP_INCLUDED_

/* extra_fp_operations_fwd.hpp
fOYWuYb4i0OEIFIC5QZzjCo9YN7bw01K0sPPl9hBmV10PjR/Um2xYgi3Y16/3B773VX16gucG5fr/MPlZIiD71VltABer3DnnqqflvxxmzJvgI/h5NK+yP5xhMTrukUc4B501CGNFU2uDafQIf1TKO7w9w4hqHRut2cnDBTmqfwulbLGSx9jATYHfzLp40CE3xedMG8B1h12Cu/aW0FrS5vbb1+s4w/Wty8is3sfdw57JSjLfIyIc06+cGngGGAywlH+5EYckmalrlCheSOSg763yDNdytJBLYotUjX9i5lx0Nqf6n/xPfq6n82JFL+GYKAY0hvoEUR+iVxt5ETgjsj7GGnLbJOUgWcQnEewify7fDx5EeBFZZ1UTuK24iWVZ7FTvAQ6PM6iBwooeO/qWibePSENDpftwIHgQLnGfR3J8uaRHjQXjY084x8v2SomEt+L3lJBz+T5MafzqCIO0WJF+/LDSwqhctu4CzATgqW1BXH1SM9v6lX6ZafL5p8z7CwDFgin89wKkEYXkMsPmD9B9n7uR0TtRpDre3D5U9lTUdwDSjkqmHuW/offD5itpJ1qcHwxAbpARAua2TUiyjH10+zF7IVCgK7YytEvxO8GeVgt9yAohf6dCJVft2MDY0zgD76FIOmS1AGWBQEvBpg8R7KePWPPhO6G6ppwvtWDFv2YdjReuzL6vdAQXSl8zgRcZ/tCkyXxqyUh
*/
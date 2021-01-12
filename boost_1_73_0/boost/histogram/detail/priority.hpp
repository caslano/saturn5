// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP
#define BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP

#include <cstdint>

namespace boost {
namespace histogram {
namespace detail {

// priority is used to priorise ambiguous overloads

template <std::size_t N>
struct priority : priority<(N - 1)> {};

template <>
struct priority<0> {};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* priority.hpp
oYbFwIm1LpTAvOJYYhECNh6TtMeHI9RfUV0WSv6mt5G8rIIBQ/b1s9RCdGOZyyoL+yyrWC+0yiod4/kU4ifp72iW8EPtgkKGo6f05eexj48njz3p4og9d/RtcbKB7HMSufiQdbPwOfJ8/mKvZLGCTyqMYBYF/NJXh1tv7FMpQ0rGe3plFvN4goCYnd29mFSk1/pA6bsxbaDXGMYUApJLCMdPLdGREv8uPVtmC7ArVlghCgWi
*/
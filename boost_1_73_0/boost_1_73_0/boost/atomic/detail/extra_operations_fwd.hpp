/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_operations_fwd.hpp
 *
 * This header contains forward declaration of the \c extra_operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Base, std::size_t Size, bool Signed, bool = Base::is_always_lock_free >
struct extra_operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_FWD_HPP_INCLUDED_

/* extra_operations_fwd.hpp
6+d1T09urp8Xr5U+H3Th9dIPgrNfJU4VEMqQ16drKDOebmd5Jl+KfCG4U9LP2nAndHjItkUYPSZqDx8l0k/mKNHho5teb6afl258vbl+Xtcp0jfPnm5Jpx86SpLDaLWneNyW1XQyZe8XiLfV4Q84/AGHP+jwq7R7eSjJj0PdK4LtcW+x5AemrnnHdviel9Aq6eP0pUJ+/KnMKb80Hh7qHOxZsaJ3RXeoM93R1hHMF2A9y1eKKUO+L2U62gMdi+E=
*/
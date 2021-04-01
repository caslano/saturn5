/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/operations_fwd.hpp
 *
 * This header contains forward declaration of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t Size, std::size_t Alignment, bool Signed >
struct emulated_operations;

template< std::size_t Size, bool Signed >
struct operations;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPERATIONS_FWD_HPP_INCLUDED_

/* operations_fwd.hpp
akcorUcElPrcvcJLfClWGThlwAPd7Hs9CkPXFg7cp/cUWilJd6pql/PP3h0ZgsP50DRDbkaptsJJ5gPPZPPto5IHqpXSCGA8BBlkgOcevtVFnOvjQojEKDMNsa5kdR7iCEiyc1TDByBnNnw0KcqcEh3g3BbdOuLBf0Y/EP1eV3DyiR0vKKzmtEb8q1g50QCW4pGGHseRQvfCKJdsmQOki5JrwDp6pA3RWzdw/1ZeE3xir60ziKaHf5vMvhqlVXfoW4yAyIAufDAL7Lberme7vIwcDEqVt+9pptnl/3CTI4YHk3ZGb3taqc2AWMsvLd7OVA4x28Yi5G1JUv8LHpmLAJw6Bg3ZzJh+xBLI7lAkuF7RwQY+1opB12rd7FbqDqQhaXCzdlJID4yBKwR2/q6onKfZ8iOqjjowv9TY8giI2Pdc4RX6dxmvr0eKHFoQIYgQuYZKx+WnT/70fKVWH8p4zQVU6Qy0Qyt+ZzZblj9uvyLZIn2r7T2yP//r7YVspINWo387LoWG8m5ICgFYMVLgLF7KDIyY/jOyHtAH29J+W6HERBb5qD/gkMY9Ew==
*/
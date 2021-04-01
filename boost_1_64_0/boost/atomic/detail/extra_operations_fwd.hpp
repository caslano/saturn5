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
N6z/0ndBJzPjfXURblnkP5SiXCfHaClDT+c5MNGDgma8lskMqOnrGA9uk61IoLxGRrjsosCQhYAx0GI4Sm3lr3y1X8Alxgqk4WuP2452WzukS3gaJODM+aB7a21r0YTV+rI3NLkYkWOcNqlZQb7ut5PYh6mL4eAOyXFvDhWF0yhunLnMGxfHf47NQ69aI/e6QbSe+ZCtdZih2p4+pHvhb1h0SPbIWHQVc5si0kZtA+oFGRrOWJRMtDeQR9ptiWHUX86JYn6+HKX67TJna/IJoTZb7Y7PiiefvgaHDdMxYoSwXxB1DOozafEuGDyeeB14QaRqbl1hUgCS8bjWXfbATPQO5VT0mrJr4BRt1wSS17OTEMKVFqN9F9Em0aFj1GRDkHF3sJqLqNySw9fH/37PdyRq8fc1ygzXXGCDlWMdABIJGYdeuxLhMCMhaUtCcLRr+ydVoRfm1L82pisT85S7xHItAxjtZ8Z3NZzfmQrWuuOHleheflGgyuMMpQl/RASCjl8zs75ucr61+CUe5QiXFSi9budfDnkVU/089D4RZIbvBtzAv0sHWpdQIg==
*/
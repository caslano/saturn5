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
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
*/
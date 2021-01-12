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
++c271P3Zdjp1RMZip7gwWmO12fVqxevB9RrAK8/z0iRmVcy5CY2nwyqQtCreG3mkX7JGy36E5JPhPP37EI52v2YUhTQ6qGa5AH6ZtLqT+H5SvhOMfCfWLpq9eUkGqwLJtI/O0kdWM1+LsVIWF/vFUDdNEEaCiUPaAYnKb0mR4yJ37IM5+SJSpHpOEI/34d944TO/cod77AXb51yQ+C6gJ5Zjm05IpG+WyLx1nkD3pBlPqjN
*/
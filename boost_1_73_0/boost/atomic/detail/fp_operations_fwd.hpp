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
7Tbh5awdQ+uItWO4khtSVbJb2Xdyo+7aT5GLvR80/io5feroPlamgP5cCj01VcgvpNCTUt8vSqFuVejQMewp2fsm+Ydp107LvJNlz8nkSnjGRBck90kC6yTsblWrYoRwj8gEcSZQdvIutsn0NWP1egs1/lmNeRNk0Nd/nhWpUeGG1P1jCFLfQ2r8U99/UeOPb2F+h5ag9uZK/WrXCK2vsj7WSlGC685rU9OZ+5vlIl2OtpQk
*/
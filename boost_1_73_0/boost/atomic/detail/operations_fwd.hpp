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
t8a59kxKEdOqVBEqdZ7K9G1kajDe2jaqBkXpxIOhPPtHMP0xECq1AIaKuQFRAB/0kpG5ZzTAYjuMfPtHgfKTBIS1PI2wnr+cCCs0FmEZ+sF3k7xgEFLBQ+fj2xav3YkRSF1IOHfXWHzUoGHCHGp1cjJwdlkzC9L0YFi81M8xc+cIapvmQKigE/EZDs+p+O7lLL+kX31QcdVWvrvdvDeaa/8zeGAhSheS1pbex/S570kffJ/0
*/
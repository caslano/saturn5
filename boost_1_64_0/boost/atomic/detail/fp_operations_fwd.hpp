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
rJ5X8dEKxGh91QsxuWKLYbe9/4Twn2BA1vj2GeybeS5iGF5OXLjluRDNY+0omjeKO+KGw4NlQdPkP+Q1ma15VQWm2/3m8VBID0sifmsBo40AfP9y6myYJgoCX9C95RNGO5wUZNDqL0zIrSmuC9Ow/YkPD5h0aJHC8SZmH9zfU2EfR/Gm/+Smj3K+yVAlgeswZKLnkJJPcGe/28JLwkqF5wxyxrk1OWVt3+KaStK/21/UFjdLr2qO9bH2QykYoJ81NiuB3zJW5Tqq43YUaadSNigvhRa3A3ICU5GlkrBhpgLhbrxP6JhEjB+cDlPKZ7a4sV6A7C9ZeblQ75a+bVK0Sgk/j/LUgSavwx2hfqrUfWqWsyhKGJxc3L/oxOf+DlqYqjnSxoOoOp4ySF0Mpy/09wj69ZagmQT/BWOWWYMEfYlKpQB8FVPg06gU0xv1nLW2uBmG+VgKIQ7hcE12xBSDIC/NI7QI7E5mtzF9OmpJUL/hSuDVTYE7Io7JSu4rJ8gMRaIp4zSYlKLCMJS/U9m4ojGz/bPAYNhhgeV2LTvc/TE0lSPf3tc76DljVg==
*/
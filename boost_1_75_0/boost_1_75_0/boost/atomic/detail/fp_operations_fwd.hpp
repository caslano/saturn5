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
9Z2FgGAci7kmZGlNwsYJvxi7bzbO7Zpux9o+0jXlNwl+LTSv9ksAa1LKqc/WAtWZdcSi4J9vfLuZAe6j8+2Qvs7+g0oYMdfpIkyBkyfKFw4vh2GPtG7JnTM+0TtUoFKShxBjQg+ad+5R7hwR1U1wVkYP2h2LFxrb1JHeHIDqJuTa5I7klIzqmNT8DnCGl+whbWB6p3+mILvTq8qnrQ8aYtQ3Hd9/MddpqxzUt/vziEmAkuY9LqQc5FNoz44FQiDS2/9jRgy1nQVvTvwZO1gkT5hYj/9jItDgBPgkR5UdoLx9hUaDCkrlz5M5OfRQv7KOrwtr4TeKkFlEYH+pXJEFfvQtky4E+1knJG04dz+wt8UFxNYeGphcPK+udR3VN5JyvnUfUYs8oQVEO20/ZvG0Xe+MId/fz/lKv1sMD79fT3DFiVShjS6lrWnaNjvxTEq4+At+lIFSQBOFuU8CRv7sA1DqK4MP/VWFfVG76ezNOOqIWbMnZTXe46YmzetE7ugrvV5TZCtJrvJ6OPLOPfB0J3fIMyO2OKfGiomds/JhyQT9GdyH3LpTw8+70GQEZZun7q+wsUlCzFPFvLf+bqTEJSIZSvmDogLi8Sb6fnF5Q9CuOX2yBqX18/emy57iNb8iimV+1RykTGSmDu6nEAiE6J7l3E/vXuYsdfixJQw6iUeIR9we+R+e2ivSlvOGDN+X/M6dz8XP0fJc/HPA
*/
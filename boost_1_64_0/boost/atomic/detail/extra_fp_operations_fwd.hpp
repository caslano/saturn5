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
mhWUH05xgiLVYNA8I6YmekHB0QNjo8Ov7j/jUMBfhjdPhKqyVuhah+9rghPCCSDDF8+FXSne3Q9xHfJbCRepIrSjg6iUyV0pJGdUK+fFUorqkQmL7Te2D29t/LPZ0XMNRD7o8J5rTOPwPlaNplZ0VzrFrgQwnoN+hxRDTrLpyWd48j48reox7RT3+7kARGuHjv5n6/QVIgjksSt3Ok4nxYXUf2ruz20HcxvZAL9aohs5Xp92JmnVdclpZNZVNwGcVO3MsbesRk3p3UZ9d/0vge4/YeVuO5xD4lp2naXawEvy3AVDX498rdRNkz2uZi5Mo/db1Lk7kY6zAnejficf2793yMe9GQ1/AqoZUa3DUheHGd1ghqufVeMuxe9rWQj4rvIcp+edKP/0zO5Ld1DjKAVH2cQLjr5t+yXwPqMC4LT1zs6OIJ34IJqIosy4b3t7pkQnbkldF9Lks480CT9EzJnGEAO9sePVZ3jJXdaaljNJ1HqkqXtXQVXG4PnedDTWeVOp4cQL34yfhq83UmnxllZwqKHOzPQYPZvx9ruN3Ku/JI6riKFc7RHooQ==
*/
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
+1wLkBVlAgd+AnFyAAumue7BVZx+nV6mcOXP5/4kvYHpF/AnN4R1EU9CqjcnJgX4WCvUxKyAr2rBsXCEv+7yPP8ynY79iyibztJ4OkngEyylQn5XQSW1KXiVe150nc79LIyTlF7PIz8cR/1VAWN2j04FfGSUHu4NFLV/WP15Crce7A0VbpVatYbiGxx1gul4NooDP43CLLr26SFKutDPS8zvtaIsDiGpMafmANmQIFUumgKpX02pgdTalZyKRxVXKJihlrblPOoYWWcEUXDVtT6EtLUtGi4Ka+1ZP5qihrIyJTUyya9bbDc1sEAhqzvrZ5tA8IViakNIC+RkpoZXWBmxAYtpXCYGtW0Au1ONTOW2uxZo1f0e4nkoV+50qKXWfEE4TChkBeFRR1XaMCH2U603hLzaNt+L3Q1aVagJichy2FH8XVMrURNXTDzrZoXXVP9xFsxmX0b+uS39cfwqnOeN4s9hPCePH4QbEIOtjL+WvGjpQC60FEiTqk2zXL7g+INIwuByPsom02w6CuMo8Ty+hMskap0y9zpJ/TQOiPcn4fv3WNGJYZOYKVxTEYCMCSwVDfq2OI09Ha0cJCLlWN2DYXS4GO05T7upzyN/cpH5aWZnIY3HUdcChlgTOFY5HTBtktG17dI4zSg2
*/
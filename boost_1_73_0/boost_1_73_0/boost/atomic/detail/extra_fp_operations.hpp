/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_operations.hpp
 *
 * This header defines extra floating point atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/extra_fp_ops_generic.hpp>
#include <boost/atomic/detail/extra_fp_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND_HEADER(boost/atomic/detail/extra_fp_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_HPP_INCLUDED_

/* extra_fp_operations.hpp
T40GxdnInjh4KueaR9TZWHZydgQ20xtEWTL5/AQci2X/FiiRIA0TdG7E1KxD7XI2yxftGc7qFiaLOIb7UlLsl92zjLWeUCs78Ot6b7yP13wxzIKAQYFEVCiQaWgNpQmT9/+GwLLl8mfcAsvapR1ClbCjbZnWUDRFhIalS3CqrXWJ1lDJrYfKbXAdTRr4hTYPuxdB7Dq9KNLjIHkcbhxkL4QjiEcuvTLomTdXtpzHDoV3ebxJThkPn4+adXjxkbQ=
*/
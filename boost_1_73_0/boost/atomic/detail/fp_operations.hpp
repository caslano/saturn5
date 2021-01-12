/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_operations.hpp
 *
 * This header defines floating point atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/fp_ops_generic.hpp>
#include <boost/atomic/detail/fp_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_FP_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_FP_BACKEND_HEADER(boost/atomic/detail/fp_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_

/* fp_operations.hpp
9Y92p6Ky306kW52hTEuvAxSLPzJH+4vsqLvgnvB1VG8ixge63+7C5xQ9sKx7u2ndW6X/tqp3m5F/e9q3RYGK+45o+7Z8wVo535Wq1+EbmGEohG5gp2MEtwyCtTAnhUYjzWRFzA1Lu7UfekIoXDdTq5UkHMedism8+bvWLomJAGK92jDJvoFSE1M2AQkEh0rj+HSrBZdc7zGxw1pOaVaVe+Aa7WnRfrj9Nqv6A9KcrtT3oDSn
*/
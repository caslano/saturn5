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
VzUBs8laecxmquSW3nNnh4PuKrffqRX8EGp1oGy6u7y8iiYSqHJXeMKzgryeufQZ308YpjHFCVvz7JbkrQx5KmiRsSBD/Mrq4rzmU2yjDM0OepJdYg7+7nPQn6Ox2yi8BGtm0jJwcU+64soYcqDygcqFcCsma224bU6iEE5Bgh+DTAmW6Ow6m9J8gcD0mmBSv0CQMbbP9aDRJw1SECxWhIM07AEk6FIq0Tc7s/RdKS2W8Acplmp/bnKKyrFCwOQ=
*/
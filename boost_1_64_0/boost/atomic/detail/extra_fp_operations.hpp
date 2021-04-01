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
cBcz6Ggtxrdx7UXGgQXtU+d2mZes1YiQ4RoH4rt5U9MH5EBG19R+SnK2yet2WQDwWSFY7lW87RPaVGdeltuO9o2OUQ8XCIN4FXS0kWo978PpcYSiyjueUW3E17rqLseASqjRk3S76/kySZcVyIL2SIH6h10KAzA3oMD01r0idvhJ/Ra+1SPtt677r7BoecuFH5CwABP9brYlUyUWRdm4gKJ5BP7mRfJ+3WJ0N0m4tZNABQ2mTnwJwgwLgqsSwu6QfYGXSOUF//kQJoQQWFVOXmrsqYGJNlY621EDHAJKcU+8NpKcKroUtG+3uE2NVSLcNeBgM1YPgiNUr2/+kuqlkNwLbUyi8dXODuWzaZ6IiWAAQITWXBP4qE1jCQUcZsm1S8z7ncpZRxHhBheKiIUTclQX4piWqv2+hznnDt/XwGUS5XKyZdFOHinLvuf32hqoVULkG2SIJ2CKUmQguChKyW3Xj5EEFezjKtlqaDZx55n5GW+pGkJrYhVc0uTj+03NAgnJSS0KKvLRKjHsUuyzy4a2rcBezidpaFX2BQbBHn7New1/0r8HegyvEA==
*/
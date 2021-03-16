/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_operations.hpp
 *
 * This header defines extra atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/detail/extra_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_EXTRA_BACKEND_HEADER(boost/atomic/detail/extra_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPERATIONS_HPP_INCLUDED_

/* extra_operations.hpp
qw/L24d6hA/P2zeVTRrZWkwF6Qo6+TbNH2PVxlQiVUNZu7OpxKqGwpN5tVjVUHgSoNfW8RTg8OD9K7PaF3lR13I4JEU+RUbirJRV0dTb6vAHHX6Vdq694to/mfmU1b2yy08GMJ46PDYD6mMCNw07UVWhzxJQPWGrW8fzwwW3ojcMh/P9LAIH8weRbVe1WFVh6KhSPVpVGFlSqkWrCptKpZGD41SQrikJfajjmoqwD+/0/Jh+XveU4+b6ea06nYw=
*/
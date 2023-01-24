/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/operations_lockfree.hpp
 *
 * This header defines lockfree atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/platform.hpp>

#if !defined(BOOST_ATOMIC_EMULATED)
#include BOOST_ATOMIC_DETAIL_BACKEND_HEADER(boost/atomic/detail/ops_)
#else
#include <boost/atomic/detail/operations_fwd.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_

/* operations_lockfree.hpp
luz7+zA2mJna7qs9wWhzZxAwgz3L0z0LgfDsHN57QPlLGb4tRSI5m2JjPrwUbBllVnSy3dugOzgnMLgS1Rl/Uzv/BihbW7jnlX+vU/7kUgZf4g8q3i1CRwXmQE8QxYeIQIp7DBBKokx8L4Vx5kI7EArTEGeIPSDqhEvCEbmIsWMkEi+fZdc7PsQHliSXnajMWJPcKxMtG+rZmETB/IfN55SOn4nKBwWMgg3F0y7yV/hF3J5hxtHk8sFbquJfG971jvLmjgyWFHaTsGbqkr1KTUFNztQeHzQdiHihH65pzHVsevp+iFVQC+VLTFCMSr63ZkxQ4Am/ankpDpoco7MDizc7jNzl3qfPL+qWriJWo1ZSwNsTTHAQFz9CblKW05qm3AJ/hjQ0Mm/0DcwFswmg53igfPCjwKW6zHXkBz+ozHSMjQ5Ho8LJz08rcRNQtikkz5eabtxDQLSk+CAsuDtk7yHa+npMnOmSaEqdqNu2tjFvT9Lg2kB/T964MkMq0O33Nmc6zghF813q+WzNsW6Ldy162imlbqhQhU9L4Mz6iBPZSWTDHPrMi7G5XyHiQkO7sNIdpDMw/kFdN8gvAQXSM3os9JiZZjp0PK4HxtA4rbRVHStqtaI+6Cszhd0UUtp9m3aYZfIe6DX0L8GxjTyCx9EMReSCZmf6feNC69G6l2YHqkRavGclPKprrMNfO1Y7QzqmIuqXDEVxBZaO
*/
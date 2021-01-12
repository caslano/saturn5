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
6r6Gl1c2LHsRRDHBiNSxwLZAAmMWSp7cVyQ/MvRJGRJqa0hvcFvL/lB9IAwgheNCGBiO+DKp2LRc1UUNEpbPP8HE0/JUeDn71OIlWj3SidNyVNzJlejWDeDX5BiIdW11pROYavhZqEK++iRPn806SSenLFcwoVzmSR87LjzscEYXwGIFiEkh+oa7+oQvAMpeWOttWFEfxind578AFomsKqoC8kpCBnsYnX2r8Hai+wDTCXNq
*/
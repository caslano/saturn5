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
upuokEMsV4geX5xvq+rExhn+GLjq8KKdCrx00GxuFCi4U2Pcd5bc7ps4TDBundSboWa0g3Ipz5fk2qYx1p8EaHxtBSsPpIb3QVfLxeeYa0f9wK5j1uEP2CHVpdSP3Xwy/Ff4DjuouJOCi2SPxTwfdUIe00c6HwU1jpOfzkdz/B/TxNDxur/E2tc/bsFt/J0mOy2Y1nLR6x+iMicTkQxaB2C/5QMifofQF8m/UEsDBAoAAAAIAC1nSlJ9V9Da9gQAAOcKAAAmAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9NYWtlZmlsZS5pbmNVVAUAAbZIJGCtVt9PHDcQfuevGIWHJtXtXUJemiqtegKaojaAgCpBQlr5bO+ty67t2t6Dq/jj+429d0doKl5yCDz2eX545ptv2P/+23329unZT51/a3ywssJ5cH9pmb5+ua4fqPxA6QbrMy5mtNN4qF/RsxoP9DJr1KOP9yzX9TNubjgw/jNjxZuaRZzs7UPv0Pl1MMs20cvDV/Tm3bsfqKKD1wevJ3QkrNEdXSZtFzosJ/Re5ZNfWnF/P4365wnpRKKbZkNXrYkUXZPuRNAEuTNS26gViUhKRxnMAhtjKbWaGtNpOjw7vz45/TChu9bIFjbWbqDYuqFT1IqV
*/
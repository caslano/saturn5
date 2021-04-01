/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013-2014, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/lock_pool.hpp
 *
 * This header contains declaration of the lock pool used to emulate atomic ops.
 */

#ifndef BOOST_ATOMIC_DETAIL_LOCK_POOL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_LOCK_POOL_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/link.hpp>
#include <boost/atomic/detail/intptr.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {
namespace lock_pool {

BOOST_ATOMIC_DECL void* lock(atomics::detail::uintptr_t ptr) BOOST_NOEXCEPT;
BOOST_ATOMIC_DECL void unlock(void* p) BOOST_NOEXCEPT;

BOOST_ATOMIC_DECL void thread_fence() BOOST_NOEXCEPT;
BOOST_ATOMIC_DECL void signal_fence() BOOST_NOEXCEPT;

template< std::size_t Alignment >
class scoped_lock
{
private:
    void* m_lock;

public:
    explicit scoped_lock(const volatile void* addr) BOOST_NOEXCEPT :
        m_lock(lock_pool::lock(((atomics::detail::uintptr_t)addr) / Alignment))
    {
    }
    ~scoped_lock() BOOST_NOEXCEPT
    {
        lock_pool::unlock(m_lock);
    }

    BOOST_DELETED_FUNCTION(scoped_lock(scoped_lock const&))
    BOOST_DELETED_FUNCTION(scoped_lock& operator=(scoped_lock const&))
};

} // namespace lock_pool
} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_LOCK_POOL_HPP_INCLUDED_

/* lock_pool.hpp
uRQ07PVLfIE9+J6oSlHyvKV0nSJ2ZNq4CqkA8pHkWiC7VVWlfkntdUyBbN3IObEp3J5ktDshW/ICfU/ZFV01jc1dtvn/BRskryfwGnYM6yjumuVaLLwbG9kDojRG2ZH+K1lEzB9qYNmG1ZnquvnM93Q6gDRvNZCBCzb9ZIiQG/luW7aGopzAWoz4+ujorvu/mBpVRItj+PqQMxTPe/llhoe/QyPLYfyvn2iypNIKVC/e9jfI5XDXFSRCI1zF9FBMRWbdrnLmRAuLvkCS5ZTy2PYACN+IHHxcnBeKsRZT8tiDhe88QuEyps1CSzB62xW6grb0U/9KJaF92CCGuJPc457DZ8pX3X2P8WuEPuu4KKDCA+1YFddDKFC410wjhUBwN+FD5a1DLLjNM8I3gepblyQk0RqUQYrXuwbbxYvApXVXR9t9SYd2Pyvxz5jfrKm5ONfjeOeoDfvnNKkFyT+4Oad+BpiorDq4Q56mSQCW+RcbhYaerkqZsythTrkpwIHSAr1/Zm0Yl9cl9qmhROZcfs0xjLk0u/mWuFRZFPIjgEYA+1XONdE3ozrkQw==
*/
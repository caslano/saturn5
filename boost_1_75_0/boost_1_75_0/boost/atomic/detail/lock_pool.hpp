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
ddk+qUDM3lds8p19hV6R6eTF8PU4ZXv2JpKu7uFcUTEJ/7j74ruOOFbGaQmv9QBRhwQPcKNN6iC2za/VS+0J7skcfumQzxgK+tNmXQYcjHIsrxL5Xj4mcw5fuEx8bpOeYwX4WDor6Phc/UwQ6+Fkvfk5nfKDf/heHopJZ4snEc+PD4zCZ42EMI4Ei/Gy/KV+YqX701yqXx41a8iqIjMA4Lc52jJ6QeyUjX+nSDxz9ePAhzMydU+Z/Qg3WMzUXI39KLsTfZLfmBYeKeC56QN5z6e8sYNtEvFSEftCarjmrn/L/c2xPU0D5r0BiyTRBEHIpbQXFkc5LF4dH2CwvNZtI8SbCc4GdktQm0TYZo9Mzn8I0RJKHsnPhWhUPsBhnwZuxCFRSTjbocHikOcV8mel5uJtI8XWOyWfo7bd54lwyaA7M3zDD2qPQxIGTj8bQh5VPP8StBohzTizkcL4hMR/NtiRmMgJg2X5FXffU8677uh8xDQZx8D5RQsK8dj7Bhq20Uq2rc0k9ldcdRYjRob5HhPJrDobUXjD3eP3X1l/3Bn8A8AeRI1J/6K0AzKHaZm06ctxLrJ11U/Rr/TTXh0Y2oLuzVj10+SHH5234HngL+Dr/sTsVQTOedYb2MegJwunoBSi/UoIjkrqkoQom1/8VPYUvmo44r1Tmo34sw/O+Qn3yc1xC2JwcSGwtYJ441cndHiZWJL2C7n/GWn3
*/
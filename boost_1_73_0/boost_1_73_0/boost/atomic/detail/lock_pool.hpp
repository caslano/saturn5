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
quSdEkLCullq5avkwRuiMjK1DjxqzVhkp9B3biMs+vQkrAY1eawCb94az1Sbyq4eKVIeGaVsnCEiygMpSUtpTqAxEl2r3Ea+p+hz2ib4X0vz4K8Ea8gZGEwWcLkYwFJ45RP4dJldzD5m8GlyfT25ym5g9g4mVzcM9v7y6pxKr4jMAW5rh57IHahVrRXKnvPHrTRKj2B8/nYxPWP6iyybw4bYYaLD88W6AN/UtXWBL8fpXi+NnilT6EYijH2Qyo6qswMRd0HXCiSOlAlUcGWGa6tkHP0VAUw/Xn+AI9Y47U+FldyP/jQiAV/A63bLUfhdrowKw5h1VTlkcQwMAwcqHgN1VHuZtIizeZbTlsBg35y4FZRFHBV2NYhbInopqIlEwWWuuK+p2EYEmgnfjRJVs50livg/0E0+ZIvfp8RIQH5djMI2HBJReNQX9Mi1A9nlek3tqfr+pFF47ML/Yc2nGQc71NbcxdF3Hys26JUvXtwfnk4enX458HmOrrSuGxuHfzYUQsKBUJNoDXf0RnU3gWYI2iL2TrPOYQnrDqir3ukeflph8RnoAtA5676GTGVmgJ9et06/zWfv9zGVtaOGKofUdmRCuf6WIoaSniaUr+Bnf2sGyT+ycZDO4Fpa5ooPghZ6I3YeCo3CNPW3
*/
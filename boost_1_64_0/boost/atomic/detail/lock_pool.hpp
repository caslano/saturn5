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
E4LhbzikneYFiq1/Glvqc6QMPRPCc9jZKEPY3jVT9meataL7Sfwsvnky85KR3SDHD5pvSK6V+GXGjvM9Of537S9ZH1gP2OnGXvkh0aUHKSdyxJulfq9hkfwjs275JsnrhQS/uTYL7pQ8Ahq3rWckfpP0y1Zpw/L6lVZ4Pe35bWVNDOdXHFHv424O59eLeJLGsyQe3Xcppv+nG1+xM0VmYfB8q0uwt56z75Fto4IFpKjApvpK3saGfCcVSZn6Jnq/2agkrwck3TIrvG+RKduN0l62HRoPTdLOB5DGP53IhPr+vMAY3sSJHLHPSxs9xRkpx1X+s429RK0c81Pm+7/75DipVm+1ez1V8lwZqLB/Qs5p1uIAPladtNSzVdJ+EOhi9ZSVpi+wmgKHA0H+Iq3p42/ZidYf0IYc49fwHGmDnolh3T97kdu2dKbsT0wMl7fG6NsuOebtHMOt7wODjr5fFDDzlOTpdHY3bS9b2uEzOp+E5rZfytwWbu/lRjfqpAypxg/kWolPTMjjZWi4XFPN9dUh2f9YcI+VEsxSX1onSdnWBObRbjW0m8ga/WgNJmEZmyGy3rl2qth8TpE8B7v097wI/f1Ax2KWzq9/lvh3gkHeKBbaDegc20N5U+pNXC8MJF0PEv9tYJtvo5Lu7kAeGoYiM0DD0myN69/72f8uweFkGucJ+BgBEtpkL4FlnvBXDVl6jdJ4lG8Sn/mcfpNYvUDiDxN3f6PYKtcBHff/lpt0zP7fzDXMIZ9rmMOea5gjPtcwlu25hvFck2zr7n/v0LrF95qkfuGkmPcOpIm8dzhh69HvHVq3HP3e4fktUfcOpDv6vcOvtkTdO5Au8t6h39aj3zu0bun4vUPrlo7dO7Ru6fi9Q+uWY7t3aN3SsXuHK6Xuw1xtcfR7h3FbO37v8OqWyHuHPxD33jvcFL938L93iNv7fSL2fmnnO9vPzH/2+fVr0276Wlr9CzcPuX1o3N6vs/Z+71iUNfQ8Q88zlfzRDa52rQGdA/NgfzgMDobD4Sg4Ap4BR8L5cBQsgSfARRqvg2Pgt+E4+D1YAH8Nx8OXVP4dmBzQeyu9F6c82NWhu9DSNYWHwWI4yZGBZ8KL4Rx4CbwAXg7LYSVcBavgJrgY3gWXaDmW6vGr4ZtwmZajBv4L1sGg2r4Nhw0wHy6HE+BKuAauguvglfAWuAa2wLXwSXgVPAgb+f+f8Bp4pfp3aoKb4PMaPwhvhMlB5mCYDm+Dg+E2OALeCvPh7XAWvBMuhHfBK+EO2ASb4dfgvfDHcCd8AX4R/hnuhu/B+2ECevUl2BM+CHvBr8LhsAWeCB+CZ0In/4vhNXAtvAtuglvgffCb8IfwEfgC/I5zPPhdmEy/fg8OgK1wGPw+HAd/ACfCR6HqJ+fM2Po5SfXzNNXP01U/z1D9LFT9nKL6OVX1cyZcpPE6OF31c4bqRZHq59nwJZWfG7dtits2xW2bPhbbphrslLYQ9sXtleK/+C/+i//iP8v6BN//V1VX1X88/v82uvz/7dP7ll8SMvXbi+MLyHuzeYanx3Y/u1q6bEGFWQdGZXtaWfq8+lWJf8eayL9fJWSonw1L1zaQ7yj1efmbIttijaRk9xIG8WynC/vPyQuvE/Q+4eEM4nBOB/wTOM9bG2+IfN5aaJ6ROGWPPx/5JJ6PTJHnI4t7bt634tsPfX7KmP7rLl0XfCb+fOSjPB9pDo0/HcOVHj/sGc79MuwJB8EsWAh7walwFJwDc+BFsDesgn1gNRwMV8MhcC3sB5tgf9gCR8B9cCT8lub3Q5gHH9P4vPh96X/kvjTu1/n/+x519FXxe9P4L/6L/+K/+C/++yR+/737/wUV5bUfz/0=
*/
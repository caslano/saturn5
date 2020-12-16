/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   locks.hpp
 * \author Andrey Semashev
 * \date   30.05.2010
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_LOCKS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_LOCKS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

#ifndef BOOST_LOG_NO_THREADS

// Forward declaration of Boost.Thread locks. Specified here to avoid including Boost.Thread,
// which would bring in many dependent headers, including a great deal of Boost.DateTime.
template< typename >
class lock_guard;
template< typename >
class shared_lock_guard;
template< typename >
class shared_lock;
template< typename >
class upgrade_lock;
template< typename >
class unique_lock;

template< typename >
struct is_mutex_type;

#endif // BOOST_LOG_NO_THREADS

BOOST_LOG_OPEN_NAMESPACE

//! An auxiliary pseudo-lock to express no locking requirements in logger features
template< typename MutexT >
class no_lock
{
public:
    /*!
     * Constructs the pseudo-lock. The mutex is not affected during the construction.
     */
    explicit no_lock(MutexT&) {}

private:
    no_lock(no_lock const&);
    no_lock& operator= (no_lock const&);
};

namespace aux {

#ifndef BOOST_LOG_NO_THREADS

//! A trait to detect if the mutex supports exclusive locking
template< typename MutexT >
struct is_exclusively_lockable
{
    typedef char true_type;
    struct false_type { char t[2]; };

    template< typename T >
    static true_type check_lockable(T*, void (T::*)() = &T::lock, void (T::*)() = &T::unlock);
    static false_type check_lockable(void*);

    enum value_t { value = sizeof(check_lockable((MutexT*)NULL)) == sizeof(true_type) };
};

//! A trait to detect if the mutex supports shared locking
template< typename MutexT >
struct is_shared_lockable
{
    typedef char true_type;
    struct false_type { char t[2]; };

    template< typename T >
    static true_type check_shared_lockable(T*, void (T::*)() = &T::lock_shared, void (T::*)() = &T::unlock_shared);
    static false_type check_shared_lockable(void*);

    enum value_t { value = sizeof(check_shared_lockable((MutexT*)NULL)) == sizeof(true_type) };
};

//! A scope guard that automatically unlocks the mutex on destruction
template< typename MutexT >
struct exclusive_auto_unlocker
{
    explicit exclusive_auto_unlocker(MutexT& m) BOOST_NOEXCEPT : m_Mutex(m)
    {
    }
    ~exclusive_auto_unlocker()
    {
        m_Mutex.unlock();
    }

    BOOST_DELETED_FUNCTION(exclusive_auto_unlocker(exclusive_auto_unlocker const&))
    BOOST_DELETED_FUNCTION(exclusive_auto_unlocker& operator= (exclusive_auto_unlocker const&))

protected:
    MutexT& m_Mutex;
};

//! An analogue to the minimalistic \c lock_guard template. Defined here to avoid including Boost.Thread.
template< typename MutexT >
struct exclusive_lock_guard
{
    explicit exclusive_lock_guard(MutexT& m) : m_Mutex(m)
    {
        m.lock();
    }
    ~exclusive_lock_guard()
    {
        m_Mutex.unlock();
    }

    BOOST_DELETED_FUNCTION(exclusive_lock_guard(exclusive_lock_guard const&))
    BOOST_DELETED_FUNCTION(exclusive_lock_guard& operator= (exclusive_lock_guard const&))

private:
    MutexT& m_Mutex;
};

//! An analogue to the minimalistic \c lock_guard template that locks \c shared_mutex with shared ownership.
template< typename MutexT >
struct shared_lock_guard
{
    explicit shared_lock_guard(MutexT& m) : m_Mutex(m)
    {
        m.lock_shared();
    }
    ~shared_lock_guard()
    {
        m_Mutex.unlock_shared();
    }

    BOOST_DELETED_FUNCTION(shared_lock_guard(shared_lock_guard const&))
    BOOST_DELETED_FUNCTION(shared_lock_guard& operator= (shared_lock_guard const&))

private:
    MutexT& m_Mutex;
};

//! A deadlock-safe lock type that exclusively locks two mutexes
template< typename MutexT1, typename MutexT2 >
class multiple_unique_lock2
{
public:
    multiple_unique_lock2(MutexT1& m1, MutexT2& m2) :
        m_p1(&m1),
        m_p2(&m2)
    {
        // Yes, it's not conforming, but it works
        // and it doesn't require to #include <functional>
        if (static_cast< void* >(m_p1) < static_cast< void* >(m_p2))
        {
            m_p1->lock();
            m_p2->lock();
        }
        else
        {
            m_p2->lock();
            m_p1->lock();
        }
    }
    ~multiple_unique_lock2()
    {
        m_p2->unlock();
        m_p1->unlock();
    }

private:
    MutexT1* m_p1;
    MutexT2* m_p2;
};

#endif // BOOST_LOG_NO_THREADS

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_LOCKS_HPP_INCLUDED_

/* locks.hpp
/rn8MzVd7+CzFufr+0d7Ht9z7hh3XvvrbX3tx+V6W6Mlf0UXoL6zWVnF9zZuPeWEo9y7iUx95x6vjuKQt5mDT/7CHZ/8AqbD9d3EwhiDa7PzveNkuTUd72mKPefCseeaC7+2Gt8SIAyEmTDo/HiE/e6g2PWub52+42+LWOzt1+fIvfU9aNb8/EC8uiXKexMW/nrHCzdVfmeN3Wq9s8a+673cVY2Yr2p07ncDVnoQduIuYa/2O2MrrTpp4WkQgNgdib8lp2ta30zIKSqsWlrhxpW3RxKqnreOuLi+6dBK1yTMR2oi85Ce2N1jh2/Owny32g3ub4V1ll2nfif2Z7Pe1fQKu/pnOtzO9sxjtaf1Utamq5xbZ0VdV1xnaRm2zmcH6qjGe4u+y/+NlpXHkGFMoud/EYw3LU62tH9aR69tLWv8c5z6N0rE/hbmi2uxRrOGZ9zzHWX8QyZuMWGxf3DtxBq5vsnIwfbtiPN79bPJMef7yqfEbrT9XWu/nz3F7qxc5/e4HxN7cfa3sVuQnrUw38sN1zVn/S2yKpnwk6LXCQPpq2l61u9i+9MhnnRwfq+a8GJmhVfsyn17irmEzZX+x/Vd4XYyuT7cBv3pn/mlM/2zF3mlv/MbFnli/xOzBenmkfbqn+mVpmL/mKahfqefG+o7WDWPa1Jxb8alX/n9PN+Uc34d+5pzVhbH2nmxtGBWfgaRDq57KZRw3BrWBN+D98viI/bB/SkXiT/t2c/l03y0/G6g6yasMNLWOPI68W9+O43s8N0qbi6p4EeF8Oq3ROqJ+699q82xZqzsPbPCpvfBXhn2VkgcSsM0LFY8F+VkBfelZErarDLl3L5XKyNYTotIl0AaH9U0niLm0jbZcdgk97rUiNUwz5Uw3utrbMzx4UbzUpLPTr+mcq8BtDHd7PfrwbAuyJqbUbQsPzt4j2vEzxcNr3yc09Bys5DYBe/xgbjpzdAnVu5xnHuUq9d2m7ha4tAsLNKooetTrHu0dOzrKVii++zkm/El4madI41JlkA22N9++ZGk8RLZ03dxoO7nkQd2XdeybuUPeo+D62O2yv0HeYTHWT+CaXRKwlPgmQ8P0aZ00DblZcTfpnyRSIxoqDLwax7ny+EyNVtMJzi5YVDW1g9wRgLr/LF7C/I86bhQ7AeureL3flgQC3FfynnfeNbF6/Un8GM30jEucH4bfvROcN2TNWKEKz7QvrU6x54m0kP3NFXe3h3zbu+kzaBeYy7tiJgdtdtAKfe6rkLda/nFTylHlDnMtMw52tCLxa7ksavvnl/PkCObANdR7u7Oj2+cbWhhdlFGfnZ2gQTU7oNMKate4wx1zz+ts/wi6N5jMuy621fTmSZa5krEzvW82z3PY5zmvp+2cZT4YPu2Wa5H2u3ZK3IeZdeZm+X8VXHfUDJ1lqyZsvrIWEcb408J53eS2orbgeYfsW3dH/fSUFj3v1DsJIp/ZfhXG3sfNBD/7DqX4Kw/uTlzMhxpEAcbih9jzTdJ4Qp1X/v2MUYtuY+c8+vPfjeYEU8pH8lyPsx0tpnOvjArkI7mElonr7ZB20N7/aamhT0O6SDu+5kTyak/0CtzXynr14n5UWM49Z3klTrev36gzl+fHKyD58s4IlDnL28QeJZqVz9gtg95Frm9eaAeNjlHPXztm4r10F9u47XcWuNxe3zhGI971E0pBw1jxK61nk7yUtbeWfmt9Y289bvXulqx/g3U+rcr1pBjuo97K39D/dtDnrnrX+DZmtVPc/M86qC1Z/Ni0+/uj1772NVP03McFAdfkOu1zElGa896qu69xh6S9+/K9Z6+DFx7jgG0rn0g9rr5ytUBSd9y/bJdf7b4/G5q2/U=
*/
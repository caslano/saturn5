// Copyright (C) 2000 Stephen Cleary
// Copyright (C) 2018 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POOL_MUTEX_HPP
#define BOOST_POOL_MUTEX_HPP

#include <boost/config.hpp>

namespace boost{ namespace details{ namespace pool{

class null_mutex
{
private:

    null_mutex(const null_mutex &);
    void operator=(const null_mutex &);

public:

    null_mutex() {}

    static void lock() {}
    static void unlock() {}
};

}}} // namespace boost::details::pool

#if !defined(BOOST_HAS_THREADS) || defined(BOOST_NO_MT) || defined(BOOST_POOL_NO_MT)

namespace boost{ namespace details{ namespace pool{

typedef null_mutex default_mutex;

}}} // namespace boost::details::pool

#elif !defined(BOOST_NO_CXX11_HDR_MUTEX)

#include <mutex>

namespace boost{ namespace details{ namespace pool{

typedef std::mutex default_mutex;

}}} // namespace boost::details::pool

#elif defined(BOOST_HAS_PTHREADS)

#include <boost/assert.hpp>
#include <pthread.h>

namespace boost{ namespace details{ namespace pool{

class pt_mutex
{
private:

    pthread_mutex_t m_;

    pt_mutex(pt_mutex const &);
    pt_mutex & operator=(pt_mutex const &);

public:

    pt_mutex()
    {
        BOOST_VERIFY( pthread_mutex_init( &m_, 0 ) == 0 );
    }

    ~pt_mutex()
    {
        BOOST_VERIFY( pthread_mutex_destroy( &m_ ) == 0 );
    }

    void lock()
    {
        BOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
    }

    void unlock()
    {
        BOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );
    }
};

typedef pt_mutex default_mutex;

}}} // namespace boost::details::pool

#elif defined(BOOST_HAS_WINTHREADS) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)

#include <boost/winapi/critical_section.hpp>

namespace boost{ namespace details{ namespace pool{

class cs_mutex
{
private:

    boost::winapi::CRITICAL_SECTION_ cs_;

    cs_mutex(cs_mutex const &);
    cs_mutex & operator=(cs_mutex const &);

public:

    cs_mutex()
    {
        boost::winapi::InitializeCriticalSection( &cs_ );
    }

    ~cs_mutex()
    {
        boost::winapi::DeleteCriticalSection( &cs_ );
    }

    void lock()
    {
        boost::winapi::EnterCriticalSection( &cs_ );
    }

    void unlock()
    {
        boost::winapi::LeaveCriticalSection( &cs_ );
    }
};

typedef cs_mutex default_mutex;

}}} // namespace boost::details::pool

#else

// Use #define BOOST_DISABLE_THREADS to avoid this error
#  error Unrecognized threading platform

#endif

#endif // #ifndef BOOST_POOL_MUTEX_HPP

/* mutex.hpp
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
*/
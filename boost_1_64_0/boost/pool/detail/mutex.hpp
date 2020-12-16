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
9swxLv+z9fpO+QW6M64fwiqQl5+dkvke9RcuX971aRaJUvGpEgmfWd/ZN6kxvlPYLKO+/lI17469Lm+H6PgoLWvF6y1Z67vH4Q0DmRE0b8PpirLzrv2Mr06rFMMsnaroYXd8Jnvd71JUWVPmWWh1vfJ3fSnjj2r0jLKLPHX18m/uZfnQu7gr25zdP6E6uPpfYvxoK9GlRc75eXubedLhL2HH9XFc1YXD728DI+M7TAaON+V7en4dXBmmHr91ZGTSmdXWUdIyGdz+DTT/5HHs7fsOrdBElbceRILm38P4K6wXcRKm3jp47OHDDn8SiD5tcTJca/6jRHtetnB4s6DJygTK94bXpzlpu2XG3+K+B55jSAy/V3N79+Nmyi8C0UobpKtUEgarNbchbnHKjeR9yR67ulgxelS2vJ9nvH2eout1wvBydYn9cbvDW8sNRFuXLetvfsMr0v2Nyaj6Jq7KqvR+b3dttW/ZPd7t9yLriqzvnHb3a2Fl7GUy2rSo0IodleHXgsR95GZvyl+JnZj3YZ1y2qCp0j7pI1nfq7DaJkbOrVxOltZ5WmeQcxWWm92vfv/xrt+vLuVLDomcrkmPY3dqnLKjAD0mgslI1yTeVwvNeyfjbWvYCTkcEVB4O14dD3PnrGlf32vUdt17gjsHlG3dy1yPbO2KYk/d9jBemBcyz3ZC1y/OG2l7zeEthiSbfZWofTwv3D+mBJPRFuOdNs86tq2MZSYjC+FRKJuhja9Wj5uZjAh7sVgUTIZfDz0ffvwJbD/YVW2NsWna0t/JA/MuOuePqlKIvDb8/s4dRLqfPoHNLWnTZXkZm7a8ir3Hv7mMsqnCNhFWhl8RKmPPPldGXLWYZatetuXV6vE8LiNr4wgro5FxFXugl+5jfoM6zfDAbeUZF9490HnOn6ewDNLUMzZI8dZ2fu8+lr8tE1XfdjmdbGjBmu9WxpfJ/Mx1Hls+f7t/g7VZkqdVVrf+4bjN+vQrJkPkYSsi16z015u8cbSPvfkhH0rNy0QJ8VeevpH1RJe/r6Kkwr6T89PS6Vh+usNfy0M1UcKh758P/P2v4TLiCIMp7Pzzgb//LbN6NB1WvyJTfdjfDtRGv8j4E9E3XdQXht/fDvu0r/2jsV0/TiEL/rqMYR8PXdXNuEkXaZvKKavCXJ6mXZRLO/S/zuam/zEZLZxRcV5LGf91Njdv9DkyWvT9Lq7SsoSMq+nGRs7kSUxOA/9rn2SQczVdeWL8ZE9ivuq2EXWbUTnb2tfPc3jzoI3LLClE4+GllZjV/Ncz/jTsCnlB2s8P5Rn/psOfBnVS1JgTxJCR7IhJMsE/xazxlT2Jv5OXdFWadCM/OuH2QkLzBjyTURa1qLIslzKsL8svw7y9xerRI1K3jUpaD1+XCs2cxnUoM4T6CqcefiFWxj+ZDOkpyuPK1uMqZOx+Mts/tJW0PmviizE3mI/oG8xKRqZtLkcGHE9wzDXRsGf771LI+LjekdMHcB2E2M/0ZB/il8Tm+puezHzYrWjjuojkWnUF9v1ajw+w+pRR3nQlMEqPK4shcw9r2y6TW8k4Df67FGs/MRk5HieDP7BU8+0VZZi3IZ/Mzn0KmfAit8nXpjdl+03/uMZ97ypPoiKPhSB+X78UapO7MlBsKcoso/5Cvwz6VqwjA8uunDXCVPmO/ez0XZc1hz8JMvjgMmy0aAI6h5Xa4Uz/LuwbODQytw38Usycw2RUSZHESRN72mDbM6fvsDaQSfr7vFaHhduyY7lQ57bPt2svgmgXllWq9uG4APU1OX6vYbE8DXpL3cVTbTXKP2TmI4evDCos12ir6ArtNDVmdj/FldE1neiisva3k/8sd/9TmK0n3xM=
*/
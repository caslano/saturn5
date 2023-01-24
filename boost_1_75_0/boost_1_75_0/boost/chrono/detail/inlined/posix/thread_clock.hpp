//  boost thread_clock.cpp  -----------------------------------------------------------//

//  Copyright Beman Dawes 1994, 2006, 2008
//  Copyright Vicente J. Botet Escriba 2009-2011

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//

#include <boost/chrono/config.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <cassert>
#include <boost/assert.hpp>

#if !defined(__VXWORKS__)
# include <sys/times.h>
#endif
# include <pthread.h>
# include <unistd.h>

namespace boost { namespace chrono {

    thread_clock::time_point thread_clock::now( ) BOOST_NOEXCEPT
    {
      struct timespec ts;
#if defined CLOCK_THREAD_CPUTIME_ID
        // get the timespec associated to the thread clock
        if ( ::clock_gettime( CLOCK_THREAD_CPUTIME_ID, &ts ) )
#else
        // get the current thread
        pthread_t pth=pthread_self();
        // get the clock_id associated to the current thread
        clockid_t clock_id;
        pthread_getcpuclockid(pth, &clock_id);
        // get the timespec associated to the thread clock
        if ( ::clock_gettime( clock_id, &ts ) )
#endif
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        }

        // transform to nanoseconds
        return time_point(duration(
            static_cast<thread_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));

    }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
    thread_clock::time_point thread_clock::now( system::error_code & ec )
    {
      struct timespec ts;
#if defined CLOCK_THREAD_CPUTIME_ID
        // get the timespec associated to the thread clock
        if ( ::clock_gettime( CLOCK_THREAD_CPUTIME_ID, &ts ) )
#else
        // get the current thread
        pthread_t pth=pthread_self();
        // get the clock_id associated to the current thread
        clockid_t clock_id;
        pthread_getcpuclockid(pth, &clock_id);
        // get the timespec associated to the thread clock
        if ( ::clock_gettime( clock_id, &ts ) )
#endif
        {
            if (::boost::chrono::is_throws(ec))
            {
                boost::throw_exception(
                        system::system_error(
                                errno,
                                ::boost::system::system_category(),
                                "chrono::thread_clock" ));
            }
            else
            {
                ec.assign( errno, ::boost::system::system_category() );
                return time_point();
            }
        }
        if (!::boost::chrono::is_throws(ec))
        {
            ec.clear();
        }
        // transform to nanoseconds
        return time_point(duration(
            static_cast<thread_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));

    }
#endif
} }

/* thread_clock.hpp
/GuSUbeFRjuSPKcHSf7Yp5jgMHA3vTGURVi3xnjVlHO3oAwwyw/8WC5HpRH0tL5lk3QSQOPXSbdONb7Z+TLBYMBdUdYZXxxu0lU+/leNqLaV9Ziqt1N1rcf0Db6hy02evoaz2HTVYpgpHpjxlHTJbiFdYs0lr3/M9uA+m+wNTtvOpW1SO99tk9t5aZt3OyvjAmunJqGWdnRyO7u2yu28udW7nf4BtvNCre1sldspVNop9G5n34DA2umubofZ7MyNihjH8acZvK0tZfCWVM257QLnGScgrIGqfJoAzoLGkbaEwvuCqPf/KRxPchHu2gKWA3cPk+JuDadX3ipIqQqCA6ayJDB9t+aMMUpGCFnhGAwgqQJjAdgrqoykqgo2AlJIvtwjSN8E9i37WFYnOBbg7dUAqi03yoIYk24mQWSAh3UEMqns0Dz6v5w9ettZo4LV9Ow+mVjTUGWEEKQy98qpfCUY1+PBLVwSkOOa8ZsxmhCl6YoF9i13qKXzLP68LW4SEc+T9Bgf2rIoWc8MVobrmS0LBxTF3ZEAw2GHbCwxMYrLmSjZSvTdfFWU2Xw38z3AbldYFrVDwoyRWKlBjXXZOerIDbVNwXoW8iuVbw0abvDeHENGVM3MIphhNFpFkC3Dzu9I4cel4623F9G8I76TwwT65w4cdelM7aNZ7et1ckAxNgGdbeyUXDoAtyhdlk7JlUsHavtjeg8ghx2R
*/
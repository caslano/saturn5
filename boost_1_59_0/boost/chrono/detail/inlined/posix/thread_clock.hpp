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
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
*/
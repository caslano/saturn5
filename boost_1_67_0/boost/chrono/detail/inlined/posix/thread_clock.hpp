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
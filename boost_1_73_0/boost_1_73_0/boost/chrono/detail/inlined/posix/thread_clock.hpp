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
h14A2GUKwr3HpxS2ZgArPnFT9qlnGfl1gjDw++/dUFcxpYg+MV15NbC3fdlYi1AF2RIMLb5sQUCEoCDvIyvBDQWHxkxjHTEcQwLFkDR2whvtTSlEMbKmkG+oCmWJeHjQ1WzVYEgJTAIOskeTZbcBjbp2JyF+aG2MoiXlhlWr3jUWEoeByv/jEKLyMNi2ZVTLSR0Ky5L71jGrjgdEI3RgkMlQYKxRO4m6gS4cfy5RlfSsPaoaVlO1SZ2PsYMKNHqIuT+rySuwAUdxGv9tL08OPGxPzKajW7Cgj0umWALusEFCdQEWvCfmSAjO2RsqMTzjG9+9+r7aEuu6uzF/NvGNKTQMxpWEM29g4fet8ryBIU+2J3Ri9ocepu5+4P6qQfsB+72sCWDzKmVPebUeHVQaEAdYn8BO9jgZ9rRmkbH0twvTLRE8hG1C/0ODUNLssnSJUc3ryM+h3/eHysPBFHMRiaQ20p1WBzl34lg3QX60f/jWfnVhytEK0Lin79+4WK/CQBUt2Yp9CSENVpEJbgiWjALLTheWkxIBQeiRQ1Iuc5jkT9qa1R5NNq4wqO3Bfq/4wmo0rMu+IwyqWyT638vLuh5fjcBvmb4bI/Bb13fb4/DbqH/uPYPfVknQ9AL8quZHx7OqymTZC65Wo8H0
*/
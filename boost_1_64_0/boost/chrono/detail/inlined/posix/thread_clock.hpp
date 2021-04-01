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
apY67mfZhFwBNA5UCC10eglrl5tXeLrqqAge8JViuGWk/aoOrW6Ro3U30o9w1P3ED7yOY68EpwC5nHOT4letM3+BVkUE29GG/cAbwLkxy/4QMix2gECsSZktGN4FboXsvENiKQwuBVq5SYVdvHOCuQRf+Yz3ThNMlH5X9vQ1Mxrlsfw5znXdFS8owgxukDh01MLFW14K5gzpG18l1vRxEsjXmxbd8TE96DkHllkgD9l9fXdkVUGG+URHRDrkX3KgpUXBmJLT0bUK1MrwWy6d4Ec1FNO6dYuzNXq1FV2WYwYnLGp+hveEuef29iJekYNqm7cJHARkvKmBfP8xJR+Q4sGP6+Vi2Br9fqstHWQznaRBw/lhYGWiNhlud+swi0yb4063O9ClxTEMoJrsvXUHpMRqFmDtjYqpoSpPnyldI3p4kgGerMIxAcR2XmHjZwiLUXuNHsvpKcIkLbRHj0jHwiKd2QZ2wsrcyYUkzEUJ0qCK2NL1kl/nPAWq7Xn7WkBQwNkwwF1qbQCa4lOx4cOOWaSJgQekIvlXeKp9HEJBQzn9U/QWO1MKyC4Y0g==
*/
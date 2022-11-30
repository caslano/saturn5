//  boost thread_clock.cpp  -----------------------------------------------------------//

//  Copyright Beman Dawes 1994, 2006, 2008
//  Copyright Vicente J. Botet Escriba 2009-2011
//  Copyright Christopher Brown 2013

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//

#include <boost/chrono/config.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <cassert>
#include <boost/assert.hpp>

# include <pthread.h>
# include <mach/thread_act.h>

namespace boost { namespace chrono {

    thread_clock::time_point thread_clock::now( ) BOOST_NOEXCEPT
    {
        // get the thread port (borrowing pthread's reference)
        mach_port_t port = pthread_mach_thread_np(pthread_self());

        // get the thread info
        thread_basic_info_data_t info;
        mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
        if ( thread_info(port, THREAD_BASIC_INFO, (thread_info_t)&info, &count) != KERN_SUCCESS )
        {
            BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
            return time_point();
        }

        // convert to nanoseconds
        duration user = duration(
                static_cast<thread_clock::rep>( info.user_time.seconds ) * 1000000000
                        + static_cast<thread_clock::rep>(info.user_time.microseconds ) * 1000);

        duration system = duration(
                static_cast<thread_clock::rep>( info.system_time.seconds ) * 1000000000
                        + static_cast<thread_clock::rep>( info.system_time.microseconds ) * 1000);

        return time_point( user + system );
    }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
    thread_clock::time_point thread_clock::now( system::error_code & ec )
    {
        // get the thread port (borrowing pthread's reference)
        mach_port_t port = pthread_mach_thread_np(pthread_self());

        // get the thread info
        thread_basic_info_data_t info;
        mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
        if ( thread_info(port, THREAD_BASIC_INFO, (thread_info_t)&info, &count) != KERN_SUCCESS )
        {
            if (::boost::chrono::is_throws(ec))
            {
                boost::throw_exception(
                        system::system_error(
                                EINVAL,
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

        // convert to nanoseconds
        duration user = duration(
                static_cast<thread_clock::rep>( info.user_time.seconds ) * 1000000000
                        + static_cast<thread_clock::rep>(info.user_time.microseconds ) * 1000);

        duration system = duration(
                static_cast<thread_clock::rep>( info.system_time.seconds ) * 1000000000
                        + static_cast<thread_clock::rep>( info.system_time.microseconds ) * 1000);

        return time_point( user + system );
    }
#endif
} }

/* thread_clock.hpp
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
*/
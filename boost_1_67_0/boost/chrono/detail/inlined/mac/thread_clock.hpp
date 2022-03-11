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
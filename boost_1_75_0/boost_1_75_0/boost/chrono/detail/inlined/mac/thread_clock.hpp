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
79zj/2603utu9BP3BIJNc/ZL1i6SKdYPrWUfP+MlG9v+So8SUpi6q8a/Eqv5PbiZNAa8382CEsR3dDZDAnaY8ZIv4gw2ZXfIqGMmtQNbR284bQ8m45lVNRz8MaGjBLd8mIqeE3px7o5sf+vik4e5yYuBdSoLvyx+qWf9e+Ruo27Jdtlydk4ZwlcaU8Wvs5LBC70ivGKYqvUl3U/Kc5Hu30eNmO7rpkJ1N3yQ3scvEECUEIlLcYkaIDLnQOFqh0CSsyDyHpczhXCezEGQe0o6+cskYJAly898Ohxye7ZQX7BzybK5O6W4p5ipCP41jNpN/k8g0nVC+PSihAi9PgU9DN1/yMh8DcUdoo4aqkVTs9TAHAxFEPo/VrqmXj2mXgdDHHMwlKA4GELvF19P0NCGNPUetouqwsnabdlnqO2aOvoaqbqi+B0puaLxOyLpcSf+oiwmRy/KHKOHuJIWt+8E34v+trjJaZbsHdS/omXRTgM11XptUhC72pPUQgcMlslz0ChpxwmZyJkonT091o1FCjSA8I0G41w7MaXLNcuiJVgZGusq13nVcR0597Pp9KAQxMPpmB35alD4L70bjyUo8zvWgE5J4vTSPTm7Z9RYEA0g57lYEzPxyYk10IOyNNmcM83bEr2x6noHHeL9zekQ3z3gf4jNu9Ih/hx0XePJC9KMZ3O6ajwfBPmOJ10az4Fh8ngWBTVgPC82o+PZ
*/
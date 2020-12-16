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
/TG8O4iyQ7iuIwnP8I7f1BN/YED8pi4dD9vVkDAlWyZcDNwguINoV7Nf9bQrahX927vW+z4ncbur+lrvy/QcD7E0kWuyM00vvb8H0lRgHfnOcz5ax+kLtVisrU7nc4kTp9enGGKWdSm0Xb5rhvN6WL7Ir82a4ZI/n/JrXoY2ZPYf3eC+QvnFvuZbfmnW5YeyYlwcoaGKsSkvxsHRa6sk/2s97ZyQpb1W7+sqCLduFzO8rktaVAnt4uHX/NsF09u3C+w/fbuY8drp28UHr/1v20XvstbtQq3yK78023aBuKdvF2rVn9suFpW1WZvFc13y6HKmY8oyImzWZVlV+jFliFvyuiyrzm1MWWPm9RhTJ4TAkQuwJ/1lySuuXp4ZbJ8PEE/yOdSt7xb/SedgGS3UWm0CD8H9DlfHMFRLuL5wowzsh/sc7me41g5DDYIb40A43JNwq+F2w8U4DerHDWUUyr1gN/aJ+aloM/aJ+3GV2SpRzVJl1XKopb/D3xFGvJplREOXka7CHNGqqaMm71FDLZY049Bye/qOe+JxL/M67hDU9sMo4ddQJvbHRRq/4/qPjWrJ+cXD5HpHIuVFaoDqDPt2KGy70WonLPctcNw+Rgscv6XaafRWFzoulGeLI5XlN10NZd91pZznFOokTL0KtwnuENzvcHUMPJfB9YUbBXcT3F3GENQJ9hsdUSdhqBOEwz0JtxpuN1y4M5rPPuZmPq5NGnNdjmcMzB45Zx3/ekMayR/nnM3UOuzuSHPxcs+cs911+YTIWIr+EbDVR8P+bY6juSUpLMIZHXlh5CWRF4eFRIWEeMbSLMT+cpIv1n2m57lnwCs4Hvtikfyybbj3j5f9NbzLUOftFtkXovN2B/2eY03Ky8rO0fHzZX+sf3wZs1Gf11NYDnok83puftJ9PWHhztDIXpG1ImtgCv2wqDA9hubpEq7ri8KSr+tn2d9Rxev9WVOyxuRmDc/15PfXQt/8NmR+LeuL/XW8xKlEvztNjFxjVeQ7jP13FtwzyP8iOPM6FpZqruAoE2q9tAmPPxd+t369xfLAdTUqIMx/XY1TrwTq3ItfCdS5b9JhTfV4ulc9YfocD3nC9Dn6vRI4Jq6dJ6y5Pm9hoJZ+Q2HgmhwvFgbq6x/0hOk831oYuHbHkEKLdTo8YTovNT1h+hwJhYF6fUOHtRH/LS/rcYL2v7sWY/cyLMbuDVQBY/f0XM37OKallQsI55phq/Rv0wi8vOZPnCbviXa/UYzfyve+ZhteIfuaqXimZTvHATzvfmskToMS+66NEqfGaZ8T5PfYu7z8fo9jORZhLp+1ZvEdfvaL+ppluKLNtTLeUByvT9xBpCuKd913zroYedglsjY6mhCsz9E1shZczciuYQ7pPv3Khut+yLFG25QN1weQOC1KLJt3JU4r6Rfcz3UypvacviW4ymtIItsGzlOFfKcC/nhdl9f4rHE50kAC3vua6HJDfNYxvwk0EH+k8YKK9E3TlNeu09TS62HVEn+8sVKFSRqWJ87iWSOqusQpb6xVhnecpt5rd9SVOOWM51WsHk+RGetyQ0o53ifgvmzC+9I7rKnfOFGuI3AJ35M6uceJetoefujt35E6S7zm3muOMG285W/qFbIv5ZzWG5mo/NZETFKyjedY1+FwX5vfAFbra7D9BsA8M26qfpYpFH/vgPcWtgPGb2j5+5zh2W/7+7xM9vcs8fd5zWrf3+fj4neW+Pv8kcRJoZ9p4NPPFGc534GMzbF4h0zX32fk+n3qpTvn3V/EenkU7hvkO/UNXS+23xaSWE5tJO7tqjyOexkc64vHqGhXP9yfpJJYny3Ff5+000Fw/vUSz3rLlnhZyG8lq3I=
*/
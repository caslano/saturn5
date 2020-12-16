//  mac/chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//

#include <sys/time.h> //for gettimeofday and timeval
#include <mach/mach_time.h>  // mach_absolute_time, mach_timebase_info_data_t
#include <boost/assert.hpp>

namespace boost
{
namespace chrono
{

// system_clock

// gettimeofday is the most precise "system time" available on this platform.
// It returns the number of microseconds since New Years 1970 in a struct called timeval
// which has a field for seconds and a field for microseconds.
//    Fill in the timeval and then convert that to the time_point
system_clock::time_point
system_clock::now() BOOST_NOEXCEPT
{
    timeval tv;
    gettimeofday(&tv, 0);
    return time_point(seconds(tv.tv_sec) + microseconds(tv.tv_usec));
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
system_clock::time_point
system_clock::now(system::error_code & ec)
{
    timeval tv;
    gettimeofday(&tv, 0);
    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return time_point(seconds(tv.tv_sec) + microseconds(tv.tv_usec));
}
#endif
// Take advantage of the fact that on this platform time_t is nothing but
//    an integral count of seconds since New Years 1970 (same epoch as timeval).
//    Just get the duration out of the time_point and truncate it to seconds.
time_t
system_clock::to_time_t(const time_point& t) BOOST_NOEXCEPT
{
    return time_t(duration_cast<seconds>(t.time_since_epoch()).count());
}

// Just turn the time_t into a count of seconds and construct a time_point with it.
system_clock::time_point
system_clock::from_time_t(time_t t) BOOST_NOEXCEPT
{
    return system_clock::time_point(seconds(t));
}

namespace chrono_detail
{

// steady_clock

// Note, in this implementation steady_clock and high_resolution_clock
//   are the same clock.  They are both based on mach_absolute_time().
//   mach_absolute_time() * MachInfo.numer / MachInfo.denom is the number of
//   nanoseconds since the computer booted up.  MachInfo.numer and MachInfo.denom
//   are run time constants supplied by the OS.  This clock has no relationship
//   to the Gregorian calendar.  It's main use is as a high resolution timer.

// MachInfo.numer / MachInfo.denom is often 1 on the latest equipment.  Specialize
//   for that case as an optimization.
BOOST_CHRONO_STATIC
steady_clock::rep
steady_simplified()
{
    return mach_absolute_time();
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
BOOST_CHRONO_STATIC
steady_clock::rep
steady_simplified_ec(system::error_code & ec)
{
    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return mach_absolute_time();
}
#endif

BOOST_CHRONO_STATIC
double
compute_steady_factor(kern_return_t& err)
{
    mach_timebase_info_data_t MachInfo;
    err = mach_timebase_info(&MachInfo);
    if ( err != 0  ) {
        return 0;
    }
    return static_cast<double>(MachInfo.numer) / MachInfo.denom;
}

BOOST_CHRONO_STATIC
steady_clock::rep
steady_full()
{
    kern_return_t err;
    const double factor = chrono_detail::compute_steady_factor(err);
    if (err != 0)
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
    }
    return static_cast<steady_clock::rep>(mach_absolute_time() * factor);
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
BOOST_CHRONO_STATIC
steady_clock::rep
steady_full_ec(system::error_code & ec)
{
    kern_return_t err;
    const double factor = chrono_detail::compute_steady_factor(err);
    if (err != 0)
    {
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            err,
                            ::boost::system::system_category(),
                            "chrono::steady_clock" ));
        }
        else
        {
            ec.assign( errno, ::boost::system::system_category() );
            return steady_clock::rep();
        }
    }
    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return static_cast<steady_clock::rep>(mach_absolute_time() * factor);
}
#endif

typedef steady_clock::rep (*FP)();
#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
typedef steady_clock::rep (*FP_ec)(system::error_code &);
#endif

BOOST_CHRONO_STATIC
FP
init_steady_clock(kern_return_t & err)
{
    mach_timebase_info_data_t MachInfo;
    err = mach_timebase_info(&MachInfo);
    if ( err != 0  )
    {
        return 0;
    }

    if (MachInfo.numer == MachInfo.denom)
    {
        return &chrono_detail::steady_simplified;
    }
    return &chrono_detail::steady_full;
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
BOOST_CHRONO_STATIC
FP_ec
init_steady_clock_ec(kern_return_t & err)
{
    mach_timebase_info_data_t MachInfo;
    err = mach_timebase_info(&MachInfo);
    if ( err != 0  )
    {
        return 0;
    }

    if (MachInfo.numer == MachInfo.denom)
    {
        return &chrono_detail::steady_simplified_ec;
    }
    return &chrono_detail::steady_full_ec;
}
#endif
}

steady_clock::time_point
steady_clock::now() BOOST_NOEXCEPT
{
    kern_return_t err;
    chrono_detail::FP fp = chrono_detail::init_steady_clock(err);
    if ( err != 0  )
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
    }
    return time_point(duration(fp()));
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
steady_clock::time_point
steady_clock::now(system::error_code & ec)
{
    kern_return_t err;
    chrono_detail::FP_ec fp = chrono_detail::init_steady_clock_ec(err);
    if ( err != 0  )
    {
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            err,
                            ::boost::system::system_category(),
                            "chrono::steady_clock" ));
        }
        else
        {
            ec.assign( err, ::boost::system::system_category() );
            return time_point();
        }
    }
    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return time_point(duration(fp(ec)));
}
#endif
}  // namespace chrono
}  // namespace boost

/* chrono.hpp
2xGOhfFdyEA5kwuwZ9teySvau1jnrWzzjNNQ21tOif8yY4Gytc0zjb1t/hfZ3994UGnbPNPUs7PNc38dbZv/WfxXGouVvW3+B4kz2FioovV9+Fkp2pq7jyn63LfPWQi/29586+eB86rdiDB/+/A0T1hTt314qA5rLf7u8Hvbi1tqf0vx19L+FuKvAb+3PfnOz/+Y+dXM/qchr7kRv1930H7fNja7DNd+5ffrS9zzr33BNibWVGtb6vcSp623LRXpzt6WWo6/DYMTfPM4kI/eX8HFyjcazglUzDyK5dTWbsp4TcR/Jfz7xX+bnR2V8dP1mg8nxP8cWuNQ6zU+/NKMtknDdq773s0SZ6sqVEkMM9S1ez02TuYPG+uV5X5Q0t3vtR8zxHjNX/OR7H9E7LJzUb9dy9Je5nDO2ExDWUDfRt3Xh5J2U2DfxjzfJvkLDcwvbbJ1eM4inLPYtOOlR9Y2T+lMMM14sfijCv6IjvOfnygJ6bojzQa4nWa6GfeFhUSFhnv9Dtv+Zl9s5oHnN11p5qNJt7DbdbewA2dY2IFPShnhWxrvrQg5P76h0d+e/vp+99o+tuMqzEwK77VCfa+VOPcO41U57bOXjV1Y56NhlPV8ZRn6fsqbbH8/MZ79fGXYbz9f2d3FnvnKDqI8Po488/nKsotLnq9sWHHgfGVfnPk8RaWar2w35/B7hM9zt7Nvmr2HZSnWWsvfaMaprn+jXxH/ZJWtDH87re5zX5I4udB7tWd5u49T1cJGSy2n7J+iRiDfLCOmqSz3XRraw0XRvO+ukNtOlea++3aP5777s+YbM++vVXt877/N9Deh/xD8Vvff1Bgl2wzW1WTaak98xrqipdairhinsu4nI+UcA+3mJmP8mlqfnCDxh/jbatmng7K/NuvHnb6q1E8x6qa4HOsno/T10/3s6qfzudp+E/zqpwb9zelP1/UTtAWfD1tw7Bw4Y1yL/5QdtSo6+3hO9LtLiqPS/p624LoW84AV0xacb9r9+Hcx/tZ2Tj53brSwtx6k/eUQWI9zIuGyxY53IRgDNqFfH4/v/o14PH+7aXlF+yK4H0yhvbQW/eY1fO5lh53B4420OF5fps8AG9AOnca5ydJpn4YTv17z5oC9PbgHr7cn7cG9PPnAe+/5swfvc79v8r0W+RD718c83kzag2eDl9OO1J92pBGcI2wk7UhTOCfYVNqRzIwsAO/g3GB3g0+AM2k/up9zhM2lfQhp1SLa9Z+lPfk52qWeB+HEbvQC7URLaSd6iXOEvQK+Cv6DduzXwDXarsh3IrCPhV0xi3bO4SynbNo5c8FqZjzaOXNYvyNp7xwNtgPHeM0FdQnT8bx8J8F7k8V5i9gO3+V53udxt4LXce6iW+hfTXv627Snb6Y9fa9ZX7TLfeLVTgp5vVUs2utAtpNBbCeDudbRVWAseDXb81CvOY0yiu3nlFrHdvY254LaSDvwO0w/TPFZB3yE6cuC/b30D9XBfM4BNwlsDBbwOJNpD7yW7W0qOAm8nnqQ6TxPhnL/ZiOA5ykDduV5bmJ7vhmsR3t1a9qrM2ivzqK9egLt1KoUczJN3RC0N/6V7I1zUV9r4PbBnYJL3Ij5l+C6wg2BK4CbCbcIbs3GoM0xuAW34Bbcgltw+yO3ELgJf7z9f8So/CzXCoDnqAGoSg1A+vMeDQAPn6eoA1hXHs/MtKXOMPCfl66wmXLZz1M/0bZUSRwgBbDXAjBtCv2wIos/8rT2WDtbfwd+p5tBW/8Qfp++knnN88urr7nf0t7PNJV1Ht8Qfxnbb2b3yf5qOv7r4k8QW8ptBt5jkLf1KFeYMQZGORqHRUaFlimNzcFKI3C7HBvvHpXk+vU=
*/
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
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
*/
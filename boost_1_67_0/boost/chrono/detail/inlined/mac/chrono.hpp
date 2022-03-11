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
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_TIMES_WRK_HPP
#define BOOST_INTERPROCESS_POSIX_TIMES_WRK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//workaround to avoid winsock redefines when using date-time

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifndef WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>

namespace boost {
namespace interprocess {

typedef boost::date_time::microsec_clock<boost::posix_time::ptime> microsec_clock;

}
}

#ifdef _WIN32
#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#undef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_TIMES_WRK_HPP


/* posix_time_types_wrk.hpp
Mb7pwfMOOrJ/zruTV7xbdXvdi687ztfyTYPj7FJwf1BHmi/b7X3z8bfqZrc/B9nJ/IOgWmfyfNeh7twuPJfDczI8z4bnsfD8MTzz4PkcPGvg+arblsFzq/uND89fwnMaPN93v/Pg6fpdDE/33bPguQeeJfCcnEHup2WQ++nwLINnETzL4enOi1bCs5F5ZzLvLHjOg+e58JwPz/PhucANFzwXwnM1PKvgeTW7u4ndufEf5X2X4HcUpU0HdyzL8b+kM80XXtmZ5v+u6QzucH6Qx/TYBmC64b97s7uUIzwap9t5aZ8H0gKvUeFNaSVvUSt5za3krW8lb3MLvOUKb0crec6y1vEGtZLnxFqXb1Na6d+iFninquncSt76VvI2t5K3o5W8Qa1Nl1byFrWS1xxrXf1Y30re5lbydrSC57YPpXHi7U88bh/M9QRuv34gPNNA7lL0/esCRhUBDrIKZAhg6+GZ5LUA7yprACpw7p/m/LOUuf5NOK9P8/kPgtvNRTSfv62I5vN3wHNXkT6v7xyH8/n+PP5Adb6e5+gH5YEAb9RxMg8/5Tiegz9OnXfX59zTgCVxvp3m2c+Dv28F2QzyFshOkI4z4Z0gY0GKQSIgZ4CsAbkX5HmQ7SC7QLoUQzhAJoCUgiwtBi7I5SC3gmwE2QqyA+TL4vb5/PZf+6/91/5r/7X/2n/tv//FX0eQk/8L8//R+JJYPJpa6N5nEqlL1Pwn1gG4c/ol2WDr4PnW3hkUB3zgj+x025bifCsFge6q40C4h759v41OtbnZ10K33QZ1/76ufvre8z4p+uDB01e8uPqclx647aS2ryF/L8vV3zP/tHk7O6++7aw7e+3YevsVz4ev/X4f3zvpm6GHVnx9xoX3Tl/Qf+c+l4ChqF8PV3/LQ9c988Yrp+w+vefG3od1+WZWuO3LvpY+3CY2Hd+bHnDxVyvnXLfg/OHH35Q9tuuHMH+M+vPuuP5Xf3xp1KiVL5U3xS69fWfb15a3dS/AF+5csMNlg8vMDMxrtK/hbxx/O05x15oDMGEWrFsGSYOsAbkXZMssWju+C57Zs3kNubJ2fALo5oE0g6wF2QiyHWQ3SFYJfBuCzCihNeVJeF4OEpkEPHjuAOlYCt9wIAWl9I25tJTWmDeV0vrytfB8EGQbyC6Q/nNobfmoOfT9WToHuCBrQO4FeR6kN68v/wj+3aUMvmFBpoBEymhNeRM8byijteWby+h79MMyCEs5hBekFCQJcjnIoyDbQXaXA85rzPtXAA+ktIK+W5dWyDrz5goISwWtN3/UfYLsARlUCe8DWQRyEcidIFtAdlQCDtJ7LoQZZCFIM8j6ubQeffNc8ANkk7Im3TkewgAyFmQeSBPIDSAbQSKAbz+e1qfvhGeXeZC+IMUgdSCr5ulr1dfPo7XqW+ZBGoA48yG9QGaALAJpBrkBZOP89u/b9l/7r/3X/mv/tf/af+2/9t//3++/tf9fvv9rqpOxf3///wGwXvuqnjCHOded74PDQ4vcc/+q3MXt7p2siK8BvMvxGt6AO9uBMBjwNPD2NPt4XWwxX5pcQ5fKH8AcZ57HYTwWj6UZz8mGNEMcY0jRq4pFHAXvYuB4Nzfi10AYm6Kd4LsTgZr6SFUkWhtP4Zky/P4sdM8e453qpM9GfUOqusrEeiMWsWL9EaMr/xnEsFzbE8CV/rtcj+uj6aWJCMflesA7Ch4RXPzugnhjKlpVHU1V1aSS7PYGcLu0FuKJ4WUMk4HwGwHf7uPR+FLB0c5zJqRjLq7Hwv36+OvPZbYfyLreMP98MNp5MKPSDdU1Ud63cSNgGQ5eY25ZU8/ueH18Etfg1/JScuF1ER6vsZd1Xme1Yp0=
*/
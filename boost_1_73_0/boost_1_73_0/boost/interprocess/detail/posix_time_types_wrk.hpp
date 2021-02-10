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
L2N1cmwtYWxsLnNsblVUBQABtkgkYMWdzW8iRxDFz2vJ/8OIXDbSjgUEbO8hB2Aga4lsrCAll71gGFtEhLH42F1p4/89gwzGwHR3vao35rASDD31fl1VjHs+3vL7ZDTPFtn9MvprslgNp9FguRpPsmiQTVfLSTaLepNp+iHqZfN/h/mYdL5Yb6zVLqrV87OfDnaqV2v51tt59k86Wr6v/Lhudz52uu3r+LrdaMW1WlKNr5NaLa5WW9XOx1r+aaP+VPk5+jWqjFbzaeVDVFnMR1/Wry++jr4/5oHW23406/Xrbh4pbtVrl3GjXu/FrWb3Mm7mW5vdepJc1ZKnyvnZu430IP+XY77fvE3Sx3Q2TmejSbpYiz1mi+Xmo3yfdz+S1mWvedluxNXLViNuNGpJ3EquqnGr02xdJc1ar5W0n/L9ZAPzkN3ZeJ/k/Gy3SZmg6eRum6P85ZfN2700ifAq+yy/TbO74TRnfn6xzdy2/J1sdj95WM2H6ze30+HyPm+E5yTO0+2gdRKTfj9K0rvVQxRH69d/5CkfDPqbd/3J3WDwqf7f35PZL/V8Z2C0PPj3y4Y4dD7WEzjEGSTzs7jU86jj7NsiGgxub3abbpLPTp7AHphIMbN3fEhABC5jFeC5iL5l03tfVfc+9wUo
*/
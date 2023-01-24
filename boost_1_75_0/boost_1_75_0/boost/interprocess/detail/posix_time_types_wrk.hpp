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
XoO24Y53g6DSvPbTcRhEaGhpetDLJYRiD/kjTFzU3jAAsP3KEvN1jeEUMzRBcm7aREk/tbTqlEw7UGkMIyt1PD5ueJQFluDNLNcvKVRifwuIMfhVJy7Y216v6kN6fJg1dgzwjgxkV03aWwNGH56hQKMrTE/CBlzsVKyeOvN1DePjGRvwPb38sqWx2eiq+LvRjXWxu3IDe43kZ8ZmGEd4Y9GeFazrEUyMMKrckRFg5sLTQQa1nhLTgfPXp09olbik7DwG/FbOdRh32Tnx3EKTLTL624x7So790w0bMQVnrAt5Ja3NGUJyiC4/6aLndp2ZDBTzD68XZ5E7RfDBTDrDC8gf6AusqGF5pxgkJHmiofHCFw0t+zPqr8SqU/Qn34Xs+KS66U97GGh3/6TeucwQiiKqkDaWuNTsCcmWrR2J0H11yx0V0eb+5l7AVx+y3UcujYsOOTFyBAsewpf9tYJPTLOqxwarf+OUjAc/929BM6qSVTdmfqR6FIuMVzC08/v+9VtDW8WOjD24Mp4HIfsy2XE6X0yqd5gu/WpfQoSgTgzfUQzTlt6WLQJZeJaXim5+9x2uTnT87hHb7eh/qws4eVs40hOBtvkAHyFSunrx+qdPK7UdDtXUnBStmi2PD+U1GZ2SKDS4zADhw232p3RoGc3CqKRM1bLKG9BL7Orct2LFGPH7TlKEk3Ur3hPNnvX7fQadEGCC0mJj1LX8
*/
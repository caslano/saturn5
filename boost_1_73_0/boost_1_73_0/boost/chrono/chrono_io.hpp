
//  chrono_io
//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2010-2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
// This code was adapted by Vicente from Howard Hinnant's experimental work
// on chrono i/o under lvm/libc++  to Boost

#ifndef BOOST_CHRONO_CHRONO_IO_HPP
#define BOOST_CHRONO_CHRONO_IO_HPP

#include <boost/chrono/config.hpp>

//#if BOOST_CHRONO_VERSION == 2
//#include <boost/chrono/io/time_point_io.hpp>
//#include <boost/chrono/io/duration_io.hpp>
//#elif BOOST_CHRONO_VERSION == 1
//#include <boost/chrono/io_v1/chrono_io.hpp>
//#endif

#if defined BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0
#include <boost/chrono/io/time_point_io.hpp>
#include <boost/chrono/io/duration_io.hpp>
#else
#include <boost/chrono/io_v1/chrono_io.hpp>
#endif

#include <boost/chrono/io/utility/to_string.hpp>

#endif  // BOOST_CHRONO_CHRONO_IO_HPP

/* chrono_io.hpp
wu5YApxq6qBXMZQubFEkMXbGpBj6voROkY8CAgpW7R+SWaJSrDCcT2ah4C0+QJZqZ9F5zqqN2QpbpCSxXqMKyN8NW8PbjAdbKB1xsplYCgBsjc/t8NPaa4KB+joW7P10xeuPMJHB4qm9Wawmh81eZSw+tRhrhAmOjidND0fqAj6vc27ETZ4B25R5+aK4j+Vr0g+iVokCws3pcQSZAgPd3KelqSMG5yj3AGaQQJP3chJJj4mZH+9LR3Qr2D6ziaw=
*/
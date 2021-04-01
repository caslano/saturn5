
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
scVRsZ6uijc4ESTsUJgoo/pN3n8lIlgBudezbJ+q5nwqxgFNC6sxH+xcAeKrqCmUkBYklCzTAKaXOGuaExRYXZ0IikiVwp7mqqu2WPdyyjL7cIXkyVQ1SAg5uQrqkG5uwYppWT6EA07tMEL+RtE8j/yMIiTnfBRnJQcGWvet179pnGFwvnuJCfTQ22e5+KQPG28ohmVsoZlTmKY86tpf8CxHDx1pkQbe/vrYkiwtaB3S+zt24onjYnJ4mjKzXNmzIlH+iB7UwAGvCAswj9Bn0SIGZbUJtd21YAkgSICi1Ixqqo9PnapIV9pGzY23JnXoDBp8pB+Zju1Z0dQYNdfkRb5Vzb2nYOh/IpkpeU1vdL14Ss0l0oRSbyOXBiL3GTdP4NJimH8kSyhIz/k9EZ2WkNKgYErVqCodmlUXoUMIVWItLqf5wc1pcze3FBfSviEgKpfYhOvWBb2wtYLKXz03BsFE8hL/cAG8j0dci6FzaRoN3pzmNuV42C6fw7UVaP73brniFiA0sC4uC3qzj7yEXJZw1dXjXnC5fVE+lmJwdfXM7/ZuntPZhYn5eg==
*/
// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif             

#include <boost/config.hpp> // BOOST_MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/config/gcc.hpp>

#if !defined(BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION)
# if BOOST_WORKAROUND(__MWERKS__, <= 0x3003) || \
     BOOST_WORKAROUND(__BORLANDC__, < 0x600) \
     /**/
#  define BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BROKEN_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* overload_resolution.hpp
5aEb3pnwfn/bL7oxbsjYsJ/OGunWXU3r0LsodxEab6Zn5uBMq2sS2hLcIy6bB66pHzdHBnJMxUnF5ZfosnIg+eHXmiBuL+I5PIQQgg1B3Korw6IWQKsDxPcEZjNG2txc03xPm7WHCgaaHDpC8QJVF6XADzWDYhDmNYj7W7MC+yOBI8P586r2o9qZ41ohoYy8nIPMNIE/GczVs3alU2tsxFUZtbNLSlBIwEZZMhLnvvWaMBD9OyoPiW57VgwqodJGaFjlI/KP1q6nrxkCY5CRSArhhGu3TEJ4gFCPKtR2dI3n2hTB+MWk5GyO+GgL+glBjJjmlX0gPCohMXr9fiutwIu4DRiNxG3owaajXTSF50o7aK1atRS3FFe2eUwwaqFLjZYpkufV8IbKTrDnTgP1OXU9sIcE+a17M61O3CQbpC8jMPOaFG6LHts4W51jDThX/JTOFIXn5r6vnGkC9hYEoQBZYR+QOeJSObtEKgOBrEgox7noKjAelqrX+zWVQlRGWuD/tnTYZ0AnZYnjHNdlMIe0EstGSc+CXpsEK5BoFUfqIraNV0tpz2hVTitoy8L7zaAHgY3a4O1gkWBpraVG2NZA3ToigeTkG2ua4ktPUh22Aoa/kg1VDM2JLQ5I70Er3jN75U95yHSCYx0/D5EnMVrLZKiMTXTvfzzsKy8CjyBFNFdx4lm9zYXf4QH3MpsjlA3RYRzJee1NeTmk
*/
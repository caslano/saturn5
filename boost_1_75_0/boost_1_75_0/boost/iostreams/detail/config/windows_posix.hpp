// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// (C) Copyright 2002, 2003 Beman Dawes   Boost.Filesystem
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WINDOWS_POSIX_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_WINDOWS_POSIX_HPP_INCLUDED

//------------------From boost/libs/filesystem/src/path_posix_windows.cpp-----//

// BOOST_IOSTREAMS_POSIX or BOOST_IOSTREAMS_WINDOWS specify which API to use.
#if !defined( BOOST_IOSTREAMS_WINDOWS ) && !defined( BOOST_IOSTREAMS_POSIX )
# if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && \
     !defined(__CYGWIN__) \
     /**/
#  define BOOST_IOSTREAMS_WINDOWS
# else
#  define BOOST_IOSTREAMS_POSIX
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WINDOWS_POSIX_HPP_INCLUDED

/* windows_posix.hpp
Rv30qOB557wS6r+8nVJ16U9rbBBAS2dsbLR6p7Rnp6wGaCVJzGJI6PZ4rHBgOvo2HbOxeoUDUWi6YF69PTk9xAqzVm7xjm4F+HfiZgcSrokUv9msEyy67MrGZHhwS/38o2wnmVjG29387LYH3B3c/ZUBBovMJ/TPpqN9RCsPnMh0gHWnV8p+keBkkI5oxbuaLzgTdVHpX9vNxDUW3cUMP+xbKOQCXWQz+5uvMyo+2NB7icYLN5vJ0rYgkn7Uy9XCmtceo7xXXnYYvaSYVfiLTtMiXJSvKmQVp3t8yKoJN95dzHeSutlUOdHiPVGWr0v4fFIObzlULxYeb9j/YV4CT/ntL+l0F7s/Qp9qpZJhzj9BI6H7mx++fG/sRm/tsm3go41JUgee0cZne/KNLj2Nwsbh7qIp1fz206bJlV9EYT5nScq1t0zBffEepTm+ypPW+myMqRgaC82aU/E9tn5SImyjBxjHDIKJa54PchuMe9E0eVURAS+NnZ2v0ldXMSNziE7fJo0z47f6zS9aJe3kfOw7fFDk7vGnWGAkM05lqFOIVBqfpfgL25r3h0SmXUIrXT4pJobmNxYuOyLxU3QEK55kztCdn3wg25tbayZirxrRy7LcpbOThYBG/uxaNZApkhv+Q0/0dYZawHopM3z2L+ZpMW9jqHn95nTe2D5C5j5Fc9W0vUsd4+wSOreXzyONNw1bdsOx4TZoUt/W
*/
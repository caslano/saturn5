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
Gdq65Fs1o3GbOsY84226KyiBTa3Kc0X82O3TDN16kXZOgY6oEVK5qBoObQjjWsIsazq/JiWF2Mm8ppL3S3jyxzf9e9zRWOjubyuiOVW5nUIW+8VOnXnW0whTrHe42qN8ccGnzPI/tIxaSyUF+ioJw6CTxz0aGqlZ/cI8Qs+jTQck4Cv8VFJL7gHJ0MACPqTkaWGF1/K3apox/RcfntpzHbJ84AHv0COKAw8xMXYIgSimvyPRj/F8PsA/+zgUyC0vfeTzrJu0UtaasPY90rg2eqUPW2Ca/Vz42fJrEVbdwNGjkI1oL1amTP6euKT1fkohEyNo8CdEODViZLOrQ3ehGgwmnKzwdIPywo+on0CihPzOgd6rvQy3UsJM7BDNjheoGfkozTiK4sX+7p1ycSSDGWsjr8wWSt/QyZsllIIkFrj/eznuhp83Lpz29VCK80B8Qr8/xUATq7R0kBtrhp8pIVN9CKZ7hB/hrspIrTYIbJoStZNkMjDMtEe6F3qXml7qwfS/GrfwvdE8ePlcQ0jCE8gARZq0yMWu3CN88uTCUSBb7YwF5IlgnHjinQ==
*/
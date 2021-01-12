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
gGgl0UqxgJedFWGTkqtl3SAKVpOmneeyne/5vBFbA8V2TDgzkIipcA7CdadIHiW6GkwbzmcbXg/cHplqtMSzV0ljVbjvCmfiu4nV6EGME3EGEPHkWLUdWacqp0sE/pxpQkNVC7OKP4vY/aYJ/WWt9i4jsc+bJvQbxmqGA+HMerPQ/BZ+sSvqJybz0YLz4GJCxIalVLdaLc9YYzQhYXObYbOAbLZjVBmE+7sQTe51VViHhKNX
*/
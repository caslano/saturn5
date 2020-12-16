// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_ENABLE_IF_STREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ENABLE_IF_STREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>                // BOOST_NO_SFINAE.
#include <boost/utility/enable_if.hpp>                  
#include <boost/iostreams/traits_fwd.hpp>  // is_std_io.

#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
# define BOOST_IOSTREAMS_ENABLE_IF_STREAM(T) \
    , typename boost::enable_if< boost::iostreams::is_std_io<T> >::type* = 0 \
    /**/
# define BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) \
    , typename boost::disable_if< boost::iostreams::is_std_io<T> >::type* = 0 \
    /**/
#else 
# define BOOST_IOSTREAMS_ENABLE_IF_STREAM(T)
# define BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ENABLE_IF_STREAM_HPP_INCLUDED

/* enable_if_stream.hpp
kaXt40100kRnor80H3NN3RVKOXQ25VIi+QiW2VmpUgdmDW6mxHOqv4bZFzLnfNa3mTJZIv7t9DyU5t9Y4+gjtfFvXcdZ5w2RtXVok7pOfQPi8CrkFNzbekg7JKTXvo5TXuOljdz/PO2skhnLqc9Bko8A8opc/2bRPd8SXSrC/KaYttNR8lzLSvPQM78xWl5/lDhnM3+pk4w9GVbs++aPPzu0b37sdgqS3DZQtO/gJv2B/OPm5F3W8kv7CqTgZtpd+N6f7WtYcvyJQbwBfAy+SxxLZ5hxJqptlDSt45tFd2tcB3KbGlfHOisu0dtuygzPMcSU49ocx3+Jr4E10hdq+7skTH5cVcatC+0P/R7jiYk3ycQbtOzhuRdvhD51y0E6pufk5s0rHTuqn+PoVLGcPvU0ZVhLzofG/cou8nuNRfvRkfgixqJuGt9pM53wd9nVrALresrpPuQl5DBS0060OiAT7CrWQuRKO9HYeGgsZXK3vcw6aM21A1YHtTuwUdwLfHFWX3uYXd+ahVyO3IY8jrxjn8EUuMYaT0j/Lv+vrX2+Ff4Eydcu0pwl7pUD+3ALG9M03ZvEP9mMRfskHwN979k1rZa+muoein+LP846z0/8ptyC7g+JW2gMjC9ti9I3a2s/+Vmuo1tkxsXSsWvhXPe4fqvUxWBjg6GuXKO6tKsdSRZHEWNd6W+Ea4wzvwVDJB8jrEGh3wfOUmY7bhnEk2CFjcmFRXkF7Iq8cJ5l6uUBaUMXxtVmjGhtDw9oHJqWLoF4qxZufcmbjokF0509dCVNeyPbCs3Pnb8WEkcTMx6PlvM+nAev/YKkPU3G+yeIq5/4pwbeo4zdY3SKjtFvS1rnxO0N1LXqxCWRX+5dnHmfdIapKCRUayD3J+sZk1uWjskytp6ibK3jciJsi7RLLXt8do3TkXoat/EnPjOOywLSGxHO+Tu2sd05euVInUYfs7WMa8OGojtAxuv+5RivaSOl4zXnLcw599XzY7fHo3as1E3HK9XdH+M47jxXnMHC3836jJNXwAOZttPQ74HTH+pofyAeaXvkHzfTJsX2xC+ljbBuvbEl5w/q+futwn8vNujvBdmX47zQ/fKUE2xnGDsu9+KPqO2M2OZLh66XUfPEZ43pNNK9c0qvN+cCMU9EuqXt455TVOxtm0jD2WU+I4Tq0YmvjsbntiWToKFtJHQcpKxKwtNVvLAgNrtShDO/jeeXYTOppOw8lGkb6nzTFsOfwY5pjLURaY9qNytruskXt6huy1mx5S9reuw2oVTX2NRpH4NNnVj7nTuvB2p55zW/NK8/zEZYOfKa/0/Oa6gf7U8ydoXkaIPspr1uLe235bLxtfUkz4NJcJv4N/XMs4Y1eW5bjjzXTYw9z/u0Yg9pRB/r+4TVpfWr9p68bQ4lwzHZ8nxjeT3fpMLHJK4HLM9nOJe9r3dF70bC+axu5DvBiv7co7+55ve2XRTbXQke42ZbzXtRshk3DQc35nk6OD4Fx33SPBA325o+gXPv5/4yx5omYeOlE18djU/sXM0p/V0hfT94/w7vdSrlt8GTusdxn31KQdcteS3fu2PFLdXmZXxyrPz7d3jb5om+LsfbBk90mzreNofKb9OovDaivNcJlX99T3nXD0WzHfVV6T70cq9aQvi6vuA7t2K132L25Hf6qrb14og9+XN0LdFMGAdz4RE4Gdmr4TI1XDwyOnRNDTcN1oBnwVR4NmwIp8MMmA276nl3PVf7Kvoukf6n8bvtq0xRvV22vuvSd37FsCuyzXFQeyp14CWwPbwUdoJV6cwD1M7RcPhzmAVvgAVwLbwYroPL4Xr4M3gzRKwN8B64ET4AfwkfgbfC5+Cv4Ws=
*/
// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <streambuf>
#else 
# include <streambuf.h>
#endif 

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::basic_streambuf< ch, tr >
# define BOOST_IOSTREAMS_PUBSYNC pubsync
# define BOOST_IOSTREAMS_PUBSEEKOFF pubseekoff
# define BOOST_IOSTREAMS_PUBSEEKPOS pubseekpos
#else
# define BOOST_IOSTREAMS_BASIC_STREAMBUF(ch, tr) std::streambuf
# define BOOST_IOSTREAMS_PUBSYNC sync
# define BOOST_IOSTREAMS_PUBSEEKOFF seekoff
# define BOOST_IOSTREAMS_PUBSEEKPOS seekpos
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_STREAMBUF_HPP_INCLUDED

/* streambuf.hpp
8CWVMu7tPLQFwqGEUWfXH/Ggpensh5sHSuGi5NYLh4lQCaAHWKzjtwXuidjFXl9IuTf8nxMmhBedSbNGaWVx4+vRGXpaO1IgYWIRWWvtmghNk6TZyCkGJWeQ8z3tGCcGBVsnwis7BER425IHoEi0R7WjJY6DzRNeWkApx/cyVkrrektgs7OpSVL8XBlctvoYUsblKJeeUYeY1VBUP+mpBJOwfsSdYPhZnxB66rNtpCDXLEmfAb0Jtj3efb4DCcLQ30MyC43wizyU+qd6bLPzxrY2s/Il2D9A7RstfoqJJZ7pIVq6EQjVrbwt6SXNzBwIbdQucjmmJUXLGfUpAQRndHE3I+tGMIJZXebOsjgjUVVXxRMWf6Hm9wSoCN5kGkzd1nvm2iS460HRHAgY8B1DVR5FERqbBx5oAQ4xvQNRmJGb3sH9d9Z1/o4O6sooIP90pr5uCq5bBQNHTsZkM1cdJeFiHrkpCbZaafycHbe92ZqkIn+N0Us0tvngc2/22krhzcm5sdKUN6x2QiUUR8qOv6bDCK5Rg9XHve1fgBlE7guL3DdIBJhG6xGDkQ==
*/
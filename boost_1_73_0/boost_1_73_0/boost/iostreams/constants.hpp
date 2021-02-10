// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains constants used by library.

#ifndef BOOST_IOSTREAMS_CONSTANTS_HPP_INCLUDED
#define BOOST_IOSTREAMS_CONSTANTS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#ifndef BOOST_IOSTREAMS_DEFAULT_DEVICE_BUFFER_SIZE
# define BOOST_IOSTREAMS_DEFAULT_DEVICE_BUFFER_SIZE 4096
#endif

#ifndef BOOST_IOSTREAMS_DEFAULT_FILTER_BUFFER_SIZE
# define BOOST_IOSTREAMS_DEFAULT_FILTER_BUFFER_SIZE 128
#endif

#ifndef BOOST_IOSTREAMS_DEFAULT_PBACK_BUFFER_SIZE
# define BOOST_IOSTREAMS_DEFAULT_PBACK_BUFFER_SIZE 4
#endif

#include <boost/iostreams/detail/ios.hpp>  // streamsize.

namespace boost { namespace iostreams {

const std::streamsize default_device_buffer_size = 
    BOOST_IOSTREAMS_DEFAULT_DEVICE_BUFFER_SIZE; 
const std::streamsize default_filter_buffer_size = 
    BOOST_IOSTREAMS_DEFAULT_FILTER_BUFFER_SIZE;
const std::streamsize default_pback_buffer_size = 
    BOOST_IOSTREAMS_DEFAULT_PBACK_BUFFER_SIZE;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CONSTANTS_HPP_INCLUDED

/* constants.hpp
D+eoYv5wqybuD2coIv5wrR662qrqPTNOZvWH87kY/vBqqGz+cAaTxR9O1Ff4wynqSn84TRv2h2uU0dUY5seugsjiD+fyWP3hfBq9P9zIovSHc1Qxf7hVE/eHMxQRfzisJ/aHayP7/OF4XIk/XBfV5Q/3/kLy7e8av5lnD8l8uf1LYft/5epzOnnZ/5JNknzEVTQY9gsFXo6cnvwHUEsDBAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAlAAkAY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzgvbGliL1VUBQABtkgkYFBLAwQKAAAACAAtZ0pSDiSOSx0AAAAgAAAALwAJAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkM4L2xpYi8uZ2l0aWdub3JlVVQFAAG2SCRg09fSy0tO4tLX0isuzQdRpcWpRSC6LLmgKD+LCwBQSwMECgAAAAgALWdKUuO1/BZmBAAAHz4AADAACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDOC9saWIvbGliY3VybC5zbG5VVAUAAbZIJGDFm0tv2kAUhddB4j9YdJNKMTIUCFl0YXBoItEU1VK75mEiVy5GBtJKaf57TAMh4HmcO76Od+DM3PPN
*/
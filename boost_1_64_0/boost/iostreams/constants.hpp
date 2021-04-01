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
mrAHwVrdVnlbDC18DZlYgh2YbWqySIjBT2iy0Nhzq1RTBzmwKQB0vtTnXpE4GR8ksjpLTPXtRPdjhU4DDnYA/VOnTFJTidfS3liyjU+dNPlZOLe+RTh4lVWQoSjOOTtWm4cscoMx6gMV2nXkvWDqIX/fGOiGi6ZyoL8oYGWTwWSkPy76mf28VHZe7ZmueSb1xRb0oitjsaKOUfxgDlbgGw5dLkAMk0gUbaglstNUiz8A38y0UKqdQ4TFIiOHzfJ39jiQFwA/K6n43zfL/BZJe/ZFft6NiHvOyb7V7ze8ygL04f6o/s/NZSc6xTxnlHyTo9h/xCK0aD827kSnfANHGyMqFYzxc3DEpKqhAyb/S4yJHqyCq5fAj1KQApfHqJVpyy+Tz0VQg0x5mk0kzvJzsSV2v6OJgM3R3g153fIu7u1KCyo24NxEy7jCk/zDRPYzWjn8EGiak+amB+7MDfk9WekVDUGbkBhxauTwaBZFU1op45R3BmMGPyoacsqElVPb3+fes05zCbhJYGmtgAKGIoecGPFoPTwGT8RU4/k6GLZ8t3yGBOE9/fXwcg==
*/
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
js1RIzKS+xpbkyL9cEM6nk38kSM9+swNByH7InUyv4dRfbjTEcFfTvcx2i/qAhS2DFYOla3JVe0D7AerczFaJ+k8V/iYMyQPyaK/jFYbIOeYD9laavylvaeB78WZs/ddq1/Evusjl6l919qWvepy85TLkvxJrH4x4U9iD8Kv6RnpLoSf1OHHEd6qYR5FeMFy7L8aS4N3Lr55yYJ5lbctutWQ/++4c8kCY5GEjF7npbnqvLTv
*/
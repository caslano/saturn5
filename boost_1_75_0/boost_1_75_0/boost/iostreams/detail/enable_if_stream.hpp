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
Oz49s3d+dFLf1DvxYrEttSelR22Lq3N0qbRtF979ucsKse8yHA5DgOYotG5qKukw68OOWiOh15BECnmZZsDR7adfOVsyMEP1Oks4lj9Fy6b7G43bRTXhSlZ9hUHX2Uf3RYANz3PBlAOrZmFNdaY9UNVv6HjzfKaWxdlVjPkwHgZ6YQaIFahtTSHMQt+cJRXS0E860Ry06zUT6asgEY/fb9o0fbLLmaV7mmalDWWLwxrBpktfguq0U9xxVbwri/ntbouCLX+juKBpbpAey5A8TFnu2ztMZYWJf7y3Wjih9STVHoo1fmJxNa0xwazEhc/PPZROayikppIAfiSVEmv+hDZUosiHec62xDGVrjbnDjzZNR4iqTMPaAdxaO6vT2zQqVSVGVA+lH10d7FFZXs2j+8TwL11WX34QfZ7brpLEiluaEd061RmZIW5C+jMLckFwQ2JWGbFl0o5Jjb+TpE1Bmm2u7Df7S0YQRnlC86xY9zjpmMbdTbVlx3De6Y+61IhyMEdqLtrNbvv5nx8aDMj6lLyt6QnHqEVC5qSgdMTSztO3b2n7PcWg31qcVyImrOjKZuBYJRii6EjNbxT1a8k1aorIMrXLDDNUvmThEXlLPqn9LPy8UScgf0vtQILFV/5+e5eXOGcavLOgA5bVmkHa94Jhgn4uT9VU4JUuRaqYVKQXMgYAqoKsytJ2dYMcTlXT3TUl1rNfIaWG/oC
*/
// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BZIP2_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_BZIP2_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#if defined(BOOST_BZIP2_BINARY)
# if defined(BOOST_MSVC) || \
     defined(__BORLANDC__) || \
     (defined(__MWERKS__) && defined(_WIN32) && (__MWERKS__ >= 0x3000)) || \
     (defined(__ICL) && defined(_MSC_EXTENSIONS)) \
     /**/

// Specify the name of the .lib file.
#  pragma comment(lib, BOOST_STRINGIZE(BOOST_BZIP2_BINARY))
# endif
#else 
# if !defined(BOOST_IOSTREAMS_SOURCE) && \
     !defined(BOOST_ALL_NO_LIB) && \
     !defined(BOOST_IOSTREAMS_NO_LIB) \
     /**/

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it.
#  define BOOST_LIB_NAME boost_bzip2

// If we're importing code from a dll, then tell auto_link.hpp about it.
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif

// And include the header that does the work.
#  include <boost/config/auto_link.hpp>
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_BZIP2_HPP_INCLUDED

/* bzip2.hpp
CsMeYdXq0/I0MO5HMOglO+MEZtndsvJm8uuRTdN3xEyU/BWxHPX3V+Qu/RUvO2BDFzE/UhE/cMXK83WcYs2zRecZ9afUoRM/KIXRCXQG2QFFkpv3rJZ1YnTiWJTZtDWrkzzTUUv/1M2kCGLAo5YB36KYubUMnlHQ6F6Fzz2/rL+aN/Bb4AqkTH0dSEeoGxJrh9DXS9X8NDw63nCp1LszK1QUYD3csdHlhmt9gZ7BZb/uER3LDLN8olRtYSnvot/qC1HVFn+hRbWErB/Hbyenh69fO34sLtaR4yw7zPJ34SucWBPb+WCxJqboT8MQHVBm9RJ3Ai8uolx5RvsXMvdQnM7PG2QkIZF/FKK1bq7imY7MUCVDlJeFdE1C0+HXLVIVZix8bYZhhmpf6uxiYx8iNZu6+LLNyfbB9XZukFiro5JG6SUOsbaiVPgXiBStD5SpazfCw6MD/K1VbjHZQDMJ6BnpYaMkosbE4OSr/HsisZk7Joi+xYJwM/3zfU+uhJ9zs3NSkfuLxvX/vHlNvxfJxValTd2ljkJjIk8j2kwBjiCl24mkJpFN6bUzYTLfOqErd53YT50VhhWjMLX8sVr73Wa0zzYfLz9Mjo+AYDV3fO5mtXFbv2C7BfZ3p05N7dYC/XGnY1CAfM7ZZv/F
*/
/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/restrict.hpp
 * Date:        Sun Jan 06 12:57:30 MST 2008
 * Copyright:   2008 CodeRage, LLC
                2004-2007 Jonathan Turkanis
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the class template boost::iostreams::restriction and the 
 * overloaded function template boost::iostreams::slice.
 *
 * This header is provided for platforms on which "restrict" is a keyword.
 */

#ifndef BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED
#define BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED

#include <boost/iostreams/detail/restrict_impl.hpp>
#define BOOST_IOSTREAMS_RESTRICT slice
#include <boost/iostreams/detail/restrict_impl.hpp>
#undef BOOST_IOSTREAMS_RESTRICT

#endif // #ifndef BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED

/* slice.hpp
pxNNWpIj6xrX0r4ygCHkLsW8RtFSBQqLD4ypf8i2fFTOHtyOpVhQ2LcmDTRmZOYtBVc7B+pE8hb+9D78dMIIWB4l/xaLZgNn6Spp1yOH8nOf/ff+MQjOxW/9k33iCZJIIoByzMe1k4Dnz5n+PpS5kzbwAIxm1Mavm5WAmWc+CJPdt/M5yp8nB2Z1Sn4i5nPry56DC1cM+GxmlbnSUqGHgM4whbSP445YojLXJd/Rra9Ju9II60mSKyudojrLgFTPwPxfaedx/lbeQnIcenlVZWan5LrYGWHKOUfUvtytIjJ4pIWePKY7iK6cCg2WYNTjJS3SE1QcAPmeeQXiDmnc0dC+WZG3nVF5xu1wP0XJcqJrSD2QIauIZTun2mxMNeGw3p20gB+6k7QGoRSvEMKcBodMlosfzL5wjeXCrqJezRpOtPv6+zOQTwSYVcDzTPJ1JIN9cBXOaQm5VD3quaaS4QFS8AP8tKUyYBdkRiLXNJwM2Bh0pmKMj/qWTtuar+E/0mXX8IQF7OwSNahgePbNOOKyBILjDY53VZXuktfS1xyX1FYwMSHqKBGqlA==
*/
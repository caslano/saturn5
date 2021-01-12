#ifndef BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED
#define BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_HEADER_DEPRECATED("<alternative>")
//
//  Expands to the equivalent of
//    BOOST_PRAGMA_MESSAGE("This header is deprecated. Use <alternative> instead.")
//
//  Note that this header is C compatible.

#include <boost/config/pragma_message.hpp>

#if defined(BOOST_ALLOW_DEPRECATED_HEADERS)
# define BOOST_HEADER_DEPRECATED(a)
#else
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
#endif

#endif // BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

/* header_deprecated.hpp
IUYnjo20RpKQqUg94nQ3hTRS4RzkKmllk+7iV0gPOY+ELcc3pDuSjcxBSpfj+gxPIU4u7NEcqzKMRZKQMSv++bkbZ7LvYmQHcgoxqNRFkRikdAH2g9nIVGQBsg05hThfJRyJRQYik5AFyC7Ec725P8d8G9dbe+0U/gTzAy+PtEdSkZnIamQ/4t/8m3/zb/7Nv/0/bH/w9/9JIzP+dfP/tY/kecG1tp/cqmsjNiQaqUb4TBbo
*/
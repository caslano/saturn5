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
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
*/
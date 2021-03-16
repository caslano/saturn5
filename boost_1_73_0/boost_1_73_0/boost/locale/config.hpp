//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_CONFIG_HPP_INCLUDED
#define BOOST_LOCALE_CONFIG_HPP_INCLUDED

#include <boost/locale/definitions.hpp>

//
// Automatically link to the correct build variant where possible. 
// 
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_LOCALE_NO_LIB) && !defined(BOOST_LOCALE_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_locale
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled


#endif // boost/locale/config.hpp
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* config.hpp
TBlYoGXAS6/UTmQg3y4D1o9SdC4BFysJsO3v7Pg/XfF/huK/Q+0QO5I7RE/uUMJCGtYh/xeE+V8acy78r6HX1E74/0oEdQL230U4HzE4KzmYqeTAqeSgQFEJj0VLKqEXz7ohYes0LCwHjsaWTSBEMEHZ0xDetl3ddqX1/jl6T1d9iTWD/W3Q5hCgbbFprVqWKuk1IcLykrViWSLrJW5N12D+5QoKussprjsvYYq0qFgHVDIt6r8oWXqJ2n7U7lI=
*/
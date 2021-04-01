// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP
#define BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif


#include <boost/type_traits/conditional.hpp>

namespace boost { namespace detail {

    template <typename TargetChar, typename SourceChar>
    struct widest_char {
        typedef BOOST_DEDUCED_TYPENAME boost::conditional<
            (sizeof(TargetChar) > sizeof(SourceChar))
            , TargetChar
            , SourceChar
        >::type type;
    };

}} // namespace boost::detail

#endif // BOOST_LEXICAL_CAST_DETAIL_WIDEST_CHAR_HPP


/* widest_char.hpp
LYj8Dg830ecb4AKqP2lJ4gl9/96r0F+BvZny0MTm5YJxTxn14dGq2+HMYVuwBgib6gAbfnqKealOn8HmQ3tUXYEE2JQXxPc3kWXyVdpCVn3uAJ/VsO+OxoOIT29fP0PYk4ZPSzMMGLTes6DYNp36t4QkPFTdc6uMb4VYZow0kYr1JAbTrpy59cqhEinLzfdABh18BWZ4gbetNcaaU0Y/VM8mJKJhIDg9HmHx7LQtFpcQC6l5EeEOe8FkB0fWgbmBuZnEozcDVh/NUXqef4jBGGW0m79Dj/XaSPB9bDVYJ8dnCEiwnjKioVKsOJx77ljHgAO94ok29dfc7VTwOsckerdgll19lIRxyGS1tCCwcKcXwNuGom5idRBZMXv8vQoSlw7s40ggghbsuq130SzNHViNAnjuS0vUpxbnMhUABwnICt1wud3HG/VtL04Pe/v/zlH6P/6xR8F4orEIR7D/dXNTkFHNqO601fGoJeF6TRTi144iB4G3fiXeeswk9bKHFTe289rYCYrVPtsqFDsrnwg1ehzshYMwSQuS/u1KxvvAhK+HacPcN1sHdw==
*/
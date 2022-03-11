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

#ifndef BOOST_LEXICAL_CAST_LEXICAL_CAST_OLD_HPP
#define BOOST_LEXICAL_CAST_LEXICAL_CAST_OLD_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

#include <climits>
#include <cstddef>
#include <string>
#include <cstring>
#include <cstdio>
#include <boost/limits.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/lcast_precision.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_NO_STRINGSTREAM
#include <strstream>
#else
#include <sstream>
#endif

#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include <boost/lexical_cast/detail/widest_char.hpp>

namespace boost {
    namespace detail
    {

        // selectors for choosing stream character type
        template<typename Type>
        struct stream_char
        {
            typedef char type;
        };

#ifndef BOOST_LCAST_NO_WCHAR_T
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
        template<>
        struct stream_char<wchar_t>
        {
            typedef wchar_t type;
        };
#endif

        template<>
        struct stream_char<wchar_t *>
        {
            typedef wchar_t type;
        };

        template<>
        struct stream_char<const wchar_t *>
        {
            typedef wchar_t type;
        };

        template<>
        struct stream_char<std::wstring>
        {
            typedef wchar_t type;
        };
#endif

        // stream wrapper for handling lexical conversions
        template<typename Target, typename Source, typename Traits>
        class lexical_stream
        {
        private:
            typedef typename widest_char<
                typename stream_char<Target>::type,
                typename stream_char<Source>::type>::type char_type;

            typedef Traits traits_type;

        public:
            lexical_stream(char_type* = 0, char_type* = 0)
            {
                stream.unsetf(std::ios::skipws);
                lcast_set_precision(stream, static_cast<Source*>(0), static_cast<Target*>(0) );
            }
            ~lexical_stream()
            {
                #if defined(BOOST_NO_STRINGSTREAM)
                stream.freeze(false);
                #endif
            }
            bool operator<<(const Source &input)
            {
                return !(stream << input).fail();
            }
            template<typename InputStreamable>
            bool operator>>(InputStreamable &output)
            {
                return !is_pointer<InputStreamable>::value &&
                       stream >> output &&
                       stream.get() == traits_type::eof();
            }

            bool operator>>(std::string &output)
            {
                #if defined(BOOST_NO_STRINGSTREAM)
                stream << '\0';
                #endif
                stream.str().swap(output);
                return true;
            }
            #ifndef BOOST_LCAST_NO_WCHAR_T
            bool operator>>(std::wstring &output)
            {
                stream.str().swap(output);
                return true;
            }
            #endif

        private:
            #if defined(BOOST_NO_STRINGSTREAM)
            std::strstream stream;
            #elif defined(BOOST_NO_STD_LOCALE)
            std::stringstream stream;
            #else
            std::basic_stringstream<char_type,traits_type> stream;
            #endif
        };
    }

    // call-by-value fallback version (deprecated)

    template<typename Target, typename Source>
    Target lexical_cast(Source arg)
    {
        typedef typename detail::widest_char< 
            BOOST_DEDUCED_TYPENAME detail::stream_char<Target>::type 
          , BOOST_DEDUCED_TYPENAME detail::stream_char<Source>::type 
        >::type char_type; 

        typedef std::char_traits<char_type> traits;
        detail::lexical_stream<Target, Source, traits> interpreter;
        Target result;

        if(!(interpreter << arg && interpreter >> result))
            boost::conversion::detail::throw_bad_cast<Source, Target>();
        return result;
    }

} // namespace boost

#undef BOOST_LCAST_NO_WCHAR_T

#endif // BOOST_LEXICAL_CAST_LEXICAL_CAST_OLD_HPP


/* lexical_cast_old.hpp
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
*/
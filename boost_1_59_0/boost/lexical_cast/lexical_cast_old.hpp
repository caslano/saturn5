// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2022.
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
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

#ifndef BOOST_LEXICAL_CAST_INCLUDED
#define BOOST_LEXICAL_CAST_INCLUDED

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

#include <boost/range/iterator_range_core.hpp>
#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include <boost/lexical_cast/try_lexical_convert.hpp>

namespace boost 
{
    template <typename Target, typename Source>
    inline Target lexical_cast(const Source &arg)
    {
        Target result = Target();

        if (!boost::conversion::detail::try_lexical_convert(arg, result)) {
            boost::conversion::detail::throw_bad_cast<Source, Target>();
        }

        return result;
    }

    template <typename Target>
    inline Target lexical_cast(const char* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const char*>(chars, chars + count)
        );
    }

    template <typename Target>
    inline Target lexical_cast(const unsigned char* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const unsigned char*>(chars, chars + count)
        );
    }

    template <typename Target>
    inline Target lexical_cast(const signed char* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const signed char*>(chars, chars + count)
        );
    }

#ifndef BOOST_LCAST_NO_WCHAR_T
    template <typename Target>
    inline Target lexical_cast(const wchar_t* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const wchar_t*>(chars, chars + count)
        );
    }
#endif
#ifndef BOOST_NO_CXX11_CHAR16_T
    template <typename Target>
    inline Target lexical_cast(const char16_t* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const char16_t*>(chars, chars + count)
        );
    }
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
    template <typename Target>
    inline Target lexical_cast(const char32_t* chars, std::size_t count)
    {
        return ::boost::lexical_cast<Target>(
            ::boost::iterator_range<const char32_t*>(chars, chars + count)
        );
    }
#endif

} // namespace boost

#undef BOOST_LCAST_NO_WCHAR_T

#endif // BOOST_LEXICAL_CAST_INCLUDED


/* lexical_cast.hpp
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
*/
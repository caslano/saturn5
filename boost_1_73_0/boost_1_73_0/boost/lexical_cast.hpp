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
qBn8+9y06vDSHDTmXsjHbhQnE3fq+ajTxtB/uIfLSc+d9TrBU+wMGi2gbg+yYhlf8Uz3BtzP2NLNO0SrdKihaEK01mVaJCQKXQhNsn4QgwlmchShicXkcmM7YZA4713nQzJd+E7sBb7JwKPbaGBeyBblcjAAJ/Ntd0no/r7wQneSTGf2b1HrDQN6sWz2gedGF42XY3DtSU9k0I4GGMnM8z8cVt5FcYhvkf9+4b2TaCNo0dc/sOBleseGUWzHC2Rwzmrs0BvsxeAQCzEhegI0ha2jqeVhf7kJsI3i2vOpUUy88OUKqoSuHydRsAgdV0uMnZv0no3JL7mVV1mjYzQ0jFhNTnAzx0rs03NI/i0i2zCOSvUI4qahAeD7dL6Ik7Z0m98di/2s+8wdFcgP4NgYDHh+7Ia+PQNLo6oMqm2ALaj/gA4c+qJtlqFaZ4P6wdCez11/coqH9hHt5oieuE4cYBs26AdbVW3VVSHuDqX2dhBVKmlg1J1TT4miKMQjKQht792n0jrYO382UO7xaVOShWTDb8FgmlJTtV7lwbK+kohvAtGta1F/LYYrncI3YNhs69Pttdcty1qsVol+h5A0Tmp5UtXirk43Qz8MplPw7Rvs5ndaEPR320pp2bg7A5/RgA+PqZ6rHmuOkzTe
*/
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
5g6d5T34vhuss/wE38/w/QLfJfgsQ3SWXeC2APRmTGPV9L/o9GLk/a8qC00JPm5Z6e2UzamrS1vQ6lJNApPiy9uDVheOdwEY8tvjdIXBrlVr6m9h+c6/bBzVFhK6RLAF5FR/C0ifpSiIL3/Viy97evHl5+74f5svJ/4aX77pinyZEwqG6klvhvw8LEbe8ouUv2bb55H0+fPIo/bZJG/2LPJoiZ2klM8h2TNtBNJmzVxMVkM6dQFmAXoAbh7zrV4N8OWqdzXkoz7Iay9X4x6aOY+kzH6CpM8sJ0ll5eAuhkbNg28uSbI/RbJnl5GpT9pIxvyFZNLsJwnA22eWL8Y85dQDZaTTM7rVqyH/HNxTg/x0bwTKoOlQjn2BDeqdXWabjX8ZBSKn4mbnbNwTW6hFrYby/f6kdLI6E7709LtmzbprMS1nFvwbHZUO/6LQsxj+kbS0Cc88M4Fuza3OJnYyDwYlncyn7qMQno2kAb+zaLgEYghJIeVkDrjZZCaxURfzzYLQYghBe2j+QJiVs8Afw8qb1yuOlV0eFAP9TesJhFl9CBWIewh88yhOs8kTFPeZkE5IEimjbroK+ZDaNnTn0nQ7eYriPhsgCZlKnqRtyQDcF4I7CeKfpPBYvp2WuthfT3lQDLYX/U9CC7R659A6WJ2zVTyxXgbP6rZDW21quxAHG/w+A2XPpngzfOb7wwyvYAgYb4pj77gkaDG6
*/
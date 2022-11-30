/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/csv_decorator.hpp
 * \author Andrey Semashev
 * \date   18.11.2012
 *
 * The header contains implementation of a CSV-style character decorator.
 * See: http://en.wikipedia.org/wiki/Comma-separated_values
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_CSV_DECORATOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_CSV_DECORATOR_HPP_INCLUDED_

#include <boost/range/iterator_range_core.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/expressions/formatters/char_decorator.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

template< typename >
struct csv_decorator_traits;

#ifdef BOOST_LOG_USE_CHAR
template< >
struct csv_decorator_traits< char >
{
    static boost::iterator_range< const char* const* > get_patterns()
    {
        static const char* const patterns[] =
        {
            "\""
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const char* const* > get_replacements()
    {
        static const char* const replacements[] =
        {
            "\"\""
        };
        return boost::make_iterator_range(replacements);
    }
};
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T
template< >
struct csv_decorator_traits< wchar_t >
{
    static boost::iterator_range< const wchar_t* const* > get_patterns()
    {
        static const wchar_t* const patterns[] =
        {
            L"\""
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const wchar_t* const* > get_replacements()
    {
        static const wchar_t* const replacements[] =
        {
            L"\"\""
        };
        return boost::make_iterator_range(replacements);
    }
};
#endif // BOOST_LOG_USE_WCHAR_T

template< typename CharT >
struct csv_decorator_gen
{
    typedef CharT char_type;

    template< typename SubactorT >
    BOOST_FORCEINLINE char_decorator_actor< SubactorT, pattern_replacer< char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef csv_decorator_traits< char_type > traits_type;
        typedef pattern_replacer< char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type(traits_type::get_patterns(), traits_type::get_replacements())) }};
        return result_type(act);
    }
};

} // namespace aux

/*!
 * CSV-style decorator generator object. The decorator doubles double quotes that may be found
 * in the output. See http://en.wikipedia.org/wiki/Comma-separated_values for more information on
 * the CSV format. The generator provides <tt>operator[]</tt> that can be used to construct
 * the actual decorator. For example:
 *
 * <code>
 * csv_decor[ stream << attr< std::string >("MyAttr") ]
 * </code>
 *
 * For wide-character formatting there is the similar \c wcsv_decor decorator generator object.
 */
#ifdef BOOST_LOG_USE_CHAR
BOOST_INLINE_VARIABLE const aux::csv_decorator_gen< char > csv_decor = {};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
BOOST_INLINE_VARIABLE const aux::csv_decorator_gen< wchar_t > wcsv_decor = {};
#endif

/*!
 * The function creates an CSV-style decorator generator for arbitrary character type.
 */
template< typename CharT >
BOOST_FORCEINLINE aux::csv_decorator_gen< CharT > make_csv_decor()
{
    return aux::csv_decorator_gen< CharT >();
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_CSV_DECORATOR_HPP_INCLUDED_

/* csv_decorator.hpp
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
*/
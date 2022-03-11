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
const aux::csv_decorator_gen< char > csv_decor = {};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
const aux::csv_decorator_gen< wchar_t > wcsv_decor = {};
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
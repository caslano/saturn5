/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/xml_decorator.hpp
 * \author Andrey Semashev
 * \date   18.11.2012
 *
 * The header contains implementation of a XML-style character decorator.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_XML_DECORATOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_XML_DECORATOR_HPP_INCLUDED_

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
struct xml_decorator_traits;

#ifdef BOOST_LOG_USE_CHAR
template< >
struct xml_decorator_traits< char >
{
    static boost::iterator_range< const char* const* > get_patterns()
    {
        static const char* const patterns[] =
        {
            "&", "<", ">", "\"", "'"
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const char* const* > get_replacements()
    {
        static const char* const replacements[] =
        {
            "&amp;", "&lt;", "&gt;", "&quot;", "&apos;"
        };
        return boost::make_iterator_range(replacements);
    }
};
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T
template< >
struct xml_decorator_traits< wchar_t >
{
    static boost::iterator_range< const wchar_t* const* > get_patterns()
    {
        static const wchar_t* const patterns[] =
        {
            L"&", L"<", L">", L"\"", L"'"
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const wchar_t* const* > get_replacements()
    {
        static const wchar_t* const replacements[] =
        {
            L"&amp;", L"&lt;", L"&gt;", L"&quot;", L"&apos;"
        };
        return boost::make_iterator_range(replacements);
    }
};
#endif // BOOST_LOG_USE_WCHAR_T

template< typename CharT >
struct xml_decorator_gen
{
    typedef CharT char_type;

    template< typename SubactorT >
    BOOST_FORCEINLINE char_decorator_actor< SubactorT, pattern_replacer< char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef xml_decorator_traits< char_type > traits_type;
        typedef pattern_replacer< char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type(traits_type::get_patterns(), traits_type::get_replacements())) }};
        return result_type(act);
    }
};

} // namespace aux

/*!
 * XML-style decorator generator object. The decorator replaces characters that have special meaning
 * in XML documents with the corresponding decorated counterparts. The generator provides
 * <tt>operator[]</tt> that can be used to construct the actual decorator. For example:
 *
 * <code>
 * xml_decor[ stream << attr< std::string >("MyAttr") ]
 * </code>
 *
 * For wide-character formatting there is the similar \c wxml_decor decorator generator object.
 */
#ifdef BOOST_LOG_USE_CHAR
const aux::xml_decorator_gen< char > xml_decor = {};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
const aux::xml_decorator_gen< wchar_t > wxml_decor = {};
#endif

/*!
 * The function creates an XML-style decorator generator for arbitrary character type.
 */
template< typename CharT >
BOOST_FORCEINLINE aux::xml_decorator_gen< CharT > make_xml_decor()
{
    return aux::xml_decorator_gen< CharT >();
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_XML_DECORATOR_HPP_INCLUDED_

/* xml_decorator.hpp
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
*/
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
w6Ys66drn4tC+op6dB4FEO+ti4Z36RsSNVg4Q1yPaCiLEGuCmKiVdutZJubF7/TV729yYnNu+qc9ip9R/Ocv9C542nGiC/lnjWEA7Ao58poVaX0Qa5BMktd02D+kGMIL+wSjGH8L8jH+5qYESX1J2AdpGLyYOdsCjeKK8jneX3SLjxyjCiC2Yj0hUiwhlIlzC3Cn6AtyWTrS1Xk7zIU3X6E9v+qFvmTo8smR4slWmYZBYKiElw5bdvVWyr1qwyWLV6EK6DCHcVn43FhBteTjQrzFgYme9+OfywrUiCZlXs4Hku6HJLn9DGAx7a9+HX777khbFyfLTxoiyX7DhcEOX8iJHG8i7ZYWGcm8l4pzg9jGr5VZYwifsSGpNXZRLC1sBnKbIOHp/TVRJtc2M89rrCR7rLaD6CvasaZS1o23OALTQgdqlKdDwWLM6VtH2LVLhnRXiwPy+I8luhtlkDAUuVnF9dindXi7Zu+Afr99+cs5vTkqNBYT3Y5OyuuLmIPjdGYMsg8NC7zdu3HEPYpZ1hEPL91eg69XumyGLL0vkJoJ2DEDLYDkLBmvwVhI6syJ/OTHq7JGCUf0vwuSmtygwbg2gGl26NuZi51kWUdDwd4g4dnE9+VThgEpD9M81Fj4FH5nnXpJKWyUdo2F2i5AweGkkp1QPnFpSflsIYqp4nzKtOrOUdA0R5TCXrXh+3Aqz7M6tLjfLdTMgPx+
*/
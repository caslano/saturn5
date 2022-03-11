/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters/c_decorator.hpp
 * \author Andrey Semashev
 * \date   18.11.2012
 *
 * The header contains implementation of C-style character decorators.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_C_DECORATOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_C_DECORATOR_HPP_INCLUDED_

#include <limits>
#include <boost/range/iterator_range_core.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/snprintf.hpp>
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
struct c_decorator_traits;

#ifdef BOOST_LOG_USE_CHAR
template< >
struct c_decorator_traits< char >
{
    static boost::iterator_range< const char* const* > get_patterns()
    {
        static const char* const patterns[] =
        {
            "\\", "\a", "\b", "\f", "\n", "\r", "\t", "\v", "'", "\"", "?"
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const char* const* > get_replacements()
    {
        static const char* const replacements[] =
        {
            "\\\\", "\\a", "\\b", "\\f", "\\n", "\\r", "\\t", "\\v", "\\'", "\\\"", "\\?"
        };
        return boost::make_iterator_range(replacements);
    }
    template< unsigned int N >
    static std::size_t print_escaped(char (&buf)[N], char c)
    {
        int n = boost::log::aux::snprintf(buf, N, "\\x%.2X", static_cast< unsigned int >(static_cast< uint8_t >(c)));
        if (n < 0)
        {
            n = 0;
            buf[0] = '\0';
        }
        return static_cast< unsigned int >(n) >= N ? N - 1 : static_cast< unsigned int >(n);
    }
};
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T
template< >
struct c_decorator_traits< wchar_t >
{
    static boost::iterator_range< const wchar_t* const* > get_patterns()
    {
        static const wchar_t* const patterns[] =
        {
            L"\\", L"\a", L"\b", L"\f", L"\n", L"\r", L"\t", L"\v", L"'", L"\"", L"?"
        };
        return boost::make_iterator_range(patterns);
    }
    static boost::iterator_range< const wchar_t* const* > get_replacements()
    {
        static const wchar_t* const replacements[] =
        {
            L"\\\\", L"\\a", L"\\b", L"\\f", L"\\n", L"\\r", L"\\t", L"\\v", L"\\'", L"\\\"", L"\\?"
        };
        return boost::make_iterator_range(replacements);
    }
    template< unsigned int N >
    static std::size_t print_escaped(wchar_t (&buf)[N], wchar_t c)
    {
        const wchar_t* format;
        unsigned int val;
        if (sizeof(wchar_t) == 1)
        {
            format = L"\\x%.2X";
            val = static_cast< uint8_t >(c);
        }
        else if (sizeof(wchar_t) == 2)
        {
            format = L"\\x%.4X";
            val = static_cast< uint16_t >(c);
        }
        else
        {
            format = L"\\x%.8X";
            val = static_cast< uint32_t >(c);
        }

        int n = boost::log::aux::swprintf(buf, N, format, val);
        if (n < 0)
        {
            n = 0;
            buf[0] = L'\0';
        }
        return static_cast< unsigned int >(n) >= N ? N - 1 : static_cast< unsigned int >(n);
    }
};
#endif // BOOST_LOG_USE_WCHAR_T

template< typename CharT >
struct c_decorator_gen
{
    typedef CharT char_type;

    template< typename SubactorT >
    BOOST_FORCEINLINE char_decorator_actor< SubactorT, pattern_replacer< char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef c_decorator_traits< char_type > traits_type;
        typedef pattern_replacer< char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type(traits_type::get_patterns(), traits_type::get_replacements())) }};
        return result_type(act);
    }
};

} // namespace aux

/*!
 * C-style decorator generator object. The decorator replaces characters with specific meaning in C
 * language with the corresponding escape sequences. The generator provides <tt>operator[]</tt> that
 * can be used to construct the actual decorator. For example:
 *
 * <code>
 * c_decor[ stream << attr< std::string >("MyAttr") ]
 * </code>
 *
 * For wide-character formatting there is the similar \c wc_decor decorator generator object.
 */
#ifdef BOOST_LOG_USE_CHAR
const aux::c_decorator_gen< char > c_decor = {};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
const aux::c_decorator_gen< wchar_t > wc_decor = {};
#endif

/*!
 * The function creates a C-style decorator generator for arbitrary character type.
 */
template< typename CharT >
BOOST_FORCEINLINE aux::c_decorator_gen< CharT > make_c_decor()
{
    return aux::c_decorator_gen< CharT >();
}

/*!
 * A character decorator implementation that escapes all non-prontable and non-ASCII characters
 * in the output with C-style escape sequences.
 */
template< typename CharT >
class c_ascii_pattern_replacer :
    public pattern_replacer< CharT >
{
private:
    //! Base type
    typedef pattern_replacer< CharT > base_type;

public:
    //! Result type
    typedef typename base_type::result_type result_type;
    //! Character type
    typedef typename base_type::char_type char_type;
    //! String type
    typedef typename base_type::string_type string_type;

private:
    //! Traits type
    typedef aux::c_decorator_traits< char_type > traits_type;

public:
    //! Default constructor
    c_ascii_pattern_replacer() : base_type(traits_type::get_patterns(), traits_type::get_replacements())
    {
    }

    //! Applies string replacements starting from the specified position
    result_type operator() (string_type& str, typename string_type::size_type start_pos = 0) const
    {
        base_type::operator() (str, start_pos);

        typedef typename string_type::iterator string_iterator;
        for (string_iterator it = str.begin() + start_pos, end = str.end(); it != end; ++it)
        {
            char_type c = *it;
            if (c < 0x20 || c > 0x7e)
            {
                char_type buf[(std::numeric_limits< char_type >::digits + 3) / 4 + 3];
                std::size_t n = traits_type::print_escaped(buf, c);
                std::size_t pos = it - str.begin();
                str.replace(pos, 1, buf, n);
                it = str.begin() + n - 1;
                end = str.end();
            }
        }
    }
};

namespace aux {

template< typename CharT >
struct c_ascii_decorator_gen
{
    typedef CharT char_type;

    template< typename SubactorT >
    BOOST_FORCEINLINE char_decorator_actor< SubactorT, c_ascii_pattern_replacer< char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef c_ascii_pattern_replacer< char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type()) }};
        return result_type(act);
    }
};

} // namespace aux

/*!
 * C-style decorator generator object. Acts similarly to \c c_decor, except that \c c_ascii_decor also
 * converts all non-ASCII and non-printable ASCII characters, except for space character, into
 * C-style hexadecimal escape sequences. The generator provides <tt>operator[]</tt> that
 * can be used to construct the actual decorator. For example:
 *
 * <code>
 * c_ascii_decor[ stream << attr< std::string >("MyAttr") ]
 * </code>
 *
 * For wide-character formatting there is the similar \c wc_ascii_decor decorator generator object.
 */
#ifdef BOOST_LOG_USE_CHAR
const aux::c_ascii_decorator_gen< char > c_ascii_decor = {};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
const aux::c_ascii_decorator_gen< wchar_t > wc_ascii_decor = {};
#endif

/*!
 * The function creates a C-style decorator generator for arbitrary character type.
 */
template< typename CharT >
BOOST_FORCEINLINE aux::c_ascii_decorator_gen< CharT > make_c_ascii_decor()
{
    return aux::c_ascii_decorator_gen< CharT >();
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_C_DECORATOR_HPP_INCLUDED_

/* c_decorator.hpp
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
*/
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
BOOST_INLINE_VARIABLE const aux::c_decorator_gen< char > c_decor = {};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
BOOST_INLINE_VARIABLE const aux::c_decorator_gen< wchar_t > wc_decor = {};
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
BOOST_INLINE_VARIABLE const aux::c_ascii_decorator_gen< char > c_ascii_decor = {};
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
BOOST_INLINE_VARIABLE const aux::c_ascii_decorator_gen< wchar_t > wc_ascii_decor = {};
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
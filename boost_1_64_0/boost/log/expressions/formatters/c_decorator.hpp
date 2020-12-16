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
9w876bwFBtF3ZGh+0XOafuOAuLlaz4N+ypw847aaH0Krcx9j1mnWiZvXnW6evpBSXcrCV6XjSX+KxGeUk0Rpd+K/PG0nXeV6f65kmDrXmNt6nxM+jpf81nG81ikp20i7fVKGxvYBZcU1LSt1W2DGmeS9jo9eKA238fcnPb9Dz/v3CL8/IuJ8hp7zvPD1Eq3j2Zqw9jpm3SzuG3U5UMesdVVVgb0ZOt7UdjY5jjmP2GTR35TbWBS48Zg6+Cky0Z2zB57pndpJ3UoZ7HC9sn5ZrHl6D9vvdFrbFG5t80Brm8KtdR5obTfGrembG0hH6Pc4D8n9Lzjn8u/NiNuXbSXMfQQwxe3LUtJN3XtX+7Kgm1zy61zXTc5Vxs2+iLHPvZzfg2zwSCvjblN/3fwt1PyV+muZm2ZZ5qa50XNTU8a1xY4cVwftoyCLKOOtPb1lzCzIMn/P0/fkz8TtSqfBPk4nLHue52lfkt3LvT+Y8Wo7vUbOybVh+OntfceasepBCfNMRsu8I83Ypdb0Nc/L/fb0YUmefq9mPgvrxs0ucZOBi6TANc72ybXJzllOioyBNxXxrI76rk1l9Jsm/7azjoHVfXFx8P1YHvVuTKyvknyWfuHpnuH9SH6vwPnrReG/A1neyZHjPMSHTEc+U0DO9IooT2a1YetOEfPa5eJ+sq08NSyfjiXirssTotea9Jmk55peZl4ZVj8PdTJ76ow+2yz8Noenhx7P0fpl1tBMWt4St8fZ19TC08K4KPG0XGjWzcLjvl+NdvTzBfz2hRe56z69vXF3v6c4kesopp6Xi9tk3xtOO1v8CSv+PjXarcwBrX2quo2co9v6VNxaxxemfzhR7uf53uffIuOGdPMuZTTHBtNQXzBc3Ob43nFSItdcTLsdK278vtedVOmfaajOTewlmyr9c+MtUf2zumnGzTTXTcbV6d7+mefwfUvGeEu88+2H5Dld9ZyRRx+xUSph6ncm+b50j0pjRL/ew5kq4T5xn4+Ms343M8/6hjwrPY6xTEqHPeLWwRA3UyidU70YuMYF+7pY7PeFXtO6oO8Lzzxb7ddK+PJukfPX9Vzbq+l/yro5cjzu+tOxQw15sLGPt87LrFpeZBH1y1bH8Wut42Ys+nO5v95W5/Ebf533uiVdHPK+NGVU1FfscHFuxsMVDYtC87rt4v828xu2Uhzya7uhOeUj4uZey9xQ16vkGbwHg3VOzkcQ34FmLER70HiNlT3LSeJmTnAMxkHWevq/3fLMy5wB1Nl0J7T2cgZ93RiVsaXS90kdXofIPupW5vHETeucbX0m/jrn7TNvKnXk+AQpRfYiF7j1p6+3/tQtr4lePzR95s/EbS1vr0J7feprrU+mf9kq93fwDi2w16m+1jpl+rAfy/2XnJlOvr2e9bWu75j+8lm5/yT7QXNs/S3+Y8/niuGJ/dz7F0TWMfMN/Wnxv4jf9uxj+rYC8ZMqfn4iZSA1V56/z/N79NO5dx4SrCef1b9v89SbAnu9Oa2Dx65voeM7ojoj/VTEOhDXJK5u/As1/rI2pHVrRA9jx9Zwuvt9TtLeWL9kjiwVnHX2pHHTJ54ug4rId4OtPuE//NvSwTjs8wXT7oZdSNjme6nG9X5LXJfgdr81rvI7+jXLq6tDc5M44uDNm2k9o583lec5/e3PW7400P6mtJI3+A/Lm/1xxCuYN1NM3oTH1ekVHdfzcJtrj2vtslonrnLMjYhrVUH8cT01Rlz3WeK6FLfdY8R1ef2iuOIa8O/zjN9rG+rs61PGrRnzJFAG3nRp29SxO8+LqLMv9I5O61z8l4WnVZNayeamBrOnY3Qr6SWMsPVW5ivWtBp3Zu0y/rSO9qQ1O2w=
*/
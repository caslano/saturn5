/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_AS_PARSER_HPP)
#define BOOST_SPIRIT_AS_PARSER_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Helper templates to derive the parser type from an auxiliary type
    //  and to generate an object of the required parser type given an
    //  auxiliary object. Supported types to convert are parsers,
    //  single characters and character strings.
    //
    ///////////////////////////////////////////////////////////////////////////
    namespace impl
    {
        template<typename T>
        struct default_as_parser
        {
            typedef T type;
            static type const& convert(type const& p)
            {
                return p;
            }
        };

        struct char_as_parser
        {
            typedef chlit<char> type;
            static type convert(char ch)
            {
                return type(ch);
            }
        };

        struct wchar_as_parser
        {
            typedef chlit<wchar_t> type;
            static type convert(wchar_t ch)
            {
                return type(ch);
            }
        };

        struct string_as_parser
        {
            typedef strlit<char const*> type;
            static type convert(char const* str)
            {
                return type(str);
            }
        };

        struct wstring_as_parser
        {
            typedef strlit<wchar_t const*> type;
            static type convert(wchar_t const* str)
            {
                return type(str);
            }
        };
    }

    template<typename T>
    struct as_parser : impl::default_as_parser<T> {};

    template<>
    struct as_parser<char> : impl::char_as_parser {};

    template<>
    struct as_parser<wchar_t> : impl::wchar_as_parser {};

    template<>
    struct as_parser<char*> : impl::string_as_parser {};

    template<>
    struct as_parser<char const*> : impl::string_as_parser {};

    template<>
    struct as_parser<wchar_t*> : impl::wstring_as_parser {};

    template<>
    struct as_parser<wchar_t const*> : impl::wstring_as_parser {};

    template<int N>
    struct as_parser<char[N]> : impl::string_as_parser {};

    template<int N>
    struct as_parser<wchar_t[N]> : impl::wstring_as_parser {};

    template<int N>
    struct as_parser<char const[N]> : impl::string_as_parser {};

    template<int N>
    struct as_parser<wchar_t const[N]> : impl::wstring_as_parser {};

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* as_parser.hpp
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
*/
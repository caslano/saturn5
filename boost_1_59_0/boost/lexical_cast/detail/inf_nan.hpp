// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2022.
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

#ifndef BOOST_LEXICAL_CAST_DETAIL_INF_NAN_HPP
#define BOOST_LEXICAL_CAST_DETAIL_INF_NAN_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

#include <boost/limits.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/core/cmath.hpp>
#include <cstddef>
#include <cstring>

#include <boost/lexical_cast/detail/lcast_char_constants.hpp>

namespace boost {
    namespace detail
    {
        template <class CharT>
        bool lc_iequal(const CharT* val, const CharT* lcase, const CharT* ucase, unsigned int len) BOOST_NOEXCEPT {
            for( unsigned int i=0; i < len; ++i ) {
                if ( val[i] != lcase[i] && val[i] != ucase[i] ) return false;
            }

            return true;
        }

        /* Returns true and sets the correct value if found NaN or Inf. */
        template <class CharT, class T>
        inline bool parse_inf_nan_impl(const CharT* begin, const CharT* end, T& value
            , const CharT* lc_NAN, const CharT* lc_nan
            , const CharT* lc_INFINITY, const CharT* lc_infinity
            , const CharT opening_brace, const CharT closing_brace) BOOST_NOEXCEPT
        {
            if (begin == end) return false;
            const CharT minus = lcast_char_constants<CharT>::minus;
            const CharT plus = lcast_char_constants<CharT>::plus;
            const int inifinity_size = 8; // == sizeof("infinity") - 1

            /* Parsing +/- */
            bool const has_minus = (*begin == minus);
            if (has_minus || *begin == plus) {
                ++ begin;
            }

            if (end - begin < 3) return false;
            if (lc_iequal(begin, lc_nan, lc_NAN, 3)) {
                begin += 3;
                if (end != begin) {
                    /* It is 'nan(...)' or some bad input*/

                    if (end - begin < 2) return false; // bad input
                    -- end;
                    if (*begin != opening_brace || *end != closing_brace) return false; // bad input
                }

                if( !has_minus ) value = std::numeric_limits<T>::quiet_NaN();
                else value = boost::core::copysign(std::numeric_limits<T>::quiet_NaN(), static_cast<T>(-1));
                return true;
            } else if (
                ( /* 'INF' or 'inf' */
                  end - begin == 3      // 3 == sizeof('inf') - 1
                  && lc_iequal(begin, lc_infinity, lc_INFINITY, 3)
                )
                ||
                ( /* 'INFINITY' or 'infinity' */
                  end - begin == inifinity_size
                  && lc_iequal(begin, lc_infinity, lc_INFINITY, inifinity_size)
                )
             )
            {
                if( !has_minus ) value = std::numeric_limits<T>::infinity();
                else value = -std::numeric_limits<T>::infinity();
                return true;
            }

            return false;
        }

        template <class CharT, class T>
        bool put_inf_nan_impl(CharT* begin, CharT*& end, const T& value
                         , const CharT* lc_nan
                         , const CharT* lc_infinity) BOOST_NOEXCEPT
        {
            const CharT minus = lcast_char_constants<CharT>::minus;
            if (boost::core::isnan(value)) {
                if (boost::core::signbit(value)) {
                    *begin = minus;
                    ++ begin;
                }

                std::memcpy(begin, lc_nan, 3 * sizeof(CharT));
                end = begin + 3;
                return true;
            } else if (boost::core::isinf(value)) {
                if (boost::core::signbit(value)) {
                    *begin = minus;
                    ++ begin;
                }

                std::memcpy(begin, lc_infinity, 3 * sizeof(CharT));
                end = begin + 3;
                return true;
            }

            return false;
        }


#ifndef BOOST_LCAST_NO_WCHAR_T
        template <class T>
        bool parse_inf_nan(const wchar_t* begin, const wchar_t* end, T& value) BOOST_NOEXCEPT {
            return parse_inf_nan_impl(begin, end, value
                               , L"NAN", L"nan"
                               , L"INFINITY", L"infinity"
                               , L'(', L')');
        }

        template <class T>
        bool put_inf_nan(wchar_t* begin, wchar_t*& end, const T& value) BOOST_NOEXCEPT {
            return put_inf_nan_impl(begin, end, value, L"nan", L"infinity");
        }

#endif
#if !defined(BOOST_NO_CXX11_CHAR16_T) && !defined(BOOST_NO_CXX11_UNICODE_LITERALS)
        template <class T>
        bool parse_inf_nan(const char16_t* begin, const char16_t* end, T& value) BOOST_NOEXCEPT {
            return parse_inf_nan_impl(begin, end, value
                               , u"NAN", u"nan"
                               , u"INFINITY", u"infinity"
                               , u'(', u')');
        }

        template <class T>
        bool put_inf_nan(char16_t* begin, char16_t*& end, const T& value) BOOST_NOEXCEPT {
            return put_inf_nan_impl(begin, end, value, u"nan", u"infinity");
        }
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T) && !defined(BOOST_NO_CXX11_UNICODE_LITERALS)
        template <class T>
        bool parse_inf_nan(const char32_t* begin, const char32_t* end, T& value) BOOST_NOEXCEPT {
            return parse_inf_nan_impl(begin, end, value
                               , U"NAN", U"nan"
                               , U"INFINITY", U"infinity"
                               , U'(', U')');
        }

        template <class T>
        bool put_inf_nan(char32_t* begin, char32_t*& end, const T& value) BOOST_NOEXCEPT {
            return put_inf_nan_impl(begin, end, value, U"nan", U"infinity");
        }
#endif

        template <class CharT, class T>
        bool parse_inf_nan(const CharT* begin, const CharT* end, T& value) BOOST_NOEXCEPT {
            return parse_inf_nan_impl(begin, end, value
                               , "NAN", "nan"
                               , "INFINITY", "infinity"
                               , '(', ')');
        }

        template <class CharT, class T>
        bool put_inf_nan(CharT* begin, CharT*& end, const T& value) BOOST_NOEXCEPT {
            return put_inf_nan_impl(begin, end, value, "nan", "infinity");
        }
    }
} // namespace boost

#undef BOOST_LCAST_NO_WCHAR_T

#endif // BOOST_LEXICAL_CAST_DETAIL_INF_NAN_HPP


/* inf_nan.hpp
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
*/
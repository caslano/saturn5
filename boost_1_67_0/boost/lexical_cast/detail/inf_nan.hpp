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

#ifndef BOOST_LEXICAL_CAST_DETAIL_INF_NAN_HPP
#define BOOST_LEXICAL_CAST_DETAIL_INF_NAN_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

#include <cstddef>
#include <cstring>
#include <boost/limits.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

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
            using namespace std;
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
                else value = (boost::math::changesign) (std::numeric_limits<T>::quiet_NaN());
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
                else value = (boost::math::changesign) (std::numeric_limits<T>::infinity());
                return true;
            }

            return false;
        }

        template <class CharT, class T>
        bool put_inf_nan_impl(CharT* begin, CharT*& end, const T& value
                         , const CharT* lc_nan
                         , const CharT* lc_infinity) BOOST_NOEXCEPT
        {
            using namespace std;
            const CharT minus = lcast_char_constants<CharT>::minus;
            if ((boost::math::isnan)(value)) {
                if ((boost::math::signbit)(value)) {
                    *begin = minus;
                    ++ begin;
                }

                memcpy(begin, lc_nan, 3 * sizeof(CharT));
                end = begin + 3;
                return true;
            } else if ((boost::math::isinf)(value)) {
                if ((boost::math::signbit)(value)) {
                    *begin = minus;
                    ++ begin;
                }

                memcpy(begin, lc_infinity, 3 * sizeof(CharT));
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
+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
*/
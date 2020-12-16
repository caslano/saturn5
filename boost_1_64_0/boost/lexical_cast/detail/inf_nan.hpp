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
0098y8QpB/Vp9PXBuSZe91ujzSHUqVHPJvOApKXvGp6rSxvrPM9xi7TSVhifOGePTzmfZKflkCCNZKeuj+MKaaWdJlg02H5MK/y0eBxHHut+7+aFee5FdXI6zi8wz8E5o4cPOsgwDxvmXdIwzrumORXpjXOqac5E2obNmfMW+D9nMq1prjPNjUhvmuvM86KdFv07CPEL0Qp7EuvX9/4d/dHU75Lc+p3el97gnmyTHbVtlAfsizljq96X5vRAdxqaA6qFc6aCLvtSrPiUlanF9ll1wwVWvmKVqVqY+hfpOtz7otn3kte+aO5fOu3housXB+GGvsW09NHVT9JONvQrnSafxXgOGfsU07qtS8zCQoixT9l14/3RAoUl09CSmk+yWcLLLKSPEZoDUmU+zp+ilIs/sbJ0eX5MKuhR9zx6W+gPcnRVwWoOwmaEGEewx94zbfkcflHSj3L0VdC/IWxDSHbAk5gaJ8/yZzA376T/sGfxewAK+HSia7wCCUdr587F7/PsuBXq9z1mrZHELvRcI7H6Wpzd1zCGDOMqwjSuOIas/hDH/hDJ8QO+WzSRRpvL2b4x+jzOdsQ54TnaAefQDtw3p1lteRXOu+5By9mhdRB9swOtsTVvocvY4lRtDy/3sWU/m2+VfJ87nM/j1RKf7zDO4wuN40xobQStO+T6xw7nu+4KiXc0z/ELGzYOkd44DiM5R9wk1093GOf8hf6Ny3kL/R+X8xb6Py7d64pxVTrF2sZIG5dLLrTStFH74S/Sfv9C82nvXvF2fmszv5yZ+aSB6yJr2OOQ87ezHTpfRD+EuH5KOse75gP6Zinfhw67fNpzwdkvUoTGCMYxG0u8rfvYt99vNwvNXY5aXrLOYGcMrlfh+r1S33dQ43g+L533VXabtpd7jGQc92Q9YuhfWWnPpEi+h17H/jxOjRP+P8e9dueD4DrMJc9zznGemx4tv/W5R+acxbHyG9fluSzzzu2IV3O+Gevn+6M19xRf9M+de+x3Rfa11ipa+pKkc+1n9lrw6iBva69/3xpxQ32jeVsjPl3WiE98qeu2J+7ueXXB9tR1v1fOvOC/uxY8XOo77J5nfw8bWPLYWaGPp315/T27/xtrxBUO6hSoW9rBPdvnO+jzg77eutB3S1fagKcDx9K3wnj6HskF9gQW0AdJIbA3fYUdAryQvkiuAfYDrgX2B95CH2v3AwcCt9FHyTPAw4DbgZnAnUz3KXAwUDlQZmAT4AhgGPBoYEfgKOAA4PHAhcCTgIuB44FXAScA7wROBD4GzAf+ACwEKvBxOrAlcAawD+OzGL+U8esY3wi06D0HnGmVF1gM/A54MvBnYCkwBPw9A9gcaNUjCZgNbA88BpjK8/SRQflHeK52uPnIOJdr9+fRN9X5zLeH77j0KyX5khA+Z75V9Gl1PX20rKFvhxvoE+4x+oR7nO39BHAkcB19v20AXsh0S5juCqZbTl8RtwPvAd4F3AR8lulfYfrXmf5N4P3AH+k7IsKBsgMPBFrp04FW+h5AK31P4CPAMbw+gdfz5Dr55uC7BN//dkgfBt/Yn59R9MEE7AR8kTYP24HD6EsiH/gq++9rwHL6MqkAvgW8lr5JbqBvkq3Ad4GP0WdiNX0ivg/8FPg78DNgiKPWx1s48CtgAvBrYBLwW9ZvN3AU8DvWcw9wOvBH4CzgT8Ay4M/A2cDfgGcAfweuAOIe81YBmwBvBoYCnwU2A34FjAD+BGwOtPp5C2D2X2TTkb859C+x65i/OTRg24HfazaHNqp9x5bNoX/KxqPygv3+lJ1H9ebQf5StR83m0D9t7xFyX6hKQTgKoeS+gO1H4Agcf7B3JWBRVVH4zoDhlhE=
*/
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

#ifndef BOOST_LEXICAL_CAST_DETAIL_LCAST_UNSIGNED_CONVERTERS_HPP
#define BOOST_LEXICAL_CAST_DETAIL_LCAST_UNSIGNED_CONVERTERS_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <climits>
#include <cstddef>
#include <string>
#include <cstring>
#include <cstdio>
#include <boost/limits.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/workaround.hpp>


#ifndef BOOST_NO_STD_LOCALE
#   include <locale>
#else
#   ifndef BOOST_LEXICAL_CAST_ASSUME_C_LOCALE
        // Getting error at this point means, that your STL library is old/lame/misconfigured.
        // If nothing can be done with STL library, define BOOST_LEXICAL_CAST_ASSUME_C_LOCALE,
        // but beware: lexical_cast will understand only 'C' locale delimeters and thousands
        // separators.
#       error "Unable to use <locale> header. Define BOOST_LEXICAL_CAST_ASSUME_C_LOCALE to force "
#       error "boost::lexical_cast to use only 'C' locale during conversions."
#   endif
#endif

#include <boost/lexical_cast/detail/lcast_char_constants.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/noncopyable.hpp>

namespace boost
{
    namespace detail // lcast_to_unsigned
    {
        template<class T>
        inline
        BOOST_DEDUCED_TYPENAME boost::make_unsigned<T>::type lcast_to_unsigned(const T value) BOOST_NOEXCEPT {
            typedef BOOST_DEDUCED_TYPENAME boost::make_unsigned<T>::type result_type;
            return value < 0
                ? static_cast<result_type>(0u - static_cast<result_type>(value))
                : static_cast<result_type>(value);
        }
    }

    namespace detail // lcast_put_unsigned
    {
        template <class Traits, class T, class CharT>
        class lcast_put_unsigned: boost::noncopyable {
            typedef BOOST_DEDUCED_TYPENAME Traits::int_type int_type;
            BOOST_DEDUCED_TYPENAME boost::conditional<
                    (sizeof(unsigned) > sizeof(T))
                    , unsigned
                    , T
            >::type         m_value;
            CharT*          m_finish;
            CharT    const  m_czero;
            int_type const  m_zero;

        public:
            lcast_put_unsigned(const T n_param, CharT* finish) BOOST_NOEXCEPT
                : m_value(n_param), m_finish(finish)
                , m_czero(lcast_char_constants<CharT>::zero), m_zero(Traits::to_int_type(m_czero))
            {
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
                BOOST_STATIC_ASSERT(!std::numeric_limits<T>::is_signed);
#endif
            }

            CharT* convert() {
#ifndef BOOST_LEXICAL_CAST_ASSUME_C_LOCALE
                std::locale loc;
                if (loc == std::locale::classic()) {
                    return main_convert_loop();
                }

                typedef std::numpunct<CharT> numpunct;
                numpunct const& np = BOOST_USE_FACET(numpunct, loc);
                std::string const grouping = np.grouping();
                std::string::size_type const grouping_size = grouping.size();

                if (!grouping_size || grouping[0] <= 0) {
                    return main_convert_loop();
                }

#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
                // Check that ulimited group is unreachable:
                BOOST_STATIC_ASSERT(std::numeric_limits<T>::digits10 < CHAR_MAX);
#endif
                CharT const thousands_sep = np.thousands_sep();
                std::string::size_type group = 0; // current group number
                char last_grp_size = grouping[0];
                char left = last_grp_size;

                do {
                    if (left == 0) {
                        ++group;
                        if (group < grouping_size) {
                            char const grp_size = grouping[group];
                            last_grp_size = (grp_size <= 0 ? static_cast<char>(CHAR_MAX) : grp_size);
                        }

                        left = last_grp_size;
                        --m_finish;
                        Traits::assign(*m_finish, thousands_sep);
                    }

                    --left;
                } while (main_convert_iteration());

                return m_finish;
#else
                return main_convert_loop();
#endif
            }

        private:
            inline bool main_convert_iteration() BOOST_NOEXCEPT {
                --m_finish;
                int_type const digit = static_cast<int_type>(m_value % 10U);
                Traits::assign(*m_finish, Traits::to_char_type(m_zero + digit));
                m_value /= 10;
                return !!m_value; // suppressing warnings
            }

            inline CharT* main_convert_loop() BOOST_NOEXCEPT {
                while (main_convert_iteration());
                return m_finish;
            }
        };
    }

    namespace detail // lcast_ret_unsigned
    {
        template <class Traits, class T, class CharT>
        class lcast_ret_unsigned: boost::noncopyable {
            bool m_multiplier_overflowed;
            T m_multiplier;
            T& m_value;
            const CharT* const m_begin;
            const CharT* m_end;

        public:
            lcast_ret_unsigned(T& value, const CharT* const begin, const CharT* end) BOOST_NOEXCEPT
                : m_multiplier_overflowed(false), m_multiplier(1), m_value(value), m_begin(begin), m_end(end)
            {
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
                BOOST_STATIC_ASSERT(!std::numeric_limits<T>::is_signed);

                // GCC when used with flag -std=c++0x may not have std::numeric_limits
                // specializations for __int128 and unsigned __int128 types.
                // Try compilation with -std=gnu++0x or -std=gnu++11.
                //
                // http://gcc.gnu.org/bugzilla/show_bug.cgi?id=40856
                BOOST_STATIC_ASSERT_MSG(std::numeric_limits<T>::is_specialized,
                    "std::numeric_limits are not specialized for integral type passed to boost::lexical_cast"
                );
#endif
            }

            inline bool convert() {
                CharT const czero = lcast_char_constants<CharT>::zero;
                --m_end;
                m_value = static_cast<T>(0);

                if (m_begin > m_end || *m_end < czero || *m_end >= czero + 10)
                    return false;
                m_value = static_cast<T>(*m_end - czero);
                --m_end;

#ifdef BOOST_LEXICAL_CAST_ASSUME_C_LOCALE
                return main_convert_loop();
#else
                std::locale loc;
                if (loc == std::locale::classic()) {
                    return main_convert_loop();
                }

                typedef std::numpunct<CharT> numpunct;
                numpunct const& np = BOOST_USE_FACET(numpunct, loc);
                std::string const& grouping = np.grouping();
                std::string::size_type const grouping_size = grouping.size();

                /* According to Programming languages - C++
                 * we MUST check for correct grouping
                 */
                if (!grouping_size || grouping[0] <= 0) {
                    return main_convert_loop();
                }

                unsigned char current_grouping = 0;
                CharT const thousands_sep = np.thousands_sep();
                char remained = static_cast<char>(grouping[current_grouping] - 1);

                for (;m_end >= m_begin; --m_end)
                {
                    if (remained) {
                        if (!main_convert_iteration()) {
                            return false;
                        }
                        --remained;
                    } else {
                        if ( !Traits::eq(*m_end, thousands_sep) ) //|| begin == end ) return false;
                        {
                            /*
                             * According to Programming languages - C++
                             * Digit grouping is checked. That is, the positions of discarded
                             * separators is examined for consistency with
                             * use_facet<numpunct<charT> >(loc ).grouping()
                             *
                             * BUT what if there is no separators at all and grouping()
                             * is not empty? Well, we have no extraced separators, so we
                             * won`t check them for consistency. This will allow us to
                             * work with "C" locale from other locales
                             */
                            return main_convert_loop();
                        } else {
                            if (m_begin == m_end) return false;
                            if (current_grouping < grouping_size - 1) ++current_grouping;
                            remained = grouping[current_grouping];
                        }
                    }
                } /*for*/

                return true;
#endif
            }

        private:
            // Iteration that does not care about grouping/separators and assumes that all
            // input characters are digits
            inline bool main_convert_iteration() BOOST_NOEXCEPT {
                CharT const czero = lcast_char_constants<CharT>::zero;
                T const maxv = (std::numeric_limits<T>::max)();

                m_multiplier_overflowed = m_multiplier_overflowed || (maxv/10 < m_multiplier);
                m_multiplier = static_cast<T>(m_multiplier * 10);

                T const dig_value = static_cast<T>(*m_end - czero);
                T const new_sub_value = static_cast<T>(m_multiplier * dig_value);

                // We must correctly handle situations like `000000000000000000000000000001`.
                // So we take care of overflow only if `dig_value` is not '0'.
                if (*m_end < czero || *m_end >= czero + 10  // checking for correct digit
                    || (dig_value && (                      // checking for overflow of ...
                        m_multiplier_overflowed                             // ... multiplier
                        || static_cast<T>(maxv / dig_value) < m_multiplier  // ... subvalue
                        || static_cast<T>(maxv - new_sub_value) < m_value   // ... whole expression
                    ))
                ) return false;

                m_value = static_cast<T>(m_value + new_sub_value);

                return true;
            }

            bool main_convert_loop() BOOST_NOEXCEPT {
                for ( ; m_end >= m_begin; --m_end) {
                    if (!main_convert_iteration()) {
                        return false;
                    }
                }

                return true;
            }
        };
    }
} // namespace boost

#endif // BOOST_LEXICAL_CAST_DETAIL_LCAST_UNSIGNED_CONVERTERS_HPP


/* lcast_unsigned_converters.hpp
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
*/
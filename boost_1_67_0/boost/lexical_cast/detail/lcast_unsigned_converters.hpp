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
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
4F6SqMOCCgZgTPM03/2JQKws4kGyPZ8bD+S5+Mzqvpesq/i9++Z7c3VxiFmX37fBtTlFtbHAWU/NEYoN75o486pMPD+Gjr624DcaCl/CeHFOjpf4Ev3YOa5O3NuP/uNcLmO/M+8n+6nuQaqmr/sAl7TlRSz4shTcu8B7dFJucd6M+eO12KmSZ+Ts2vG63sbc9o0+pjtlqzkA8BwrcauvkNe/Fd04ry0yjiEtCT0fBbpUnKi915TLGML15+AEzg+XyDov4hk9AX57cbrngHL0826NvNZdzrv+/t05T51jj8O8vrd2Tltjc06LY5+fl/LvQ48niV54jvYQ+vnnQT5bk5ow79TPJwv9qXOOaDjnrLE459wsxwCfOc4ZPyjH6pyxuL1+zqgs1T6PE63i3JWl1ueMylLrc0ZlqbU5o7LU+pxRWdo65wz//ov0PYUsh7iEvIcH48+VuI81pdxfwJfJrDztnG7mHPhV1k939cbfhaCnQb1d8rcaY6E8NBsvxtbfp6a/l2bsmD/ny/cM/b41/b0135d6ybadXCdixEvxaT+LGO19r7F432ts3HfWVWIUQYn6GPWsq8adz8n1x53vRP2NkmPZIQbjOWqH4zu6ohZIjYH+AJ6th0FTE42YNtb3TjXXcxan5iXh+BPkZ/KcOk7MI5fJMQpxNeeVp5Rj/1rL2p241tLc+y++kmswdyQsnZWau3/U0Ltf/3Tvf4fdGrk1mNa21tLaYpq3xBpMtou2IO3oTeCDQFNcdX7jg+gvPtQ4D54OfiL9+08Cn8R9FKeBn8xY0VPB5/L8ReCnMlb0aYyJfQb4veBnMjZ2NvgTrP8S+Fngr9Cv/i3wPMaOPht8C/3pd4Dng++JvhaA7wVeCN4N3MtY2cXgqeAl4OPB54KfAj4PPA98Pngh+LmMib6QMWcWg18NXs6YM+eA38fjteALwJ9i/Q3gZUa/wReBV4FfCP4N63Mtie/reP/QxC4/gmtJ48F7gR/Jdmv974x8j97E+Xwl2y3h/oCl4P24L2Ac+A2M3X0j+HHgNzEm0M3gs8BvAT8b/FbGML8N/ArwO4zxc5/L3dzncg/3uawFX877ci/4m+ArwLeB38/YP/eBu1zymOPmO0eQcR/NcU/iuI9hu65oUMN2h3DcyUrMx3jjc7hm1wE8ke27Mnb7oeD7co1uMNfm0rnf5RiuEU5jLP9c8H6MkdQffDHbX8R9LZeBD+ZzO4R6GQa+ijGVnuH+lkq2ex58OGP2jwB/h2uYn4OPpL7SGRvpQD63B4F3AR8DngR+sIzZz3GAHwJ+MI99Fvdn2F1b3FmxyZ01xtBxy7c9G9Pq1xqDxS2PfXLXXHMUzyF2OWgCyANa9pyz7ugUpzjFKU5xilN2j9Iy6/+zpg03Vv+bGP8vgXsAKv5xA3+D0JHDR2ADgHm+yn9+uHFWmOfFvzw/YkSaWj/VPD9ylHo+239+/3SjvvQ72AJDMoXrCOcF2V+QafodyBE3iqvLuDqU+W4QmdmKTDkAi/sV/HKHuvVyvYpcqQCbchcHkVumyoUC7fb3kyBylyly5Y23KJd7Gsy4dke5anGI4eCz+0NukZQ73VfsCVxLMNflHpZ1DgA2H6tb/6EMFVufjqdGs/6jrZsvI6dr1gFYV4mDhLpC1K0nPCav93C1xVpoD9AvIN06gSrnJwm8yMfT9O34Tl7/WjyJM3HGZxkNEbs9R4mzX8l1xOgEf3tc5LWtuCbXAbjPoXNiLXUBxfF/Pz3C+PQZys2CXsJaR5SYPXXNNQGekzo1Y9FDd/IcfRzkWIwxxnOMPC/HgfHhPMcXsO8keg/93h9vkf29P94i63t/WFfdSwLdNv7829n74x8=
*/
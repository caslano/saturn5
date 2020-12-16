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

#ifndef BOOST_LEXICAL_CAST_LEXICAL_CAST_OLD_HPP
#define BOOST_LEXICAL_CAST_LEXICAL_CAST_OLD_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

#include <climits>
#include <cstddef>
#include <string>
#include <cstring>
#include <cstdio>
#include <boost/limits.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/lcast_precision.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_NO_STRINGSTREAM
#include <strstream>
#else
#include <sstream>
#endif

#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include <boost/lexical_cast/detail/widest_char.hpp>

namespace boost {
    namespace detail
    {

        // selectors for choosing stream character type
        template<typename Type>
        struct stream_char
        {
            typedef char type;
        };

#ifndef BOOST_LCAST_NO_WCHAR_T
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
        template<>
        struct stream_char<wchar_t>
        {
            typedef wchar_t type;
        };
#endif

        template<>
        struct stream_char<wchar_t *>
        {
            typedef wchar_t type;
        };

        template<>
        struct stream_char<const wchar_t *>
        {
            typedef wchar_t type;
        };

        template<>
        struct stream_char<std::wstring>
        {
            typedef wchar_t type;
        };
#endif

        // stream wrapper for handling lexical conversions
        template<typename Target, typename Source, typename Traits>
        class lexical_stream
        {
        private:
            typedef typename widest_char<
                typename stream_char<Target>::type,
                typename stream_char<Source>::type>::type char_type;

            typedef Traits traits_type;

        public:
            lexical_stream(char_type* = 0, char_type* = 0)
            {
                stream.unsetf(std::ios::skipws);
                lcast_set_precision(stream, static_cast<Source*>(0), static_cast<Target*>(0) );
            }
            ~lexical_stream()
            {
                #if defined(BOOST_NO_STRINGSTREAM)
                stream.freeze(false);
                #endif
            }
            bool operator<<(const Source &input)
            {
                return !(stream << input).fail();
            }
            template<typename InputStreamable>
            bool operator>>(InputStreamable &output)
            {
                return !is_pointer<InputStreamable>::value &&
                       stream >> output &&
                       stream.get() == traits_type::eof();
            }

            bool operator>>(std::string &output)
            {
                #if defined(BOOST_NO_STRINGSTREAM)
                stream << '\0';
                #endif
                stream.str().swap(output);
                return true;
            }
            #ifndef BOOST_LCAST_NO_WCHAR_T
            bool operator>>(std::wstring &output)
            {
                stream.str().swap(output);
                return true;
            }
            #endif

        private:
            #if defined(BOOST_NO_STRINGSTREAM)
            std::strstream stream;
            #elif defined(BOOST_NO_STD_LOCALE)
            std::stringstream stream;
            #else
            std::basic_stringstream<char_type,traits_type> stream;
            #endif
        };
    }

    // call-by-value fallback version (deprecated)

    template<typename Target, typename Source>
    Target lexical_cast(Source arg)
    {
        typedef typename detail::widest_char< 
            BOOST_DEDUCED_TYPENAME detail::stream_char<Target>::type 
          , BOOST_DEDUCED_TYPENAME detail::stream_char<Source>::type 
        >::type char_type; 

        typedef std::char_traits<char_type> traits;
        detail::lexical_stream<Target, Source, traits> interpreter;
        Target result;

        if(!(interpreter << arg && interpreter >> result))
            boost::conversion::detail::throw_bad_cast<Source, Target>();
        return result;
    }

} // namespace boost

#undef BOOST_LCAST_NO_WCHAR_T

#endif // BOOST_LEXICAL_CAST_LEXICAL_CAST_OLD_HPP


/* lexical_cast_old.hpp
2bED2BrhDU2/0BmYyP3I2wCPpT5hJrCtpkeYQz3CacD2wEupR1hKe9g11CNUUY+wkXqEJ4GpwBdpV/oK9Qm7aI/6oegV6CcV+D3tToNR3p7AdsDewExgH2AWsC/wKGB/q7zAgQG9Q0DvENA7NKreYXdA7xA4Akfg+I8c+0b+L8graiT5/3bd/x/3/+vGuqQhPJqKd7sr6+R/3NlF/o9N8rmnHPL67zdIT1tu+w0yruHbaTXZ2f6O+SG5lmT7WrgSC1kzWvnvawF18uWXx97jpZznUEaR2XqQj9X0+zbFWrMCHg3MxEtojSsfj8D33B48bE19xQGrauX/03C3HxAiHC2N/K3ReNYv2t6njGv3QKEzyMhvPe9PtfuWzVDaN+UpkvdARzn61BY10dgONe5tBhpF1ONUWToEoZFl602aSry57WPpV4n3xj3jeM6hdlnnxCtUF6M+pcajTxXO0XVHrSX/APue8RJvZ9unLJR4JtK3QsA5xK6Qcw6jrwLeT9/Ha/akGXW6oW6St7MjhverlvgQ9Im+tj6ns5w7wJEDaWaBulRJWruufey6Jmr3TpR7u+9BOUtu3prtO0ry/6IOB/+egr5tF3VuSRqdJBc61PNofgG3uOqgbD5tE9p56ihwoQvGUlOcu6NN7Vg6HwnubFMbnoyvPTcf5zZyD6VsP3UxPsYcUtn7w9ljzuqnceyn1LlwHKLf8VysPV7RL3gu0d7PTNgn55LsfZuEpzin62GEP7YuZmEj6mLMOhdvOouG61auFt3KBy3Gnrqg6O5rYzcnvdX90uvXN55u5d+iQzHrvLzrVsy6rX+mziXTfgbieW3YsyWT38oOBsbyW99EYBYwjd+2fsN8NaQzhd+0xyCsIp04fpvZCjiItiCHU4dzkpvu5hzqam6mzccG2nA8SF3NK9TN1AC7AFs6UHZgggPnaeORAewMtPL1B6YDD2M87T+ie9lXOhc3XUuj61m86Fj2iX5lX+pWGkuvsq90KlG3h6q02wN6lcAROPb1sU/kfyRvrPX/u/2Q/5NX2nLrKNy5QfJ/8kr/5f/klf7L/0xrlP8PWukq/0/Ey8v4fSj/14RwX37wMxHYFJiFF5lcVz6a5H/7e4FiSfuTSgflw8y+MEHPKPvba/Szreug0BGpTfzW839my/9mfttpyW/K+Ub53J0u5XOjbM20ut1FKVLbdbherj8K+TjEKB/nuvUvyrW23H2aXP8cQ2Q/cCLM1fcd08UDT5F0X6sDVbDqjVCXTrwSIj5YZNazJN0Xxn7XVt6jIxl3qFESj1Y90A/DKTtb/XB3yzrfhSvpu/AeXFuQWHv97XjPPdWjDHuqW/Rpw9BgOfozkxytPORoptPlaNo4sJ10+dgsX3qXw8zyVsPlxUN6OHA+Z5jju4FDjxy6dMXTx7zR8vqfvcmvDZfnzPKxN7m84XJqY9kqmOXmxtNbmOVm7/oMs35i38nH8ozg82yum3w8iPJxFuXjoZSPh1E+Hm7vVcs5hvP5XLe9ahO5N3ESsD33bk2lXDyQvrsOoy3D4ZSPj+b5bNoyTKR8XEZbhtmUj0+nr61KfiOxnLYMt9CW4TbaMDwEPBj4Er+9+Ip72wbTZqEp8NCA/ByQnwPys1/y83LIzhsD8nPgCByBo4HHPpH/iwonifjfCPL/vZr8H8v9/3ogOBAOQpgQh3+XuPolzyuT3VA8v5+nzLafpE/Du02ISW4lPVuWpNxq1gnoaYPt/czqfMS3l+sRRpmVeXFuZPRGRDeiUue3xLXoprZP882of5A6OtqHX/Mjbd2Awb47jHKTu3yFsupriDaPs+ljYQDfR/sjDE/E+6objyeh7XMK86XeByW6fo8=
*/
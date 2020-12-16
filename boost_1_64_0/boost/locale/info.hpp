//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_INFO_HPP_INCLUDED
#define BOOST_LOCALE_INFO_HPP_INCLUDED
#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <locale>
#include <string>


namespace boost {
    namespace locale {

        ///
        /// \brief a facet that holds general information about locale
        ///
        /// This facet should be always created in order to make all Boost.Locale functions work
        ///
        class BOOST_LOCALE_DECL info : public std::locale::facet
        {
        public:
            static std::locale::id id; ///< This member uniquely defines this facet, required by STL 

            ///
            /// String information about the locale
            ///
            enum string_propery {
                language_property,  ///< ISO 639 language id
                country_property,   ///< ISO 3166 country id
                variant_property,   ///< Variant for locale
                encoding_property,   ///< encoding name
                name_property       ///< locale name
            };

            ///
            /// Integer information about locale
            ///
            enum integer_property {
                utf8_property       ///< Non zero value if uses UTF-8 encoding
            };

          
            ///
            /// Standard facet's constructor
            /// 
            info(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            ///
            /// Get language name
            ///
            std::string language() const 
            {
                return get_string_property(language_property);
            }
            ///
            /// Get country name
            ///
            std::string country() const
            {
                return get_string_property(country_property);
            }
            ///
            /// Get locale variant
            ///
            std::string variant() const
            {
                return get_string_property(variant_property);
            }
            ///
            /// Get encoding
            ///
            std::string encoding() const
            {
                return get_string_property(encoding_property);
            }

            ///
            /// Get the name of the locale, like en_US.UTF-8
            ///
            std::string name() const
            {
                return get_string_property(name_property);
            }

            ///
            /// True if the underlying encoding is UTF-8 (for char streams and strings)
            ///
            bool utf8() const
            {
                return get_integer_property(utf8_property) != 0;
            }
            
#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
            std::locale::id& __get_id (void) const { return id; }
#endif
        protected:
            ///
            /// Get string property by its id \a v
            ///
            virtual std::string get_string_property(string_propery v) const = 0;
            ///
            /// Get integer property by its id \a v
            ///
            virtual int get_integer_property(integer_property v) const = 0;
        };

    }
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* info.hpp
jFJkDnba7Asc6KvsCzi5eLg34OQd7Gdj30DlLXLgBW/nfka6De9jrrzB2DO+zjTvseFr9FP5svK8THMHfz3v0FrerGjv+BbY8I1S+MqG5SFfp/6mYYIRdXgLonu5t7O1t+TL8q1fP144cJcMf71uH4K87PU33S/9b9XtS5DWXn/TPdJ/m26fgrT2Og8flP4bqIOJ4VESMcYEiw/f2+o8HB3p9vss6z5L5dT4V9R5eDPrs7wP65PtmjVqq+/wdhl+nq4+wcvz/TuGtdV3uFX6Z+rqj7T2+g5XS/8bjNWWvkPSIPd9jVkWL76vV9/hTdL/SmOxvb5DpnWBrb7DMT8xfYcD2SYOUZ6gjP3GUjghD2Mo37gQg2lR2xasb2ROb1u5L9B7Lu9SNyxlJBhPV+kfCbvepq4tgN5zOReGVeUFKDPgmf2Q1q71c0ryHuq3ubsF7bKzH5/PbzO5r1UPitpJe72TY/va6iIFL8+/TYa11TuZ3ddW7yRp7fVOXtLXVu8kafV6J9Ok3xhbvZPTpf90rd7JsWfh21PldvaDQDz/4T7cW3DdEM+Bnlb95uWUpmWUFMaliVaUllEIRZRL1O/O6o++kzSPGhO1smbkyfIf31bQsl2yjXwi/ffDBkh7bd2r9O2Uvk6EPUoZrlLWjfMb/UzS7MO5eQel7gosuayWvYT/XEiNhbE+UZPyXRDCCH6U7UnLzC8tqR1rcmQYjLkuNKWgyjJqZRhRUIoMY3fUf5CQaUD9348MXITyGwe3MtxRt2uAoi2EeyjnZffNo2zVb16WTTurn3WTRWQa1TOdya0dEQ6Bc9hE4ZlOjNUm9Gc6ynf4vgyboGsH4OPFGU+MF2c8MV6c8TCsm3yWxPGabzLAi2+ysec8TlnQkDaOiEYwwuFwH4Vh7O5nlf/CjLz8rLTSorSFOaXzRBi2fVE+RgT7swQZPtGQ0p9w3eE09QG+7NtQFqK+y0Mbno+z7TEP+S7p/5TpnyjSRRmVSDGfU9KPZCP5jnww/WxH+jGinGlUv/EwynlvkX59jTb424V5FN+IMz8dLH2i2mdi3fEzR/yWPJg/lzExoZ2D8BD1x77itGMXbeVPVR9r+418JMM/rMsvedmvP45I/z36fjK6/vXH29L/ad03RFp7/bGfSf8q6o91hj+EspkJ+dskixf96tUfa8hvcAdKO8l2/pojw4zW6o+doNEfO+FnoD/WOfZ+Cp7iWcbvZCnH3tjasbekgbHXqpdxkuYX+u9bP+7qZbxtxtgwp7y19B+GfASjvfip36M1j7pThglS/OZbfmukXwv0RVPaJiGCSpTBROTFv30zP//2LQe2jGkZ08wvpJWY8yvfrzaeuZJXf+t79zOmtpVn9hxjJ4FusrMtNGLuXDuOnp5z+NN93v6bUaYIP6lV+byw10YHZr45+/iT8Ud85+2NPW8/3fb0vlL6KfFN7ACmwfGcnXufGjt7PCc3eE4eyHNyyz5fPXQTSTeJdJMVumP10PUhXQ/S9VHojH6NowttJF1UI+nkHhlpdHQm6e5V6JKtfRnsV5GOepUtunaku46/K/j7ZoXPOjiD8ZeRT2u4FeSzjem+G9gB+AgwnPLPnYG/p1zEA8BEvh8EfAg4mL+HAO8DzuDvmcB7gMXA3wKX8r2l15r1vaCB8piv5KPSWpdhDUm6NnCrBBHlyiOByyl/UU455GuAw4ErKc9+LdO1iulaDVwu+LMc1wA3AdcCNwPXAx8FXg98ClgBfIvhKR/COT7WMUyXKh8yk/m5hOmZzXKbQ/pya16MeTjpW8GVkn4B66cA2By4ENiacvUi/4WstyJgZ76PABaz3i4H9uT7XpTPHyb4s1yWKHYyy5k=
*/
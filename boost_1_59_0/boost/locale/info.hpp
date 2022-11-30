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
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
*/
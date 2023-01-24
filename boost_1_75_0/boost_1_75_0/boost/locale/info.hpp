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
296vBzJ+rE7xYZdvs67jYZKR0yTVQ8TtJB6bYX5X72h+q54NT7VjZ4ApNuNFXPBo+nX9qbrqMz3A0rpAp+dGy92Ppigjl2wHtgZ1B4+NkT5HC2NHA+zadc1ryrxGUbW9/IJT039Yp6uop9X2tLw1UaurlYm/ZvJxEK4LB4utxhxdIeWXTtr5h9z6UsxobEt4gL7brAha/J7h2Fc6vEchPvboVnW1fdZmnGrL9c5IQiH+IibboFm7aMEAJT4bnEBhwt19l1/4SPFA509hZFdJGvgr3/9JNvpNTvDIvWYgGno98JLi+mXKOFrr2RpFrhV5Fptmlc5fm7I5xepkJ+dHtQ/5lcLuAvrPlfTeJ4fdBFDY3lMX5AyY/OQngfP+gpjJuBzaLXizw1w2cioO6MK8P4fPg64DrmhUtg1vol5WJLdtAAT71PdWUtthANT9gAeY1HbUyq9uLKcvPjBqWR/EVsz19jPVuN/1BAt0xKlwH0B6EPBUxQJd7Au6Ng4IZYLmQ8S7imrz75fHYxM8QLT0a5+8McRx+3AXLimdCR0HHI4j1BKrHRgAYv6Y4ird0pdpAH9CI4Nv26WHrsvR8UO1f+4I5wRfs+My+Uf9vHr1aOv3FOiLYIzJ9LrKeJmESasMJgOn1yv52wKilvGUBEAoRIcX9IpD7qJF2pZKzhE14gUXW66njhmpZXAHTOZHjol8WZp5agDLDsVSuqg/
*/
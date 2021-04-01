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
L7UegFA5YtDltAIdV/ScjRmZlFs7ReXbZvGO6HLZ1ZNz/WB2JyXsuI5Oa116vCOZz9+ZaD7Ush55y1SBtm9M+ropcVaOsBJwjpY+OC5LPA0jnP9IPWiaxkxnbLxrI7kCZMNljfmSGUaN2N1VRessCxgYzE9a9qWypX4KDu3z+HLLBmKy4J9YHPhktB0Rg9TiZ6WuHnwd0DMowlOZlchKlO4sGx3kqi3qr2XUxwH7wwYfNy9EftF0Kaz7b+9f+JIbHcP+QLrrWOxWi1p8wBJ+symhviI4e4RDxaA4mxzKBzz4QSJinGzRdFw7/M+yDxfiOr+YMaTdh2CTOOgRuc5NKcwbTEv67Yjhcke9pEw59baBkVWD4lW6zc3oNJgwmY4JvefUZdp9kEdXgXWf2tthQu0ncc5gz70zwQ0Y8FBeKw5ByIcBcIc/JHvrfz0FAs/TucbastEGbpxVKQ1C4OzoxKvIVYi21GVOx+iHh+XPHoxDv5POn4jJx1/ExucSk8pVn7+2LwD39whwfE4MGxTzAdJj3zMGwohFnhMqXchrviOgsimpzUi7AgdX8A==
*/
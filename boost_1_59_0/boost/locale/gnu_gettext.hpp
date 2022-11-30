//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCLAE_GNU_GETTEXT_HPP
#define BOOST_LOCLAE_GNU_GETTEXT_HPP

#include <boost/locale/message.hpp>
#include <boost/function.hpp>
#include <stdexcept>

namespace boost {
namespace locale {
/// \addtogroup message
/// @{


///
/// \brief This namespace holds classes that provide GNU Gettext message catalogs support.
///
namespace gnu_gettext {

    ///
    /// \brief This structure holds all information required for creating gnu-gettext message catalogs,
    ///
    /// The user is expected to set its parameters to load these catalogs correctly. This structure
    /// also allows providing functions for charset conversion. Note, you need to provide them,
    /// so this structure is not useful for wide characters without subclassing and it will also
    /// ignore gettext catalogs that use a charset different from \a encoding.
    ///
    struct messages_info {
        messages_info() :
            language("C"),
            locale_category("LC_MESSAGES")
        {
        }

        std::string language;   ///< The language we load the catalog for, like "ru", "en", "de" 
        std::string country;    ///< The country we load the catalog for, like "US", "IL"
        std::string variant;    ///< Language variant, like "euro" so it would look for catalog like de_DE\@euro
        std::string encoding;   ///< Required target charset encoding. Ignored for wide characters.
                                ///< For narrow, should specify the correct encoding required for this catalog
        std::string locale_category; ///< Locale category, is set by default to LC_MESSAGES, but may be changed
        ///
        /// \brief This type represents GNU Gettext domain name for the messages.
        ///
        /// It consists of two parameters: 
        ///
        /// - name - the name of the domain - used for opening the file name
        /// - encoding - the encoding of the keys in the sources, default - UTF-8
        ///
        struct domain {

            std::string name; ///< The name of the domain
            std::string encoding;   ///< The character encoding for the domain
            domain() {}
            ///
            /// Create a domain object from the name that can hold an encoding after symbol "/"
            /// such that if n is "hello/cp1255" then the name would be "hello" and "encoding" would
            /// be "cp1255" and if n is "hello" then the name would be the same but encoding would be
            /// "UTF-8"
            ///
            domain(std::string const &n) 
            {
                size_t pos = n.find("/");
                if(pos==std::string::npos) {
                    name = n;
                    encoding = "UTF-8";
                }
                else {
                    name = n.substr(0,pos);
                    encoding = n.substr(pos+1);
                }

            }

            ///
            /// Check whether two objects are equivalent, only names are compared, encoding is ignored
            ///
            bool operator==(domain const &other) const
            {
                return name==other.name;
            }
            ///
            /// Check whether two objects are distinct, only names are compared, encoding is ignored
            ///
            bool operator!=(domain const &other) const
            {
                return !(*this==other);
            }

        };
        
        typedef std::vector<domain> domains_type;   ///< Type that defines a list of domains that are loaded
                                                    ///< The first one is the default one
        domains_type domains;           ///< Message domains - application name, like my_app. So files named my_app.mo
                                        ///< would be loaded
        std::vector<std::string> paths; ///< Paths to search files in. Under MS Windows it uses encoding
                                        ///< parameter to convert them to wide OS specific paths.
        
        ///
        /// The callback for custom file system support. This callback should read the file named \a file_name
        /// encoded in \a encoding character set into std::vector<char> and return it.
        ///
        /// - If the file does not exist, it should return an empty vector.
        /// - If a error occurs during file read it should throw a error.
        ///
        /// \note The user should support only the encodings the locales are created for. So if the user
        /// uses only one encoding or the file system is encoding agnostic, he may ignore the \a encoding parameter.
        ///
        typedef function<
                    std::vector<char>(
                        std::string const &file_name,
                        std::string const &encoding
                    ) 
                > callback_type;

        ///
        /// The callback for handling custom file systems, if it is empty, the real OS file-system
        /// is being used.
        /// 
        callback_type callback;

    };

    ///
    /// Create a message_format facet using GNU Gettext catalogs. It uses \a info structure to get
    /// information about where to read them from and uses it for character set conversion (if needed)
    ///

    template<typename CharType>
    message_format<CharType> *create_messages_facet(messages_info const &info);

    /// \cond INTERNAL
    
    template<>
    BOOST_LOCALE_DECL message_format<char> *create_messages_facet(messages_info const &info);
    
    template<>
    BOOST_LOCALE_DECL message_format<wchar_t> *create_messages_facet(messages_info const &info);

    #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
    template<>
    BOOST_LOCALE_DECL message_format<char16_t> *create_messages_facet(messages_info const &info);
    #endif
    
    #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
    template<>
    BOOST_LOCALE_DECL message_format<char32_t> *create_messages_facet(messages_info const &info);
    #endif

    /// \endcond

} // gnu_gettext

/// @}

} // locale
} // boost

#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* gnu_gettext.hpp
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
*/
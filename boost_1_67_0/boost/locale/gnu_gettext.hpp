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
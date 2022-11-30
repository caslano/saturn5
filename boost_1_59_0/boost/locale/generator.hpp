//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_GENERATOR_HPP
#define BOOST_LOCALE_GENERATOR_HPP
#include <boost/locale/config.hpp>
#include <boost/cstdint.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <string>
#include <locale>
#include <memory>
#include <boost/locale/hold_ptr.hpp>

namespace boost {

    template<typename Type>
    class shared_ptr;

    ///
    /// \brief This is the main namespace that encloses all localization classes 
    ///
    namespace locale {

        class localization_backend;
        class localization_backend_manager;

        static const uint32_t nochar_facet    = 0;        ///< Unspecified character category for character independent facets
        static const uint32_t char_facet      = 1 << 0;   ///< 8-bit character facets
        static const uint32_t wchar_t_facet   = 1 << 1;   ///< wide character facets
        static const uint32_t char16_t_facet  = 1 << 2;   ///< C++0x char16_t facets
        static const uint32_t char32_t_facet  = 1 << 3;   ///< C++0x char32_t facets

        static const uint32_t character_first_facet = char_facet;  ///< First facet specific for character type
        static const uint32_t character_last_facet = char32_t_facet; ///< Last facet specific for character type
        static const uint32_t all_characters = 0xFFFF;     ///< Special mask -- generate all
        
        typedef uint32_t character_facet_type; ///<type that specifies the character type that locales can be generated for

        static const uint32_t     convert_facet   = 1 << 0;   ///< Generate conversion facets
        static const uint32_t     collation_facet = 1 << 1;   ///< Generate collation facets
        static const uint32_t     formatting_facet= 1 << 2;   ///< Generate numbers, currency, date-time formatting facets
        static const uint32_t     parsing_facet   = 1 << 3;   ///< Generate numbers, currency, date-time formatting facets
        static const uint32_t     message_facet   = 1 << 4;   ///< Generate message facets
        static const uint32_t     codepage_facet  = 1 << 5;   ///< Generate character set conversion facets (derived from std::codecvt)
        static const uint32_t     boundary_facet  = 1 << 6;   ///< Generate boundary analysis facet
            
        static const uint32_t     per_character_facet_first = convert_facet; ///< First facet specific for character
        static const uint32_t     per_character_facet_last = boundary_facet; ///< Last facet specific for character

        static const uint32_t     calendar_facet  = 1 << 16;   ///< Generate boundary analysis facet
        static const uint32_t     information_facet = 1 << 17;   ///< Generate general locale information facet

        static const uint32_t    non_character_facet_first = calendar_facet; ///< First character independent facet 
        static const uint32_t    non_character_facet_last = information_facet;///< Last character independent facet 

            
        static const uint32_t    all_categories  = 0xFFFFFFFFu;   ///< Generate all of them
        
        typedef uint32_t locale_category_type; ///< a type used for more fine grained generation of facets

        ///
        /// \brief the major class used for locale generation
        ///
        /// This class is used for specification of all parameters required for locale generation and
        /// caching. This class const member functions are thread safe if locale class implementation is thread safe.
        ///

        class BOOST_LOCALE_DECL generator {
        public:

            ///
            /// Create new generator using global localization_backend_manager 
            ///
            generator();
            ///
            /// Create new generator using specific localization_backend_manager 
            ///
            generator(localization_backend_manager const &);

            ~generator();

            ///
            /// Set types of facets that should be generated, default all
            ///
            void categories(locale_category_type cats);
            ///
            /// Get types of facets that should be generated, default all
            ///
            locale_category_type categories() const;
            
            ///
            /// Set the characters type for which the facets should be generated, default all supported
            ///
            void characters(character_facet_type chars);
            ///
            /// Get the characters type for which the facets should be generated, default all supported
            ///
            character_facet_type characters() const;

            ///
            /// Add a new domain of messages that would be generated. It should be set in order to enable
            /// messages support.
            ///
            /// Messages domain has following format: "name" or "name/encoding"
            /// where name is the base name of the "mo" file where the catalog is stored
            /// without ".mo" extension. For example for file \c /usr/share/locale/he/LC_MESSAGES/blog.mo
            /// it would be \c blog.
            ///
            /// You can optionally specify the encoding of the keys in the sources by adding "/encoding_name"
            /// For example blog/cp1255.
            ///
            /// If not defined all keys are assumed to be UTF-8 encoded.
            ///
            /// \note When you select a domain for the program using dgettext or message API, you
            /// do not specify the encoding part. So for example if the provided
            /// domain name was "blog/windows-1255" then for translation
            /// you should use dgettext("blog","Hello")
            ///
            ///
            void add_messages_domain(std::string const &domain);
            ///
            /// Set default message domain. If this member was not called, the first added messages domain is used.
            /// If the domain \a domain is not added yet it is added.
            ///
            void set_default_messages_domain(std::string const &domain);

            ///
            /// Remove all added domains from the list
            ///
            void clear_domains();

            ///
            /// Add a search path where dictionaries are looked in.
            ///
            /// \note
            ///
            /// - Under the Windows platform the path is treated as a path in the locale's encoding so
            ///   if you create locale "en_US.windows-1251" then path would be treated as cp1255,
            ///   and if it is en_US.UTF-8 it is treated as UTF-8. File name is always opened with 
            ///   a wide file name as wide file names are the native file name on Windows.
            ///
            /// - Under POSIX platforms all paths passed as-is regardless of encoding as narrow
            ///   encodings are the native encodings for POSIX platforms.
            ///   
            /// 
            void add_messages_path(std::string const &path);

            ///
            /// Remove all added paths
            ///
            void clear_paths();

            ///
            /// Remove all cached locales
            ///
            void clear_cache();

            ///
            /// Turn locale caching ON
            ///
            void locale_cache_enabled(bool on);

            ///
            /// Get locale cache option
            ///
            bool locale_cache_enabled() const;

            ///
            /// Check if by default ANSI encoding is selected or UTF-8 onces. The default is false.
            ///
            bool use_ansi_encoding() const;

            ///
            /// Select ANSI encodings as default system encoding rather then UTF-8 by default
            /// under Windows.
            ///
            /// The default is the most portable and most powerful encoding, UTF-8, but the user
            /// can select "system" one if dealing with legacy applications
            ///
            void use_ansi_encoding(bool enc);

            ///
            /// Generate a locale with id \a id
            ///
            std::locale generate(std::string const &id) const;
            ///
            /// Generate a locale with id \a id. Use \a base as a locale to which all facets are added,
            /// instead of std::locale::classic().
            ///
            std::locale generate(std::locale const &base,std::string const &id) const;
            ///
            /// Shortcut to generate(id)
            ///
            std::locale operator()(std::string const &id) const
            {
                return generate(id);
            }
            
            ///
            /// Set backend specific option
            ///
            void set_option(std::string const &name,std::string const &value);

            ///
            /// Clear backend specific options
            ///
            void clear_options();

        private:

            void set_all_options(shared_ptr<localization_backend> backend,std::string const &id) const;

            generator(generator const &);
            void operator=(generator const &);

            struct data;
            hold_ptr<data> d;
        };

    }
}
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4 


/* generator.hpp
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
*/
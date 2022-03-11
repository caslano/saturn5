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
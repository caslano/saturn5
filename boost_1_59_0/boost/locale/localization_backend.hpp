//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_LOCALIZATION_BACKEND_HPP
#define BOOST_LOCALE_LOCALIZATION_BACKEND_HPP
#include <boost/locale/config.hpp>
#include <boost/locale/generator.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <string>
#include <locale>
#include <vector>
#include <memory>
#include <boost/locale/hold_ptr.hpp>

namespace boost {
    namespace locale {

        ///
        /// \brief this class represents a localization backend that can be used for localizing your application.
        /// 
        /// Backends are usually registered inside the localization backends manager and allow transparent support
        /// of different backends, so a user can switch the backend by simply linking the application to the correct one.
        ///
        /// Backends may support different tuning options, but these are the default options available to the user
        /// for all of them
        ///
        /// -# \c locale - the name of the locale in POSIX format like en_US.UTF-8
        /// -# \c use_ansi_encoding - select system locale using ANSI codepages rather then UTF-8 under Windows
        ///     by default
        /// -# \c message_path - path to the location of message catalogs (vector of strings)
        /// -# \c message_application - the name of applications that use message catalogs (vector of strings)
        /// 
        /// Each backend can be installed with a different default priotiry so when you work with two different backends, you
        /// can specify priotiry so this backend will be chosen according to their priority.
        ///
        
        class localization_backend {
            localization_backend(localization_backend const &);
            void operator=(localization_backend const &);
        public:

            localization_backend()
            {
            }
            
            virtual ~localization_backend()
            {
            }

            ///
            /// Make a polymorphic copy of the backend
            ///
            virtual localization_backend *clone() const = 0;

            ///
            /// Set option for backend, for example "locale" or "encoding"
            ///
            virtual void set_option(std::string const &name,std::string const &value) = 0;

            ///
            /// Clear all options
            ///
            virtual void clear_options() = 0;

            ///
            /// Create a facet for category \a category and character type \a type 
            ///
            virtual std::locale install(std::locale const &base,locale_category_type category,character_facet_type type = nochar_facet) = 0;

        }; // localization_backend 


        ///
        /// \brief Localization backend manager is a class that holds various backend and allows creation
        /// of their combination or selection
        ///

        class BOOST_LOCALE_DECL localization_backend_manager {
        public:
            ///
            /// New empty localization_backend_manager 
            ///
            localization_backend_manager();
            ///
            /// Copy localization_backend_manager 
            ///
            localization_backend_manager(localization_backend_manager const &);
            ///
            /// Assign localization_backend_manager 
            ///
            localization_backend_manager const &operator=(localization_backend_manager const &);

            ///
            /// Destructor
            ///
            ~localization_backend_manager();

            #if !defined(BOOST_LOCALE_HIDE_AUTO_PTR) && !defined(BOOST_NO_AUTO_PTR)
            ///
            /// Create new localization backend according to current settings.
            ///
            std::auto_ptr<localization_backend> get() const;

            ///
            /// Add new backend to the manager, each backend should be uniquely defined by its name.
            ///
            /// This library provides: "icu", "posix", "winapi" and "std" backends.
            ///
            void add_backend(std::string const &name,std::auto_ptr<localization_backend> backend);
            #endif

            ///
            /// Create new localization backend according to current settings. Ownership is passed to caller
            ///
            localization_backend *create() const;
            ///
            /// Add new backend to the manager, each backend should be uniquely defined by its name.
            /// ownership on backend is transfered
            ///
            /// This library provides: "icu", "posix", "winapi" and "std" backends.
            ///
            void adopt_backend(std::string const &name,localization_backend *backend);
            #ifndef BOOST_NO_CXX11_SMART_PTR
            ///
            /// Create new localization backend according to current settings.
            ///
            std::unique_ptr<localization_backend> get_unique_ptr() const;

            ///
            /// Add new backend to the manager, each backend should be uniquely defined by its name.
            ///
            /// This library provides: "icu", "posix", "winapi" and "std" backends.
            ///
            void add_backend(std::string const &name,std::unique_ptr<localization_backend> backend);
            #endif

            ///
            /// Clear backend
            ///
            void remove_all_backends();
            
            ///
            /// Get list of all available backends
            ///
            std::vector<std::string> get_all_backends() const;
            
            ///
            /// Select specific backend by name for a category \a category. It allows combining different
            /// backends for user preferences.
            ///
            void select(std::string const &backend_name,locale_category_type category = all_categories);
           
            ///
            /// Set new global backend manager, the old one is returned.
            ///
            /// This function is thread safe
            /// 
            static localization_backend_manager global(localization_backend_manager const &);
            ///
            /// Get global backend manager
            ///
            /// This function is thread safe
            /// 
            static localization_backend_manager global();
        private:
            class impl;
            hold_ptr<impl> pimpl_;
        };

    } // locale
} // boost


#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4 


/* localization_backend.hpp
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
*/
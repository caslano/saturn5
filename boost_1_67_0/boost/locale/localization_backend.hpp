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
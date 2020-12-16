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
jokaO5nAcvE7jfqz04F9gRnAAYIeeB4wE5gAzBL55PuhwGzgeP5mO+C8DfNbm3bQk+3gFaUdzLbmDqhz0qly6b9iOm+lXPomYCrwNuAc3jMoAW4BLgbeKdoBf+9GP7oXg+VhuONwIeAcDTfGCPZIjqcp5Hd+arI7WwcF+uR3GpDfqRoUeMoyPNloY6vgtsNVwx2GOwHXwQw2EuBmwBXAVcDtgjsAdwwu1C/YiIXzPf+7zxk5/y8qyG6K839xvj5VOV8PN3km625DL9o6m83IKUmTdsZyM2vXYikeyECr59blNvEku8UzON41nlQv4zlqE0+qazzxiYNc45nmYTzOM+3Jfvp40mvjycyVUdTGMd3DOJx52WUTR3FtHFkZJaWJjMaK52IP43HmJdxfH095bTyw2e9aXjM8jMOqf5s4Kl3jyMnOOV9EZMUz08t4jtrEs7VOPK75ucTDeKz6D9DHU1UbT352ToZLXmZ5GUeVTRzV0W6yHko+ZnsYx3F557TpbBQ9K/cYiqddOP/KZ2JXTvpw6jNJj91+l/dr66ayOVSfraDeBvs3lul4WSa0ucY5tME5tDN8cj3hcxk+TwmfWk/4hQxfqIRPtw0PZPiuSvhiXXh3mXklfHk94WMYvqcSvrKe8P0ZfoASfms94c9n+AQlfJUuvPsdAyV8dT3hxzL8RcD+CKSZ4+vuq9Z3V7XBO6r/Ze9a4Kscw/h3dmmXVu3WttZoWpd1sdYSi8pUKFaiUESrbYymJkUShpCE4x6GoRLC3OPnMoQQhpD7EEKIiiSX//ee//ftPee879l3jmnyO9+vp//O97zP837f+z7f7X2e532ZnxpoHR++U2vX7fnHuagB1+mJjDWWg1aDNoCiomKNbNBg0CTQPNDiqPB7aXgLb+EtvIW38BbqtlO+/6fPrqxsgXn/rLj9IhHPP90r7v4Yac3+bN2a/U3fHghYEUfl6HvDiilazG/abBboYq1TnyP0mvp4TM7y8SGnjY9IBm4T/A7qNelz9PER5sFuEfwU9Zr0Oc7z9Vm22XZq6VgEr7WO/WLwGcvV1O5BryvdmBNE/FZOEPFbOUHEb7VA24Yap7WrxQFsF9/oNQfcM3/iHSv6XGN88EqX+065OhwH8F+NA7D92t30fu2uPn7tbrZ/mvcdU17hn86jXD+gmIuRfsn+wC7AAjluIEdffy719GL9vYEVDvPqH46K/V/65ML+uH83n34N7GYDKCo6PH4R3sJbeAtv4a31tp3y/W96E1vg+9+a52/El+b3v6mUueJSTv8cmydysu39K5r2l5dK+xslXVNLPWMJx0ljCZWasYTanCZfKYWb/Y6Tfb2rdesReOnlCQaZC58dodZdL+lmQwSld45Gb0OTXja8M73W9/3IKMaL8rv4NjGuYioXek2dUjK8Phc+VZS/UPW9T136XJR4wb9S9f1PWX0uSrTg16jGAyirz4XvIPiXMp+E5dES3Y2DbD3cr82FPz7L53cr5WNauVMlNBA3c+GvYH82dpX6U06Gx6bLh/+9qzbnFvqc59yyrDYf3hA2PFnVh5TV58N/KfgLjfOb8uEp48Y35XhbF/cHzIf/UfDnGjP1+fA81gptPvzk/1g+vHWd9+Unzzj6wI+gXbizPXbBe1JQY6jubOc2wLLavOv7BT9WZQOUVV/HacBbBX+4apyPsuq864cEL1ebd71U8PfhPJ4i71r0cUkr9K/cl4nMqa8H9QIt4ZhsbRe7Lx2tkbBalF+o6lvoUozRSm3TIPjnqfoass7HbGu7OB+zlcueuaepcdYpVSzbDflbzPFDPwnbtnEKr82poAcSPX9PYR9+JOd1hbgmRijjwNgnjtk8j44=
*/
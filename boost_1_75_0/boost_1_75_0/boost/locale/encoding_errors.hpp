//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_ENCODING_ERRORS_HPP_INCLUDED
#define BOOST_LOCALE_ENCODING_ERRORS_HPP_INCLUDED

#include <boost/locale/definitions.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <stdexcept>



namespace boost {
    namespace locale {
        namespace conv {
            ///
            /// \addtogroup codepage 
            ///
            /// @{

            ///
            /// \brief The excepton that is thrown in case of conversion error
            ///
            class BOOST_SYMBOL_VISIBLE conversion_error : public std::runtime_error {
            public:
                conversion_error() : std::runtime_error("Conversion failed") {}
            };
            
            ///
            /// \brief This exception is thrown in case of use of unsupported
            /// or invalid character set
            ///
            class BOOST_SYMBOL_VISIBLE invalid_charset_error : public std::runtime_error {
            public:

                /// Create an error for charset \a charset
                invalid_charset_error(std::string charset) : 
                    std::runtime_error("Invalid or unsupported charset:" + charset)
                {
                }
            };
            

            ///
            /// enum that defines conversion policy
            ///
            typedef enum {
                skip            = 0,    ///< Skip illegal/unconvertable characters
                stop            = 1,    ///< Stop conversion and throw conversion_error
                default_method  = skip  ///< Default method - skip
            } method_type;


            /// @}

        } // conv

    } // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* encoding_errors.hpp
LXFR1VIrWPudVh6rtEEyWNsjen6p4vTTTN30D17d3ABFEerR2EWl4qqU8ozkgyUFUtuiF/uARvEPWtcnimg8tQxOhXnpbr9+Tlla2PN9MpRuWuVoDfJQjxAj/M3/5Wa0wIwf6AK6yQl+z59A3KjZu7Nrpzj5w20Nmz9iSyVXPF26JyQQWXuGYlVVHf8QyYmZ7HVLjkQsURoPQ9hhoSxygzYIwHIuSNzPm0i3Kn/yyRKin7Pf/ZqicesjhWq2XISf13TyESVgrLRu9XaloMzt2GlsbLjUbqSwxJ7ccFqXi9RwbHzt7gzNk77KtGrVAzzbdiIidLs1MTpWSbgU5Q2NNs7NwUBnDwLz3dMn385bfGr0BLCNjn1qja8hNudXdlq/BfH3OCzM2D91qDx6rgS1hrQGewbxN6xrdCc5oDkQTQLBj2qhjDG7dUv2OFU/lor0tsFTBXaJAJw9H3ucv2wk+5Fv0N83ivyJZ4RVxJh9iyGYNrZyUnmf603KqkileoZCHCxacLEd0AO1UMilfQwWKUb88H048hNRlABUJjoa3/2BXj1zRjBBtx4CNp2Su1P8MvepN+kZoNe9itfiUL5kL18L5e2DJS4fL1LTa7gjbQrMs43XZ8Yrc+y5Bz0rFRA+9twvl9VN6J875jfQ9tcVes6AH54nejMSU64LE2mcbWHvHeYuMidC7tHG/CQC67y4iGLQB2stebdJojv9
*/
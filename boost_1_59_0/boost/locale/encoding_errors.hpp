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
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
*/
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
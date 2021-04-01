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
pX7lzj+lNuxI1ShX4EREdDpx5O3NE9hxV1TZQC9gT8XDGW4WzJaZSM1TFGKClweQVjgoLJUYnynxOdGTpjiBErwYfBC5EsIXhkrZw0rVW1fWBeAT2WaWm8Hs+6QxMxpm8XoCOvjQd2YYkW3WgFGrwqYU2jB9L1fMoTrEdHODnf5xqS0WcVA0P/qHt6O693kWOE/PNl370mk5zjS00ymN1Xx9J4JC6PqB5XwLa3USME4T4tmgxt8pUes4e3hF+9gdUR36PPG1SK0gevxKX3C6q+KI7gyJePWCd9CeZUuw/9MzJOkY6nVOZ/ZWY9BwziR4p+d9f3goyTe5o2OxB9D/FbSml594qv/y4YFMT7C72U8sIZKFokz1Hf6RJEXdifMMUkkEoewXDGIInhqsAkky5tSp1ZFYPvWZr7XLHfuOyRm6Os7L2kWFMVT7VwqghT0o/fJo9EgRVpbLx4wdK62+pWUwokT4SMyZQrFOHLTl6X9JO65SH6oWM31mXt4RG6cCTMsSVhxkCSj4uk2QeE7TNbOQ1TmKO53QB7gFYkGogyjg+13MSURwfetvbg==
*/
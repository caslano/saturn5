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
dD7wWAtoYVwl+oh312YexhlIW1dx55k3Cpp7l4h56T0ePrQZYu7cRbjlK0xA6eoQY5863ZbL4kalsI06RM5V902FHsAp1t7YyKOugliRtY04oRw2MgmhLVeeclWXCsWFF+tTQyvdtWgSN6bA1S400LtOKDdGIP2bDYkn8XoLxMUYD85gP0XArZ6OPDy5b7oHlLisljZFR7K7120oWsHwfW6aHpM1hNq1duMT3boHsdBFitad87wN9a11dDS6n3Nu7ySC/LfYN6+ukkgEhlgizdhBcPsl76QSS7uCYqGryLhsg1pI82YM3a0UXA5D99Kg4mIsmIHuKsjMAFKDcT/IL9RYl2AWdBL0E2J3uyCvr/9vklwGH2GxlTXdJmzwDJSvzkaH4vi65JdN19k2U+PE+01T2wTPvg3OIx32cfQOhdmH77L4nPPq1hAa9XB/4/s8zyTzCiHyfp6cjic99lO3ol+bMKp2ASSDDOX+byIyQpkcX46mo3+d6Rcakod5DkAHQF9HwMf1Ifduct+K+V7581Q17N2nChvM1nhxA05Wj74LX0VfwfbrugMgPRJbwSqrJIWh8lsoaIvfj4G5Fb+M5QYJ8UNkn5IyzzimIk2WCYMw8b7WdKQ7fH96Npmejq64eTJtubYHM5BorIJ3
*/
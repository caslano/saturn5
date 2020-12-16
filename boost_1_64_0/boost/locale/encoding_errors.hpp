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
b15O0NDjVnyLXwSMv7U+wTzR4vJQFtrjMV4m+KP92XuyTPhPKbLEdGYs/WOZ8TGANZBfxw5a/cGXZkS8IzNW5hxJU26sivxL9XGPkK9q8xgl1pc2bWXLDL19LdOqMYV9/hadbS3T6u0uaRcvnxfyNyzIS4Ppue7D+onPb5ttnFbKH2YzSTlp4834vJCHdfnJDvq6bGAc/lXIQAHggfUMo6RUU5cyRIGz+LWgV+PPoZ3GF6dAlV3ldwn5zSJRJuB+8OvT8ivdRzv13yzLV+2Wexj7f0sm2AJw+LpoC9qyWiqbasR5pUj9ZITauqQbBUvgJJ3OkK/2bIq+nav6pb6ezI4tX+y4XKJMSzwD2uYfCHAB6gEFoO/R66EWRrRqPD/TFvoDmb4Gbcyl9/VreWdgayzbzIU5kXIlRY+5J9v89zI/w1hWFO4jNXTcspwZ7AM4UsTBHK+TB9JY4mEqspl165e0uxs5+rpl3qqdN/JElqoPyHNlmo2MbP0YwDzUOnfWn1h0Y/GpSj4Uf/dq3P61mdFa1FGPrY58OFiDYddhfGvkY+mnQa9v60jrzJY6dr+JMqwxboaa/Z6JF6E/8exIOUMx+3aS7pK177bIKFOmx5xEH+8Z+TmP3aem9YfSNmjGMCVtBuLndIN4/hDIWYBnQ0YG4zDy/n24ny3vD5X3+6NLXfw+f+heQ3jfUTFMr98SrX69tbMNex2Pj6Hjkjh0XBKHjpnWfO8uzoMPkTjO1qyoDs1414wzD7WZ5xc+QZ/ms+pwF7iDdvj++SiTJm6uVl9Mz/Od7L908ypt2vqDbc4sMa3aD2DKrzv7wrTWOcWxubFjMmjqgX2gJb6v9dwcZQw7N0dZws7NkWel3fNfjD1u6I+4TcRP19WZaPaaeluDZ3PukzRvuk9E/j8ZSfBfkmQ8DrjfnaKPtWRTt+p3xxsyzTauMsz8TkJNXGocqq33LqV+1pd1KeJrQ38c03N3Es9fN0bhy+wyY5B5LnZ7eX9vlxteO0tdg7TtpEvfpsyzmVtOEM9zNO1GR8t6IV8X7Cyfu94Hta4tdenandLX3C6f56Est7EOv/UWyXuL3W7I2g5Nf4NnUyDhQ4C73Mna88ZqOWsY4mIcN/KZvBP7NNYVz+pKfqvkM4+xhvztMjaQvxvdBdjdPBN/PY6eYF8XYvO6k4wD8E5k850IfRvmFIAHwNX87uB8QZ5bfQ7p8vibf5v4NmCkEZgQ+7syFIu3XdYZdIBzqzkTQrFzNyk2eO/ZnUP3Nh4XuvdY373NDcbx3WyCec/Ixu+8YJrWWfU+xNGWfvlX6L0WbThLtmG+15p3PVPzrueq7zq/qfagrMuLwvvrQEbkmPcwOu+KXSzv/l7S1bnteFezS9TxDvk5H+8qdnE+3iGtJnawpv+25mvGDtb030yr9t8XYQzd/08eRy19d1Nk3w1+rbHnkRYXtE7MOUtHX/2Nr5ULVXLS4mi87YijrjriqCum5TduzHnJxP7qUx3jyhn/fjoKpl8tqadOvZ4wyunHuBzg6yVNqWssSpgF+AWwusuNEUr/PdVpo890+g84e6L0Y6CPVaDXL/tZ+POTz6e6tsS/BwHcLnjbAOwI0NQB81PjyzeZfgz2knw0o8de3fTBcJK8t6o2Hv1TfOdDY6BXpi0z15U+kL+TTH8Ft8vfHsVXQ5WxKsv5RObldq1vDMJ5tV2MpzCe/QwJsuVz1JCkrTNSjA2NicbKuD9d6pljBNerYsdt7097Ev3oE7swrrelH12WExkn7HOkKdvV2r7EJMrZvLds1/jmvWW7Op/3lu3qfN7LtDKG/n54j3yQNR+8DzMQ8LRgiHWOu8LfbNn9nOeq7/u8PPo=
*/
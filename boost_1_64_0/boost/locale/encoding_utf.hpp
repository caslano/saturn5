//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_ENCODING_UTF_HPP_INCLUDED
#define BOOST_LOCALE_ENCODING_UTF_HPP_INCLUDED

#include <boost/locale/utf.hpp>
#include <boost/locale/encoding_errors.hpp>
#include <iterator>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif



namespace boost {
    namespace locale {
        namespace conv {
            ///
            /// \addtogroup codepage
            ///
            /// @{

            ///
            /// Convert a Unicode text in range [begin,end) to other Unicode encoding
            ///
            template<typename CharOut,typename CharIn>
            std::basic_string<CharOut>
            utf_to_utf(CharIn const *begin,CharIn const *end,method_type how = default_method)
            {
                std::basic_string<CharOut> result;
                result.reserve(end-begin);
                typedef std::back_insert_iterator<std::basic_string<CharOut> > inserter_type;
                inserter_type inserter(result);
                utf::code_point c;
                while(begin!=end) {
                    c=utf::utf_traits<CharIn>::template decode<CharIn const *>(begin,end);
                    if(c==utf::illegal || c==utf::incomplete) {
                        if(how==stop)
                            throw conversion_error();
                    }
                    else {
                        utf::utf_traits<CharOut>::template encode<inserter_type>(c,inserter);
                    }
                }
                return result;
            }

            ///
            /// Convert a Unicode NUL terminated string \a str other Unicode encoding
            ///
            template<typename CharOut,typename CharIn>
            std::basic_string<CharOut>
            utf_to_utf(CharIn const *str,method_type how = default_method)
            {
                CharIn const *end = str;
                while(*end)
                    end++;
                return utf_to_utf<CharOut,CharIn>(str,end,how);
            }


            ///
            /// Convert a Unicode string \a str other Unicode encoding
            ///
            template<typename CharOut,typename CharIn>
            std::basic_string<CharOut>
            utf_to_utf(std::basic_string<CharIn> const &str,method_type how = default_method)
            {
                return utf_to_utf<CharOut,CharIn>(str.c_str(),str.c_str()+str.size(),how);
            }


            /// @}

        } // conv

    } // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* encoding_utf.hpp
U13W9EG3Ybn0DZP5zH4wMHbEQ+4P5x6NjpzuCPQY7QJkNFpQYGL+EbuE8gV7wAs9WgHqCWED+zspTbq31oJ4DDBABCmf+I1UstJrJxihWpbmpn0ea6iq4QxIHDwdpVmgIwTAhno7canGEaGc8MKy4ei0fdIGjG4HX4rvXj/AIfomVW2oxOol/v6bRgTrkadxm1F3KRqIPux3XHKTK3bunf7JPgL/EiBPkM4Web9pqNATeByfiXVIz3tJh2lShNiK0YZHJ/j4uvVx08i/+dLT9defkg+JRfBqAtOKlVFjFfS9PGS5ROlJtW1lE5bJZx8BxzXcnsHR8jBTWxusUq8jGLh3dLYoV4uotr6w8FpFsgXX1Ad/9VSqYr/pwWmWxk1mpeGFr+2GM53NN5C4dP/gZTNKdB1IVKHtI5uloUeN7ARRsaqbDegND6iV2d4ZVGjjMHzuBzqA+KL1nyIwq550b62HNq6/OHwXpFYrOYpASFkYJ1pbTr9NrYOE9bRWWXw97ff2ldu0+TmUiAhcoxs12NRzD5orVbonuEfD+9TEpt9/6pbl3rbw0v5GCw==
*/
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
K8XpCpkVbZZBYwYNyBpRUqJAycs7vb63dcrcVoHCAY6z/L6PZw/g1Ou02ek0QmTYjV7a5K33Pxw8/aAre1klSvteGpTz1sBpKTNbCpgTJnHl7rGHJvh7ufe9REpmKka1tft8w7Oc9lTJ+cli06yEKXcZLEJHciVsMOGAxBv2hUerldj+CerXpVwCJssEt7Nv5YDThJncYX0Qm2Q1wp+gJPPuLjBzsA5qi7Sz0a4+iM29wG1krWdJWlJaYe2A04ztXemi8+uXnX8DUEsDBAoAAAAIAC1nSlLPPIJkfQMAAAgIAAAdAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfY2JfaGRyLmhVVAUAAbZIJGC1Vd9v2zYQfvdfcUgekhiq1fVpXYphnp3UxgIrsB0UAQIQlHiyuMqkQFJ2vKX/e+9oO07adHnpFMSkyPvx8fvuqGNdGoUljC76w4upGNxMr8Q8y67E4E8xGk7FqHNM29rgf1ik3Z/3dKALrz4i/gt6aIwe187+jUV42VqIB9j+kdcdja8lSeHg8iDO4HWXBziNLmKX5QPPhXgt0R1j45+UPe8ET2mF3NhzYJuN04sqwOngDH55//5XeAPv3r57m8BQGo01zAKaHN0igQ8qrvxRyfv7nsffE8AAsu7tQs0r
*/
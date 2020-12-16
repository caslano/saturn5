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
LWWhqwLWHIU2oq0PvO4Ov0Xa46wTpNfMSfV10q6tP32dtGvrTz+WMS373ZjfIStcPysyX/mDvSuBq6pK4/eyCCoqboiISQruGhAYLiluuQua5jJN7CCKQIKKaUXmWlTYOGWTpZlN1jhFM05jZTPU2GSNlTVWVlZUVrZMY42VldX8z3n/dznvcS68h6g18+7vd/jz7jnfd9Z71u98n1pn5dzYfQ2JbC116DrmIlV16oyTEcO+j35c0uw112NE3ImW+ghy/xxK7gfDX1eviEPTRyv7oV9K/xxwmmbNeT+YLN5t42/TGCN/N9O1A/DX9+NOnUuxU4T/dF27AK1+jhPGfvhdGe8s0IQZF4i/7FNPSrpl2KWLMgrASdOOwFs/J+rOdD0s/a8wbzSgKw5l+AS0/L8t5ngY79qhqXSweCw388Q78uZ7dR8RT25+WRp1VrBcL5Vpj0aaJS+W4VgzCJYXXgalOlZEMF/PSL5/Ns83VhnVuGH8OceYcLHukPQRytlHlmyPPVlnuyXtQLMX2kEJyuUxsTaBewcuEGMm65J8usk+byv6kn1oY13g/Kc2CwmJ9lN0AWXn5+bWthND0k2DHvIo5pG8wCnMSlMRFEEUwCZiTrah6BHqIsNhRDGi+E7Scp811NGv8kwtkushzEsx/sm04f+G1z6nMv55Oj8V4+Tsyfpxcsc5+vmqMdX6xscWejlfNaZ6Pl81pno+X2VYq9+8/QzOVw/TTv1HlAs+ynIK1ZSTdr6q7J90lDTvGX1QAr9Azm6xOdMI9aIcQ70oR4a1PY/8SPqHWn1CnPzd0fp+7pW/A9U5qzV3fkD6DXXpJ8LYd02Qfg/g22+FPYdA9rXkx/SQpkA921hDnucgp+04l50v35WgnOZzviO+u8acY3vXJsS3NGCq9S3J3x9O1X9bBd31c9DkFKXNeDkHTU7xbr6TnOL5HDQ5xfM5KMPK/rgG38bxc3/6c9CoaP0ctFitj0bMQYu9rJPiFM/noMUpns9Bi1M8n4MWp/w85qBbaTv7Yj+H3aXpQDEH3arWWQNz0J6cpzwgaUb6rQb/HWipe4y22CNoaUwwQ4w7zDZSbx/yR94fW+XFd/XOR9+DP+ej1vzh5mkOXYzQeGDNH56X72KQV39d20A82n7ckhm6UdJnIR6tLk3Qa+em1tywc6rcczejjCnWfHVlqmO/PRRWsz4H7wjm6UX5/t/gNdkowtsNxkxL1+PHMp4lYi6ra4tIh34e25PrgXul/wS/GzAOVKFmnxeSVtjrn4b6uMdsDTqZXvL5QG27Fm91DySCedkr03wEGihjjdkoo0IjzxrHJkq/TtZYdZX8jbiYp9/Jsh1n7ZfskL/9rXEvXoYPYnjn72aybANcynaakrb51ppigOTnxzKxxjlr7+g1ma8DEIxbatyF/yJNSHzAlcMxTsbRrc58ui/juE/yOG6ei3SvR1ofxPrgOZTxJNMPNjdawB5AAdPD9COc6MOj0TdG9uacenL9c+rPUurMqZEuz+bUzVPd5tSkVefUzvTsdaan/A2RoI510kOelZK+wkjBuiXChec66KA9jv23CHzjF9injfn6naS5HG00Hn2hmq/XJZ92ZqFxp9kJNlv8ZTqdsiaR1tnI6Z17eDPfvyjVdY7yptvvK6e5/v6L8luVY4rsR51NcM15N+4YwlQ67ivml0B2Y1FpfkZBwbI0Z6lCkkO2nU6hlIuL046b5GG6ho3XjpkMq9e12Al4h/SP0vaJpHVvz1Y/sFH6n6dvH8q8eLcM11IjT6Rfc4g8dWT+Wcd8J/Kp0Vuo3Ns8YKurz17nnF6Hn50NzLNn+3S4vF/61rq//+3Yk6PDp78YM+LN91c=
*/
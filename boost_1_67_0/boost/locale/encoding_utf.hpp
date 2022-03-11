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
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
*/
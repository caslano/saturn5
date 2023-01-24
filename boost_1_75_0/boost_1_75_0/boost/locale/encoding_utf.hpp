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
ffUE1wfrgr5dgyeXNtcLvdAsAgJNyhsfUQeTTJW9orDwu9KrR6BUOZ9rZD+RiNl2dmv8Ymf7yKkt1DYTiXp1QB6bdK2WE13zrDY+d+UImTaj7mv6OgLlWL4SifHo8CJhLqatvIB4bMNarMigEQA1jrIkkIJPNkgK7uw9yudciNibVZI+ikAzkq4zpvgtd1D1Wtft1ksLdEHwncL/wIW71W3uBl5Njmor15KPRvgYbBygf7mvedzhfc9J4H/wuLLFDqbfOd3mMJgaqeAjFZXQCBVLWlBUD17XGtlDGsj++2SoWBNvl+asvm9F+RaW5yvm1oRjj1U1aLsRzDesl8O0vKVb3aFY3R4GTlzqlXwXf7VMO+d9Di0wKSMxiHoFWxWLzYffNEW7Cyuek3VQdHuoj4obDXpDi9+qrrF47J7lSdMWGu1hHx05YttrUlk5CLiOz6rhPZUPRZnPy52gbIXCFTWsGLcfDZHskoHnFqcdf3nVt2ojBiDZGf56Pmk7bmNV6JMOuH2XV4R82/UVkjNbGyuu0BeRfl2N+PT6Jq+Q6LVQXuwzsFCiSEL2OcmXAMuZXQKdHUHkCScXQ5uwPZ5JEojolUxYIHyv88WkmPnLWMY5jO32JqP+vK6+STRM68jpmDzV/te5JA8gwsAklLb4kCRZHxn7BnaLV6/r61aiKPITd/MjQgaRewSsqxJuucW5FDjxeSJhQLCrUodr
*/
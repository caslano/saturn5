//
//  Copyright (c) 2015 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_UTF8_CODECVT_HPP
#define BOOST_LOCALE_UTF8_CODECVT_HPP

#include <boost/locale/utf.hpp>
#include <boost/locale/generic_codecvt.hpp>
#include <boost/cstdint.hpp>
#include <locale>

namespace boost {
namespace locale {

///
/// \brief Geneneric utf8 codecvt facet, it allows to convert UTF-8 strings to UTF-16 and UTF-32 using wchar_t, char32_t and char16_t
/// 
template<typename CharType>
class utf8_codecvt : public generic_codecvt<CharType,utf8_codecvt<CharType> > 
{
public:
   
    struct state_type {};

    utf8_codecvt(size_t refs = 0) : generic_codecvt<CharType,utf8_codecvt<CharType> >(refs)
    {
    }

    static int max_encoding_length()
    {
        return 4;
    }

    static state_type initial_state(generic_codecvt_base::initial_convertion_state /* unused */)
    {
        return state_type();
    }
    static utf::code_point to_unicode(state_type &,char const *&begin,char const *end) 
    {
        char const *p=begin;

        utf::code_point c = utf::utf_traits<char>::decode(p,end);
        if(c!=utf::illegal && c!=utf::incomplete)
            begin = p;
        return c;
    }

    static utf::code_point from_unicode(state_type &,utf::code_point u,char *begin,char const *end) 
    {
        if(!utf::is_valid_codepoint(u))
            return utf::illegal;
        int width;
        if((width=utf::utf_traits<char>::width(u)) > end - begin)
            return utf::incomplete;
        utf::utf_traits<char>::encode(u,begin);
        return width;
    }
};

} // locale
} // namespace boost

#endif
///
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* utf8_codecvt.hpp
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
*/
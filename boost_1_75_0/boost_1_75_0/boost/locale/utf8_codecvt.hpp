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
ysj4qamluYrJK9VQUMRvOKjTUFBGm+7ekQ6YpdryjXzIZ/I45dxsP5/eQaLF8uZBaSvo7E5f4hLtyY3/lobBwGWMVmGm+Cs+ZreG1bbc2fwxC3Nja62hxc5PXi823v7Fc1uP9mcLB+c99GTQeNp9TGEZLW5zhRbyEru+hhrXXasFTzvxUgkJA9bDcKLq+OIEXAmx6xn0MBEbyT359+FaTC9zu1ZPwRyoNyLA3EYpJglsyGYsk3vBM5OcydIpDc+QjZCzMuaUtKY3zDzXCZV9gwei/oX6w+CB4zhaSbdi+a/oA3q+xO4XHXpL3sXAo+WwywYcU+gMM8sF+94UzxVhXs7+dJ1AyZn15b3lXzvhWzqwMV9p4x4Z0DT1DMQzyl6qEah+QXt9zs/yFE097NzdNGvX7ugVHuazWJFSG2UpqAazHHVgfN4QXhEh6TRbBiTH/UCTvmCPMdonxt3gCw+e32ir6AaPFM4WII7/qN8pLI959qyk8A5Aph1sEOqlLaAGGBv+KRWEW4fsg/dtiJ0xiTz5w5B7sLYz7WpbATlCeY5y1IX7k7LpKgL7HwMyPyYis30rRxwmbzSZlK623vh5ahbEzxt/z0lT2YlUJ922SomuF1IJlGN54LAm+f1gMylXvP/TeYEahZ5RRXG/1Q4BLDPyI6R7DKtjIkAmOSIFOVOqGQUbPqaojX1atawdpchpAqBTLr4mraIa/q0O
*/
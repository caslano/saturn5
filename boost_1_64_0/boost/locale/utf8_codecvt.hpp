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
0y/Od1vUrfCLD+L57cv23g84BTgUeCJwf0mPQT39FHre4HG/CYxj/FgvYCMwD/iZHMeUwHmTFf0/nOcp++mHAA8CTqW/fgb99bOBhwLPAhYDF9CPvgh4GPt/LK+DccCXgEcCG+hPX8k1NSfB9zcLtAi0BPQkaG3b2Gbnag7G390Svu5/08+9s33c4fmaPX7tjbCz2ATEYoCKQJNAc0DXgB4GrQVtAaW2gw8bVAyqaBf2VYe3//cWBTr93/b/l1ZMwb+C/MlVMyrP7D8gf6AZDdAysQDFIhbAqqBp/r0de5rvjX4VC5/9PMlnX6zz2cfbfl9LSbNjGua341DqrdP57CW9vgfn1Mc+1Fo3L5p1RHrej7dG0LccIerw06/36wwTcyVMFHKvRXTl+M4g8fu5iAMQfTvFlYiYzzpjr4g8Y27E3hwDchntorlmlsonHaEYI2F961HfcYL/ckQmx1uGi98NEd0xmlCHeVYuiOjCsRh4faJMXoTafx2hG08ZJnL0pwj+C6KeDLPdxO9XIvriDetdaFoQ0VHt247wHWupLDcVd+U8To0mH62UgmOdgzN+wkiEvlzE2/ZwWWNIm0WZvqrxNV/92KpQQdO8DEfyuF9F6bNRi1lulBiHm4KOa5pHYn9R7qOIz/HFc31EB0nfzPJTpPG6HqINk+05rbZHmr87id8pph7+tvr2YFE+luUxoit+J4p6U/DXZFH+Itd+2Hc0Mp7NehcI651VjskQxDlvRPtbOVhnZ+E7AnQuqVr1N+k8zi0CEtdE9k6f58HT18m4n5zaF8cn7jNzy2fOEOXEeZnn2pHnalrmMFyX8kWfy3keeoKyzFzwaN11iVvn9NlVTucpgh4v38b5nCvD994R5WBMTb6frIrzFH4yEm1FNP0/+W10xw1vkOKY82iXY4TcLZEVmA/kE9jmSFcH40PQD66hxmTY6X6RHRB30151jqhT6UOybXmU4O+uuB+oZOmjod3PizH5PVy7G+vtMdfBsea+fqr7APQ59zuxrN+1msf7wdGCf23kFEi9gV4Yivvqm6D2ER1xvSca/SMTjUPQLmxTbGWnzWKbZgDHC/nFkaV4Vr6JK3GgK8t4xZVpJEak4dU6yVgWcYtRDB1iPBglk+JQHk943bXJe7N5nFPKpHHk7aI90hV6eG/h9WHdS9aK8qPte8Wj4jjjPDnTtNFlqL8aZP7dB41+AceBU+WcXP21Dd0J2IW6xLEY9u86/k42opOeFMdhdCseU1BgcN9ce1//Qda+wqZ9A619S2PsfQOsfXOa9uWL6xP7utn7Bonf+9m/9xG/p7exfu/V4vMqNnfvWd3WENuPoGzQOvqhNhnqa1iaJE2/rq5LF+9BvT7PXmjjdQUdQvZFxXWqlKV/h/4lIfskxqAKVNcl5J37slBWeV1az+l01qW9TnivnZ8FCtJum/d1iTZz7OtS2YDs/9rRns8fF547wG5WvNlfcU02EHDt3WHm8bJ8T7m/uU/v97pU8CNdiv6mrLetVEl+rwsE/zv+dmEMS++Dhi7Vu5lts27Bf8S+f10qdEUobUPWNVrYBnpDel5cLPgvItojyY7HPNLUhxbvjGcb73msox1tyvrtstvzek89Lq9YNr57XS142xA9chnfxyR9Pu9zabw+1gmZh6DjTGOxkcF6cT6mHI8rydYTa8fDbRBydZJePMgHFNjX3beCX4q31rb+Ohgbt0mUWQ6ZJl/9jNJpp8kxBD+LMgcbaWwPj0yNEYF95Wg7XlN4LwTxmkr4F3yCVZp3O/maqWVly/j6ttRaz/ZP6Zqxb5bO3tNMWc53RnuffVr5TMqzre8VZTKV90fIq+6Ptuwvgq/+doGs43s=
*/
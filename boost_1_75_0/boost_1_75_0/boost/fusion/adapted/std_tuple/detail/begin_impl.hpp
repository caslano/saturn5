/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09242011_1744)
#define BOOST_FUSION_BEGIN_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef std_tuple_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
Cjh5DM6DMz2zTh6cZXiKYqXCkUtSKxUORfsHpcLJyGzK+fimVg2lwtEekCdmx3OtM/KHt/yPZzJh9efzk8uGh9eqPuRCvQbeoqhXTjqpVxKo1/OkXr8fRPX6owLVa01FHEv4dzeReiX5Hc1viZVHNb92DVavXhnqeXuq99/kYR69hDB2zQ2vBJdMtg1OHuZtu6tseqGyPTBZ2TeYbu0brLnJY5MH3lhn5a0BB96pddZneHrZp2XdcFDqi/xRdff4ZP7PNcHyFJT/81baMUiydgySxBcXPAni9LS5S6R8i7nVQWbG1++kse+0348LssGmeP1xS1NSRD4S25B4vTNSitdrI1FpykfWu7aEb3SvblRnHrylbu6oPK0ANkby7xaLym2Q8sZxxy2whowwP+CKW5qiH5/qDSVdqr5ffsCO+639qwC+p6xqlO/P3fXyfRfwfY+zwo1Tk53G4mdhCag0/aPupnD+d0xDnF9qct7hfmz6FQ82nOtq48pGv+FPV6PfcAt/w4mJQd/wqasp35DU4DfcN0J+Q/YI/IYzDzRsc5vX+YZAHensqk9HXAVD4CtyhAbskpswyUFacOjmpmjBA/aGtODN4fIzpgzHz7j2ARPXQt3FB++/vt9Y3n8Z3p/AA0A0eapmWrb7bpanV83pSXqP44XjXGLasA29iQ7qxdvRvXR0lrtoAsSlPsDYJIn4fzaN/G7v9xSrc23C
*/
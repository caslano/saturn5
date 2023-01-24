/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_DISTANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_DISTANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<single_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
              : mpl::minus<typename Last::position, typename First::position>
            {
                typedef typename mpl::minus<typename Last::position,
                    typename First::position>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& /*first*/, Last const& /*last*/)
                {
                    return type();
                }
            };
        };
    }

}}

#endif

/* distance_impl.hpp
8wfeHex4KQ+5CtdXHa+C4a6l+eksOjsIl8v7y+Wrni2f6yHsKvERuALXB7twj8R58/qgz5EuleXiH+y6/1u4P6CSF9QkaVgFL/iW7l8vjYmfUqSny+8v92ZOpxoNYvlcWZ70dDf5dYv8MnpH8vuGJmqjVx6P2p3za3xKjmfYwh1QS7JcozzNHP83KxfV6QaAUMRe9srHrtrfMv1blzzQJt1MtN3T8u3Plg/dBBpl1ylxPyd9jr3s2xLzoalBiJElBxd1ykf/UpF2BX9oCpBTeX58jOqwb0UUyrRX8jnaTD6qpFvQF2tUrJ93VzxIFEt+ozsyf2uAf36dfMuz5cN68+mjcg/Lkd/o9Bmgnqle9+n9NYf3MqWb9bR867Plc1cN/VnWV/2hX5pwz8Ck7BG9AaBCqc3vWfxLpFxJR1c6sf0r/sub2g886i3oQx2k/wbp50Ge26z45CarP+s94uPl+DoqZdhUsFvuSHPtaQ/7k468qIdOysj16ffP9bCXQ9pX3t+iN9kotqO/0dUbMAJ1+pspve3l8v6qoBvCWooadq/z3Mlf62WtNnkbSIDF6rL3h8e1p/cLQrzQs+NvzEc+YlI2CrvVpDPYpXO7Zf7arFwPmZnn+8/udcKKPkrgmgbx6qD97QO8Sh3ka4b05vnJ7hJvuTLjqJyY56n+qDfJHyzpZ9dkZXhX1pg3RZel7hv1hUIZhy59mjEmuT9O
*/
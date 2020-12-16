/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };

    template <>
    struct end_impl<assoc_struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
                  , Seq
                  , struct_size<typename remove_const<Seq>::type>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
HYq77mUBOeUet+M80Y6G7meYdq/5951hSj/a/QxTkyd/2zNMVUeH5/1klHtyKB0sdsl4HfLdpj/T4IgvpVH4Gbo4GcM441PH56KP72A/R575/nl+zpaGHY3Cy76dyAFnGlTBR3+esE3/2su9Z025025/a48u+2Zgeyl3Lc/V3CQtt2eRUQebAK420lz6owB4exO2Bf6+1ExrQZYyI8x2ZD6n/LD0//TTOyRTZjnsvsCIoyPfZY1NW/BKtwBcB6Sv4iFLvnFyzoiiv3W3N8k+1+V8XLrtfJzb+MZ9TN4pdJYtE3ZK/jvOpLmfcar7WTX3M2mRz565n1X77zuT5n4GL9IZs7qfYavrWTL3M291P9tW1zNpO3rK8yt2f7C30ey98VueeXFTm/tWdTj8M2lch3A9kxZv1a/zYOQzad0s/ioYXttDhJfk4Xye83z4U/1GP65h/F7ODlHv0+nU+9SLep9GU+9TIXgjOMvQ+p4uU2N/rTftj9SHfivPQN1G/f+3g1vAP4HvKZ3MWm/onUzXcvAHQ+t/8lP/Uyz1P4k8vwfsCN4r6aA+qPHUA5VFPVBTqQcqn3qg5oIPgbeBqw2tZ/RhsAJ8BHwcfBTcBFaAL4JPgF+Aa8D94JPgz+BTYEPRd0L9UutMfcVcMwBd9FfmsjzzwHN4FuwSngWbAgaot3+mqZee83eUqYte+tnU5zWXZwbn0e7CZWAR9X7NUmnReiAXmPWD82n3+naWqf+f82E8cNHr+K5BfbvgQOpZngTuor7/D2mPQJrXHPAj5u9jS/iVhwh/A8PfRLsElWAK+GdQfvs849nMfL7A8F807Stw3snyc+hfexn+ZJzyGt/H63wfVSzHNxj+W9Tzv83QevLeZnlut+qVOkS77GP641zPvV2eZalHyfR3ntIH+Ov0Xis9Wgyvv3u89Mc5ks2fuxxKp79etYRX5vDnHh7nBBwvlx5KD9mTrLeH9MdxNsM74LH7e9/ibz79nVGLv0ozXnd/Kj0cZ3L86dQT3pftfxDtWAwGM8AhtB8xFFzBs7/rePb3Q579/R4cwbOiSWBjcCTl4ShLfed4z7jJpb5P4hnWVNptuRBEGMpeyWQQTulBvdjQ+i/RFpTewzSmLx1sH6WeomVP4RwWXNVT9WdD/1/Phu57qv58aP350P/N86EHn0Ke1iJOuGS4INwtcOvgtsEdgGu9DvmFS4HLg1sEdyfcOrgquH1wjZ5GOuCS4QJwS+HKn64/T1r/+e/7/Eb3/4tnZM/51ff/Zf/+KcylB3AdexDnpKYNYRAD4rgHuI5drC/njhuakphCO8vRrKfT5nT4WhfX286x7xuF0tOETfw+rrfdBTcK6UnX6SnumRueniOx5uhcews49mqYH3MvYlpQfuayD2ZfP0ziHvhgr94j6Az+E/kZtLImP+q9YttO56HcPQ9DJbCGKLWlKn6P2vO/uNx+97YiQv7WueSv0mbj17RV3KaZPAuUTEGiDMua5Xut1HNJalbuNP28X2jvCo/U9gzXlh3lYa4t6zDgVT2jXVX1DP817Zz+B9cpj5TdUvd1zUjrbXVf7/xPrWu6r0fWfb2zruuX/6n1yMa95HmDe7u2TTA+XJ069rmjRpxy8vOHtx4Zb1CuUt4uduhjPonrMieDXSzz7hyD8o9ycbHDDsWpnH925HpFJ96h7Mx1oy5cZ+nKdZZu4PWSBtoP7QXeZVlPqTYonyi3JL4TlZ1G/Tmb8QwGh3OencP59aWcX9/F+fX9vEv7jOMubTXv0orthbHUZ38e2AlE2pVdqxQwBUQelN3E8yUfHj3Pvsqj59f3gRdTT73Mq3eA6RI+mCHhe/Wd0pZgNniSV5Wn0sc=
*/
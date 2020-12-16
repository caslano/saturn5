/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305)
#define BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct single_view_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<0> > type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
5j0RFphkhXie56PlOagGtE3MCp9YOlBYcLIV8jObd+6XERSHFsfsoXmHlfKcYoW6zG6c//Yo9QVtHDPH6nLZKW6qFZKZDfppQwVhLrR2zHoNG5mP8kRryyxDs8XFhDmmWaEas8efHW1PPUPrx6xFldKbKJfpVijFTP4OD+aCVpXZxEr5lwnzo/Fcyk9KKEdjzrBCBpO0tbH1X9HneDPlur81AbR7+/F8YX60CszubcpRVlgELR+zS4seZRdmwUc/hZhdOff0vDAnWlVmTX5pe1KYD602s753G9yh+dAGMus/MFNHYd7ZVijKbM1sWC0sgLaM2d+3DmWiuDl4vmVW8+hvXYWF0FRjwpdqc6Dxfr5ZenaTMA9axjR7Z4Lo7zcamA9tLLP45c6VNJ9PHec0MJeBudESmfHP0f3RFv3dOTSbtOjvzs1Vj+lCU43pQ1ONGTQYE+apx3SiKfuCpprPi9bNJK3R4/l+GnOBOhcvmiqXIJpqvojBmI6F6jE9aKox/WiqMcMGY2qL1D1zoKnmc6MptyU05bZkMF/EYD5tsXo+N5pqPj+aasyQwZiWJeoxXWjKfQxNNZ8PrRoz/k5G2MAcX6nNa2AhA9OWWqESs97tG7cU5jGwIJpqTMsydZzbwAJoqjFhuTrOZWB+NNWYEQNzrlCP6TOwMFoyme77FivV5jYwv4GFDUz72gplmXXxbd9K8xmYH005n0Gc5jeYz29Qn0Fc2MC0VQb9NDA/mnI+A9O+sUImk7R7X5eo/N48wzyrrfR8F8wpZZ/1W35YWARtGbOfD/5xRlhwDV4PmqR16NdqpTDnOit8w+Lm7+uXLMzyrRUumtiY4UkbhLnXW2Eri7u86c+xNOYGKyxhlr/ua7cw2GiFCcyOXFoxRVgA7Rivr//0H8k24bMLlsvQqf1nCIMtVviSmWmgz04WsEI9kLZu1vZJVIPOnG9vfUM9Q+vKxsw5YHdRYd5tVpjE4hZ/s2eYMMd2K/zI16GEK0GYhrcZQWarV1ReR73+wQr7meU5+nK8MNgZnWfyr0e/pxrQ7MzoPhXNh5bEjO5T0UJoiczkfSrmsks9phNNNaYXTTVmEC0vM7rXRgsbjKntVpsb7Stm2yuae1Lcj1boyKzMgJUnhfl1Nu1oxkb0PHmPlT6TMpmH9JTvreHzXTTxe3lmc7fhH21Z9Yuw8H9wmwBp1SZ8/hnF7bXCaGYVx835XJhjnxU+ZXZ93sOmwgJoDdl8+a808gpzHcBnTyxOPnsaVT6I1j4tLsZccsT6a4Xv0WfCB630PlEsGr2jhOZDy86M3tNBC6D5mDVrPTyWxjyE5ypm9LuoaEG0tszov1XRHD9ZoSQz+R+pOCZabWZJsyYOFxZCS2HWNGQ6K0z7WT2mG60CM/n/qVgfGq+B/ncVDX5Rx7nQCjOj/11F86LVZEb/D4sWRuO9pnew0OCweh00ndE7WGhOncl3sLB2tELM6Ded0HxotZgd6Zu3m7AI2nxm7cec/Ip69mu0der3H/nuwX+jLdhsT3pa9yP4nJbZL9Ub7qc4tCRm/DuoAbSpaZbODJBQd08LYe7f5DkADb5Zsv8N2TErbDNL6/co5baw4Ek61qFF/5ZeBC2RGf/+uyOEeTLjeXrQ7jGrPW/XBPnOrBWWMotkn5a2tl2GuH/Hz1fSakhvXmn+5Y3jP8IsZ6zwHUibf733DWERNI1ZnfqtigvTzuJ+y+z4kW4XhYXR9jKbm2H0CmGhc1Y4zMxqeTue7LwVcjKbkrFTU8pFZ7Ff7y1FNVywwipmVxoD1RBG28Fqv7c+11aKu2yFr1ncjIWfd6Q4tCLMLhbNuYfiruDzOmZ5TiTPERZAK81s6Q8=
*/
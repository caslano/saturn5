/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_TIE_11112014_2302
#define FUSION_VECTOR_TIE_11112014_2302

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/generation/detail/pp_vector_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct vector_tie
        {
            typedef vector<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T&...>
    vector_tie(T&... arg)
    {
        return vector<T&...>(arg...);
    }
 }}


#endif
#endif


/* vector_tie.hpp
j53QgmmquEpzcS0W4Uach3twPr6IC/AtXIin8VZ8D4tluxfj9bWoLzbH27E13oGRuAyTsARTcDnOxjtxFd6Fa3AlVuAqfBJL8QW8Bz/FNfglrsUgtnEdNsL12AXvxe64EWPxPszATZiNm/E2vB+X4QO4FcvwYdyCe/EhPIUP42ncht9jOZ7H7fgjPoqtaO8dGIaPYyeswHB8Am3x5+T+IA7TiT/XQT5HHTEMO+Mk7IJZ2BVvxggsxu5YgpF4D0ZhOfbER7AXVmJvPIwx+Br2wU+wH36GA1Gp1CCsjUPwShyO1+EIbIojsQuOwn6YgLE4BiWeidxnpK468WD6quKeVGrW048bI/fmoI2HeDCRW7yLG2OW9cI9rFch6zW1ve6y3vuq9U7Yy/WwXvBWTX5GcWNkva4G61Vf5r7g3d79dfuDn+YGQjXJqF94yruXp2/4knfd+4ef+aBOQONFgW79xDsvCrysfcUr3rX1F08gX6M+45mLAn/2fuNV77r2Hd+0KPCy9h8PqPKtD3lY+eXpR757UeAv1pf8LP3HG4+hPzkpk1RC2kE6TDpLapzIfyOlkJaQtpIqSWdIQWPrBnQmxZOySSWkraRjpG9JjU28lzSVVEwqI1Wa/P3V/Yt/8S/+xb/8byy/UP//zLwcy2UZ/z9eNX//brmWvltieN6JpyP5x+jmuv28bXN1eZ6/TOmnMmOMZg5Abf9P6cvTLkD6UTItkHpemDHXKa/PkvmVpI+Utb9cOhMaSX8SnfmrUnCl9b1m3qvtE55OKa79F7Olj36cXLMMIr3DG2ITNf1I0y2W/JxphZYs7/ul2fu1s8X6fflc5/ix5EsfJPu2BVq319aBQd0HtH2gfp3LEvX6vqqq7kOfustdd3ufiTNS9xjpa9QTqyKVTKTu9pgC1N/bfmHK8dbJ5NZ/TWI3mMnNcWyo+9Vq4z4wfZFsaw39yaKlv/gHPINtg3/D98mk1OSov61vXFxWRl6mbZ6Ykx7q/tNk17pX6fST+kTTz1pp/2pVjASlzezrnnf2eVB6AvOauo9e1u/4EPB+l36S5Mmrsl/LHe3EEJ1UZ1sV67RVieO1LF5zfq53X2d9bY7ZNkWabv/oCk3/6EpHuUXpjs+zJl5Ec17bIP0oJX+XvpRlmv7USn322fanrO88VxTp9MWPt51npE10YnJIG2Uj/dYk/kbqtLzMeY65z9ra8qR0OZ/Z86TttceTJUjGyte33cf5B+udoaGqp2qOp+HO+TDZv3rLUDLku6Avx49SVi3rsfV2huuxxR9ux1ZQLZftc2zHek3/uBSd8VBpqr7wqv7r6uNE+sK77vsizb5nk1X9AOXYcn4PZGZIu5sdr3FcpZK9rGvSGV8QQ1uerm+NIc1DBtc5XAtJtu8SjnvJI1vzHcN+cuTTOch2bz5pmjOfhY58ONaUbOT1MjzVVF6XfrLqvMxBtueXURnOvIodfb+VjrvOOm1Acz376zrjIBpIf2DWCcft+CGNeSJLc/yMzM2xz/3G/q7x+KlWHT8ZM12Pn2Cd4ydE5/hJ0RwDevNoluh83tN0joMYnXNAbA3nALPOmIpSnc+6yVk+Jzk5x6k/v3IcFbG/0mjndrX5zs1x9revcOxnThWqc8pu+/Gp2ofltvP0HLexC7wm52PV2AE5HeuMe9kkfemj5Xlyd/yYhjXlavb3ROv8mh7HMSj7eIHZuY+byz74obVjjkvb5Jmqz0idMNftM6N2/xfpfIcV64xXjNYdY6meyzPAp3mIHfPWasbNRDaU58DyOetH+pQMwmY72832e0NGzjh+NBV47PMs9XOeL+UzHeYYc5BeID+PXH4LHZM6fSb9dz8kfU6dzLM=
*/
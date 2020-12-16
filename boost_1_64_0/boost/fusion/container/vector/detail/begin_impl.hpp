/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05042005_1136)
#define FUSION_BEGIN_IMPL_05042005_1136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef vector_iterator<Sequence, 0> type;

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
S+K02Wg+X7Id+7P209J/a9lOOX9Pyu+PdnK89hiMHTACO2E8dsY09MCJ2A1z0BOLsTtWojduxF5Yi73xAfTF7eiHL2AffB398SMMxK8xCJX3YTBGYj+MwRAchf1xAYZhBQ7AG9GAt2AE7sZI3ItRqOO1RmNrHIhDcBAOwxhcjINxKcbiSozH23AIPoQJ+A4Oxa8wCf058cMwGIfjeTgCL8aRuAJTcQOOwk04Bj/GNDyIZ+BhHItKP1M6BuF47IeZGI6TMROzcBJOUX9XSP8xTnDyu8JPfg/0wTD0x6EYgGPt5pqU6KTvFwud/P94oXy/LUIfXIxheBYOxCUYi2djPJ6Dw3EpZuAyzMFz0Yjn2fd7nNv0+zmYTTtjP9RjiLR3H7lW2rtavje8lP9vyXYXSn/MRdgHL8ZRuBxn4yU4Hy/FFXgZrsIVeCNejtvwCtyBK/F9rMKDeCW24rhXYUdchd64GoPwaszCa9CIa3AOVmMlXoeL8Xq8FNfiSrzB7ryUNPM5z5bP+XTU4wxc3frY63G8fRXrKSiZx1sIZubEMweBbJ0bkV1imx+h54NSUsK25G3kxCG2uRKhdHy4LmDOAdk6b6Ljh666xAW2+RPLHdZONi5oPI8iCOPJK/hvG8l7yFGUZ1OmK6UuuZLH/tjUXIvUUtt8iyWl7AMPJljmXdTwfAt5H/lncnwZr4GcyX8zkRNp8xHqG7Ga58vLOA90XNaTXcNoE2VBWFvGMaljP3cji3OwH71MbEdZIhrJukS247kel/C8mmyd35GayDZ4F2VHcRc6zvX43MT2dnM+LnjPNu/Du5z2UXaEvI32HCB7LG2lzgcxlvNacQmuJv88gGNhEHW8kjgej2PQ20Cu4DXwuIQcz+NssnX+yAU8Xku2ziGpq+CYHEvmkvCFQBuV/ZHX87wevQ64NppfkkpZPHUzybXvWeabXMDjNNqjfAHXkNfyvA4PkN2SLfNQjPz3vQst81HqMYhyt0rkeSg6m5+SSfmTmJpsm6eSzeNlZPv1U6p57q9YaZmzsg/ryfGU1SazD7LXIss8lnQ04X7afoBy4yLLvJbVGIpraecFSr2UY89t6TicbchPsu1eylKG2+a5rMBa8h6ybr9l3svBRQ3nvriNaDz/JWqxOgeG12KZB1PEOb+AxxvJqZTXobN5MQcoX075WupvxF3kg2Rn82W8ed7uLOpQt4rnoTzezGuPofwIZZk8z+RxJVaRl8jcms083ob70H6ezR7KvJdY5ttEKfI8C5eQPVLZFu3n4WzmeSK+jQb+u+5s27wc/7PZlrJUrMQqmadTyfPaVNqslPG8luceq9x1BnI6eQ55GbmGXEfeT3Zd7a4LJaeTTeTV5M3kveR6cser2Z6cTi4iLyevJz9JPkDWXeOu8yJHkdPJJdf8t+cAaUlLWtKSlrSkJS1pSUta+n+kkzv/v6AsuzI/L18Zg25eAODPz/8/tYdOnX8f5Cr9aF3pmxYj6CxNNCp9boTmE3Lk6Ob2HHPNrA66dkA/6CK2t3uerTyXOT/XLrSMd04bGxmuk7ISW5nBWjZSLYsYbC3rbSuLsZYdrVDLBlnLdtvKBlrLbrOVRVvLzraVRVnL3ixSyyKsZXfbytQ2L7OVqW2eppaFq20Ot5WpbXa1laltfn2uWqa2+T5bGW2W+cQyT8J+7bjlqG8ja3vJ+O4qx3UG7OZr1/sq5WXcEMBYXlRAPZn3+yXl7LeiIF/mP9vK5i+UY9WqZRxroaVsi846jpd3it381e3dlTITDZUx5HZtj7Bb10/aqc4NKTc/rywulblqoWoZ+zKocxsok3ZMNsjcCLUehZaytAb1wmUcsH09S1mWtYy2TZY=
*/
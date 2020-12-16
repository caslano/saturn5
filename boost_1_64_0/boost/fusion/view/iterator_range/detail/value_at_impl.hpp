/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_VALUE_AT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_VALUE_AT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<iterator_range_tag>
        {
            template <typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::begin_type begin_type;
                typedef typename result_of::advance<begin_type,N>::type pos;
                typedef typename result_of::value_of<pos>::type type;
            };
        };
    }
}}

#endif


/* value_at_impl.hpp
E+Ckgfh4EF4OHRwkeQZlt5/sat3nKhTyvr/Bmxch/Kd8iK63YyY4ZGJFeb8gaR/nceD72lO4bcrb5+aysT/mlxkPRVTx9nd296/ANNqsiKgdIXyC8UgkegbPtEaaKXe1itjaHaxTE9jxcB6bN2xRKrkMZWhkYPARPRPduFFFXp3EAsHzo7zhVxPI2C9kWwSNSYL8l/Lmu+ach1ImIMBoeHt4Uf4h4Y8g/6SUkZ8yM2VqL2JbccVy2o5ZkKs08Ji14gd1IdqHRvnjspBgDjO2u4FjBL4Jm5X64DoO+/G7NH/gFyJPM4+RYUY+6e0YOjn9/kL9iySBToDo1/vwGeofvB5DGQsFlVEKmQRlnqOMg5diGBPoiQWdT4goDP08Dh0Z9RIXhMESfWTEbUIn0z19VdC70IKHuSrZaAvW4XorY6dP++By0bA5UslcP0Zm9OfAycDA8t8saB9A1TOvYNUhAAwjuhOAFR/gHVfC7+m9N1FKyB8/pabvdptnYl8tGntvaRmUSZZQPlPtlt4fK2mdYfiHwktLpqeuB6vtAH0GSuJLn3KZ59DtTS1DPHPxZ1MvCtJQxaxRswleEfmhn3i8EKrCgwraNdAA+7BsnH2XIvIyGZmIQAfr3gBtf9mw31EJEuLU5W+49zH0YSnpWVWkL15Hiu3vmM0QyI58Kz2MSVnSmIJZVMa+kpw1pz8H76XN2TL8mJYh9aPMT/OY2ct/je/HXmTPPEq6DotUKsIoi5CxjsYHbYDbXPYpURDEcE6pGuezgpdREfgoB+e1kwGEc0pFx08SZlkmZIC85ClVFEDWRUo19sVi7ueRX05kYCAppwaNeziujNy835f5hUQRzpzhfGr3IFWjD5MylmksgAnHe7WGXIKY6WB69GqGVmIO97QadSgLFfqlnxNZB7aF49+mGns8gos04YIZFcKdD5cb518LL6B2oVBZGKRRbHkPyP08nqe6/OeihEM35CVrTrqW9NtdnzsODDPQAOjXrs+DRjBKq7e9Pg/0P9+F0HVo/DGQ0bf+r/Dz8E64vAwep9VRkvUfGHUKOz6fS+M5K1F4pR8d+g6ELtMroUw3jWs9RGXRU5KNbh1EvYqtflWX+UtA1373SHLe6NR3GzvhRVUdcmjR5gTIvaO5MTMV04XPUM+VNT/bwtmQWYh5O8WgH6ybn5qbjtEN6cpS8y2cvRuImG8TDAZ5J/WTR6Zj6rvAiGNHp+Kgjvs77p3Mr7Zx+vQI5dy6i0vHgPE21jviTixMxdk6Iu4L03HG69DFvfSu03FmZe7grt/tAFx1Vo+45O7TcdWYhPlPjbt0j+k4mBLug9m7AS4KZAz9k+BNVxgmN17T8J4aU/ppd20E96fXt7o9rdx4X+Me99J0vIOC6W836Qarb1TjXdf5e5P0rr8SestB0g1y1Y2KSb5f0DjzfizV3SfjXQyg67sWWHxjAvJwNSl5hUbsg+D3gVijMRPs+++M3b/qYI/f905Yc3UEsZ+4I3YENn6CPXG/O2DrGyWFnf8QG6cvmBUF94tDv7HixtB/aKfpTDu5j8RmLR1J0OfICzh9s1Pr0jqm35zB9OE+pOMbt3+Zgc+A6V5I1hNQ7Qo21k0MvKZ+9XWmSgeu7u5gvX/7HLfekkV6sz4oDv0u1LL1T3suXdOq3PNiXioT/ePk4sZ/8ceL7Qf5yfb7c8a9MxeJMMv9TEfEjXPrbBXZeMyM5C9ZkQWJjAry/rmO+2GzPE3/YkkbbpBS3Ctwy6FYFHs6giVnfm/D3bLGvc4HdO55n2/ct9X2REce3Gk6PE7sym9nmnQbvdB5b3q2jQFzUCmBY6POzrVw+PY5vgE838KA2Zvk9cup9Hq64Nw=
*/
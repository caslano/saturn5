/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct at_impl;

    template <>
    struct at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
        {
            typedef mpl::minus<typename Seq::size, mpl::int_<1>, N> real_n;

            typedef typename
                result_of::at<typename Seq::seq_type, real_n>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return fusion::at<real_n>(seq.seq);
            }
        };
    };
}}}

#endif

/* at_impl.hpp
T70RsVqZdonStMcAI8DnVUlAXWWzQff5lENsgxvKVCprp3/8wChAyFWe9uN1NnalzC0Dh+Dl+NvJVYVGDk8W6Fq1hvJvQWfnPgeZshpMmPTisjt5TzdkwlptN90s5Z2C09rGPOAS+2+8AuKFUmjZ3sgRaffCDOWU/6x3/SEk3yFlIsHCyrX5+BghHcMdGgdAxiEm+tKexieNDjMfqSvKfH3aoOT0iTgQRYv/ykN3dYUTspl9FcEz+cS6ixKqlIkbVaOCo/FOLK0KdWvzB5AA5e0v2HGgo1kmxF2PlVR7mramLhO3F9ZakdzPPo/5S9WDHYyBRzPFaH02f852d8lljRBD3cjPXeXAtVwAXUs6cPrCpM2rKd93Xb2iA1wEjp5XbE1nCkywJJYCzmCxpiYDP5c3bBTHSkZb73+1EaoQvQkayTsPRRJbSRROjSW8W2v/7tVU4OBouwrc+7XwUg1Aoylx9MsQnEqOK0OGmj7FgUOr09O+wV3zxCurN0a2dUfOEjOU6/80d7KeotatwQIrpW/jaRIHOk+hcRk9+6T/3RVmkUBkFTX++j+5Sw==
*/
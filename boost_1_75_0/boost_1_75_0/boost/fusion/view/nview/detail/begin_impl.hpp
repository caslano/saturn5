/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM)
#define BOOST_FUSION_NVIEW_BEGIN_IMPL_SEP_23_2009_1036PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<nview_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::begin<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif


/* begin_impl.hpp
CDEhIWxJa3IMN/ILjfrV+DiiXmwSPrW6iceJPBeXRX4iEfbH+IkGlcb+oEeFfF61mO39eC9el5XB+evnKbu7rSmtTYcVuX5l1wlHfmPbxuBmfNhAqSQX7ws0PxAloNcJ+ueqK4gNvL8zUN5p1UztcOXRsLVNAs5IbvQuWG2Xmn7x8pLrlNtYtQv8zzVUa/khOxN89xEAyZbzQRASU5GTBDAzEYiOMhq/MNixy+ouWrsm6OfJPx+VlqRIOkPcl4mf81L3loifIzHNt5XOl3vrGxu8qs6l4jcXCrzuVgc/ovjeoKJu3+pR0TcIX9UhE+kt7WSeaNeEzm2jcrb0o/nHT2RgW6wNCxbxn0eoxilC/LACEcHndKDzrgL9q42gemWm5/DIcywqXXw6yxfc/u8zI3Ho4EqFFXen5l4l5CTt2gG3k+Sit5uVbylOSygg+/hf+z4LBuhgBYyj710JqOamIxzzTXsu5JHhJPY3p9eT+E7nP6Vo3e8s/a4mr+BDqkSeCJyyVSMGlVLJV239yTnnDUXRBW8Uwci8VTdPa5xSpG6265Xf+C2zJuFLs0qucyPHvSTegFIPv0y1jmuG2TfNNihV3/3IET6iE+i9Bb0DePfwjD6iRaUomOXnpETDvjrmwfxhkJKMfxD4dr04cnydmmZpsQZ8IVyYYwSmRX/Q6sMHLpZCigYP9vOvxQRiNa8v8TGfOGyhh866g4es
*/
/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_04052005_1132)
#define FUSION_BEGIN_04052005_1132

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_begin.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag; // iterator facade tag
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct begin_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_begin<Sequence>
                  , mpl::empty_base
                >::type
            {};
        };

        template <>
        struct begin_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template begin<Sequence> {};
        };

        template <>
        struct begin_impl<boost_tuple_tag>;

        template <>
        struct begin_impl<boost_array_tag>;

        template <>
        struct begin_impl<mpl_sequence_tag>;

        template <>
        struct begin_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct begin
            : extension::begin_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence>
        >::type const
    begin(Sequence& seq)
    {
        return result_of::begin<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence const>
        >::type const
    begin(Sequence const& seq)
    {
        return result_of::begin<Sequence const>::call(seq);
    }
}}

#endif

/* begin.hpp
ouezpPyU7h8lmY75L5ZCodTSppCqHvPHHauSQrWp4f7x9H34r6qqRv3wZGsTGa4w7yf3yEM/OmWvygNGaLm8YWwrSSlkAO8zWWLxfXNIBkq2iBVXGV0dlY2S8GHKt0OSTf7/DOJje5050qSte5W6ZPo2QbkCGCjSXXlqbqMKw+MlXmX8oMpIgrIKbtaZuS0BvoFBPsxMg3xVpbGHjHV9MhCf+vGji5X3+U2C8gbu4f8Y873yLG7mPznQqLQDGycnRAsyLdAirGQRmP5ugVNm/0XEIrDClli1ak+8iaejKuYLwPaHlsPbcOxju4eTCKlUEBnfDk4m2RfejuLm2BYFI3hYldpkTSRqeIaz+X24AS44XYSPra/Cx+W1lKtMcFYttT4F98o3wCjKhmyjB7oq7/KbzlDPn3DH/4dlUT9KXtf8YePhUxM74P99oMU88wFF5BBmlR/0ZwKUN2LFvTjqCPVIvE/hFLsa2nCUCo9ab7nLRnt2oCdbUxCtoLUb/MHbbvy2N/zZag07QN5SjwMIG6zISw8kkB9E4EcQg6EK7x0mU2me9d5bj6j+WdKklJVwAUL2Fvxj2bYgr9BlMvnvqUiKw2Jimn+8J3uzsF7sSg6Nlnq47CTJyfM9cvI2Kdg1052/25fGRid78kPTEtlwmyXkya+cZpMCm7MiXwP90BsR+ynweKapDK8SgS87wd84YtM0Lf/tsgNKdiLK
*/
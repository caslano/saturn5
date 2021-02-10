/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_05042005_0722)
#define FUSION_AT_05042005_0722

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag
    struct std_tuple_tag; // std::tuple tag

    namespace extension
    {
        template <typename Tag>
        struct at_impl
        {
            template <typename Sequence, typename N>
            struct apply;
        };

        template <>
        struct at_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename N>
            struct apply : Sequence::template at<Sequence, N> {};
        };

        template <>
        struct at_impl<boost_tuple_tag>;

        template <>
        struct at_impl<boost_array_tag>;

        template <>
        struct at_impl<mpl_sequence_tag>;

        template <>
        struct at_impl<std_pair_tag>;

        template <>
        struct at_impl<std_tuple_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct at_impl
            : mpl::if_<
                  mpl::or_<
                      mpl::less<N, typename extension::size_impl<Tag>::template apply<Sequence>::type>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::at_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct at
            : detail::at_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};

        template <typename Sequence, int N>
        struct at_c
            : at<Sequence, mpl::int_<N> >
        {};
    }


    template <typename N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at<Sequence, N>
        >::type
    at(Sequence& seq)
    {
        return result_of::at<Sequence, N>::call(seq);
    }

    template <typename N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at<Sequence const, N>::type
    at(Sequence const& seq)
    {
        return result_of::at<Sequence const, N>::call(seq);
    }

    template <int N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at_c<Sequence, N>
        >::type
    at_c(Sequence& seq)
    {
        return result_of::at_c<Sequence, N>::call(seq);
    }

    template <int N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Sequence const, N>::type
    at_c(Sequence const& seq)
    {
        return result_of::at_c<Sequence const, N>::call(seq);
    }
}}

#endif


/* at.hpp
6TYUAVZ8aNYw4BmFHq1wOxhjwhgaN9snmSrjGJel5yVBaDux9LPmbIedNMmU4lcIOtRAnucRpF9jlVSDLW/mRVMxw0g8MSaTaax5a1CXR5FUigWEhTMq9mxiOdGtmBryKmMz6mfUY5RPQtjexCMRvVwzatHAly5BEINlQtk4CTRLncAZIeg7aRLnttXPJsa7F89vw5SnXj6DBUezIotcFnJ54hYzPiBG6R09S+hz3/d19xXq8Cx80VTvli3cy8xnVmY+62GmGbX5FDDCHOW5l4aw14roSJ9/DBna8mMY+3NO5xTW0yi3rx6oDt4hgZIl93PL3lCTIJUbUy9QxlkFOLW1ZaADsUWg0rAsAarAsQBUikAxyPAvPOY5U8ILf6IzkBDCTBDolZNgtHq1jq2CmshVRVBt13LNBLrGG2SkDIqspxD6YV+LYZ2CsfT6e14mAVSeE1WBg/32+rqcVpTdrCro2k09uBBa2kLVQHi3AIWRMgvUiKOI5jhpQVfRRG6skQSE7i9LBTFs2RT2FpFO7SSOoop9CaOxyA6NHbNV7rLFMi/OYUeMGjMUXNZEeqN1TglGGywcxUlG23JHNB4pLW6VI+UIY23/jI1ubNGrDGinxx3odCsUeORlIzu3EnWdYzjkTDZhprv9qW6p
*/
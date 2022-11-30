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
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
*/
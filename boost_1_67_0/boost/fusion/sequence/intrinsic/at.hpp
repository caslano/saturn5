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
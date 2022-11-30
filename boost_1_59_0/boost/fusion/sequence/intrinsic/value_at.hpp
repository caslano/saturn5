/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_05052005_0229)
#define FUSION_VALUE_AT_05052005_0229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/empty_base.hpp>
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

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl
        {
            template <typename Sequence, typename N>
            struct apply;
        };

        template <>
        struct value_at_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename N>
            struct apply : Sequence::template value_at<Sequence, N> {};
        };

        template <>
        struct value_at_impl<boost_tuple_tag>;

        template <>
        struct value_at_impl<boost_array_tag>;

        template <>
        struct value_at_impl<mpl_sequence_tag>;

        template <>
        struct value_at_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct value_at_impl
            : mpl::if_<
                  mpl::or_<
                      mpl::less<N, typename extension::size_impl<Tag>::template apply<Sequence>::type>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::value_at_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct value_at
            : detail::value_at_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};

        template <typename Sequence, int N>
        struct value_at_c
            : fusion::result_of::value_at<Sequence, mpl::int_<N> >
        {};
    }
}}

#endif


/* value_at.hpp
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
*/
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
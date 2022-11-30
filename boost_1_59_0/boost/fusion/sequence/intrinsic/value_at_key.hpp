/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_KEY_05052005_0229)
#define FUSION_VALUE_AT_KEY_05052005_0229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
              : result_of::value_of_data<
                    typename result_of::find<Seq, Key>::type
                >
            {};
        };

        template <>
        struct value_at_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template value_at_key<Sequence, Key> {};
        };

        template <>
        struct value_at_key_impl<boost_array_tag>;

        template <>
        struct value_at_key_impl<mpl_sequence_tag>;

        template <>
        struct value_at_key_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct value_at_key_impl
            : mpl::if_<
                  mpl::or_<
                      typename extension::has_key_impl<Tag>::template apply<Sequence, N>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::value_at_key_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct value_at_key
            : detail::value_at_key_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};
    }
}}

#endif


/* value_at_key.hpp
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
*/
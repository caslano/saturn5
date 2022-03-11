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
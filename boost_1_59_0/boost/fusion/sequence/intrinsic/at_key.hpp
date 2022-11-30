/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_KEY_20060304_1755)
#define BOOST_FUSION_AT_KEY_20060304_1755

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/iterator/deref_data.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>

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
        struct at_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
            {
                typedef typename
                    result_of::deref_data<
                        typename result_of::find<Seq, Key>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& seq)
                {
                    return fusion::deref_data(fusion::find<Key>(seq));
                }
            };
        };

        template <>
        struct at_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template at_key_impl<Sequence, Key> {};
        };

        template <>
        struct at_key_impl<boost_array_tag>;

        template <>
        struct at_key_impl<mpl_sequence_tag>;

        template <>
        struct at_key_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename Key, typename Tag>
        struct at_key_impl
            : mpl::if_<
                  mpl::or_<
                      typename extension::has_key_impl<Tag>::template apply<Sequence, Key>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::at_key_impl<Tag>::template apply<Sequence, Key>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct at_key
            : detail::at_key_impl<Sequence, Key, typename detail::tag_of<Sequence>::type>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename 
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at_key<Sequence, Key>
        >::type
    at_key(Sequence& seq)
    {
        return result_of::at_key<Sequence, Key>::call(seq);
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_key<Sequence const, Key>::type
    at_key(Sequence const& seq)
    {
        return result_of::at_key<Sequence const, Key>::call(seq);
    }
}}

#endif

/* at_key.hpp
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
*/
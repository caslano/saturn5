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
tGuk6vR31FLTaWmw63cLWJp2YjK+470K/yahhwxAVlmqBA7Rctfd3aYtMl+J1AQYZXyskxpjXJAUvj7FbyWIE1TSXxv449KU1aOAgf/cuQ9c3W36+OlSzxQqBO8JY779aJ5YVIkdbDLj8f6rd9RXMrxPBnAMIgXEZv7ZIwQucAWopLf59+01Fh9IXRcTLKhEFe+dsaKmA0CTycCs8RF7CeZ3sXwXcqayJnbbNfIdnk+wDmIbZbIO+Q+hDwIvj9axiS0KOLJtZ9UiHSjnVIR96KerYBhC3YZdxVu3RQNPusJh0ZSQeDaJR9OP+SVTnbrRlwPzDc7+eVhAzMJiNn8TzoQx1fnGJFB2BZt7F4Pw97ZuabKB1rkYWSofsJfqYCeE7IFaMpY2QbH3ZkTeESu7yCKl9x8c8Dq71DEa2Pc4s3WjFyAYO1p8SmI9kNRhVk08+ew38l74Jvyg+zX+Xmwd+B/xPS1eQH3AVCo1Z1IMjoPKlVs2lEq4Sy2Cn82imVhuKs53Ys4Qml28ldPiXyYzvm9prRFTPRZ9qf7uqiSBVOQh7Y2T4J/C05czVg==
*/
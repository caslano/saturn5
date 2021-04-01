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
DjyXF2hKWD8RQk+qqpgZTWL8Ust033ASCG7qmoF/Bx7GbvRzR7xnQb5j0vp9Udna9st8VlLzMkvY8OX9G/492v3Axr5lKxYYwpRPb7Pob1c98gXVg8EczUDtOC6SJeicr1mlJop2KDAM+PBpzNpofpAbUQKNGwB6SNq2eiVJfZluu9t6gXn9IxHrL6X0mIDwO+3gmioZO83UXHAj7GbKI8LlOwY7WvELDw/JYO7Z/vAcE6I60fQAaGIclAOzqs+RcUOGrMx/KAchBXZS+ghiPLLxt9RClIcUbkBGO7B1bV7c0AfwgDdnaKO1er+zH40HqBgdm2ObnNqeXF5g9RQplN62mNFHXH1P8+CuZxNYU1C5noVr+MziF4OCN1UIuUmMQQDaX6D9jg/xCPi5nGRoZvz84ABa+q8ZILZJRRw7EXgANBXEh+23T/7THNMCUgykYVDva2VctKFUSwrb7gWFzUONwfB1ifR0PueKZ/N4Y4WyZVJAoWfrgSZkFjSSu+csI3whjYiemrUMdiXXBKfmq/rbFpMtNe9GlQA1PjCIU08D0TWgW7g172tSjQ==
*/
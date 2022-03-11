/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEQUENCE_INTRINSIC_FWD_HPP_INCLUDED)
#define BOOST_FUSION_SEQUENCE_INTRINSIC_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/support/is_sequence.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <typename Tag>
        struct begin_impl;

        template <typename Tag>
        struct empty_impl;

        template <typename Tag>
        struct end_impl;

        template <typename Tag>
        struct has_key_impl;

        template <typename Tag>
        struct segments_impl;

        template <typename Tag>
        struct size_impl;

        template <typename Tag>
        struct value_at_impl;

        template <typename Tag>
        struct at_key_impl;

        template <typename Tag>
        struct value_at_key_impl;
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct at;

        template <typename Sequence, int N>
        struct at_c;

        template <typename Sequence>
        struct back;

        template <typename Sequence>
        struct begin;

        template <typename Sequence>
        struct empty;

        template <typename Sequence>
        struct end;

        template <typename Sequence>
        struct front;

        template <typename Sequence, typename Key>
        struct has_key;

        template <typename Sequence>
        struct segments;

        template <typename Sequence>
        struct size;

        template <typename Sequence, typename N>
        struct value_at;

        template <typename Sequence, int N>
        struct value_at_c;

        template <typename Sequence, typename Key>
        struct at_key;

        template <typename Sequence, typename N>
        struct value_at_key;
    }

    template <typename N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename 
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at<Sequence, N>
        >::type
    at(Sequence& seq);

    template <typename N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::at<Sequence const, N>::type
    at(Sequence const& seq);

    template <int N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename 
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at_c<Sequence, N>
        >::type
    at_c(Sequence& seq);

    template <int N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::at_c<Sequence const, N>::type
    at_c(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::back<Sequence>::type
    back(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::back<Sequence const>::type
    back(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence>
        >::type const
    begin(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence const>
        >::type const
    begin(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::empty<Sequence>::type
    empty(Sequence const&);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence>
        >::type const
    end(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence const>
        >::type const
    end(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::front<Sequence>::type
    front(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::front<Sequence const>::type
    front(Sequence const& seq);

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::has_key<Sequence, Key>::type
    has_key(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::segments<Sequence>
        >::type
    segments(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::segments<Sequence const>::type
    segments(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::size<Sequence>::type
    size(Sequence const&);

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename 
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at_key<Sequence, Key>
        >::type
    at_key(Sequence& seq);

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::at_key<Sequence const, Key>::type
    at_key(Sequence const& seq);
}}

#endif

/* intrinsic_fwd.hpp
+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
*/
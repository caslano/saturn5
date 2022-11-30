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
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
*/
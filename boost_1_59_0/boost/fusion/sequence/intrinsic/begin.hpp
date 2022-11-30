/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_04052005_1132)
#define FUSION_BEGIN_04052005_1132

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_begin.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag; // iterator facade tag
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct begin_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_begin<Sequence>
                  , mpl::empty_base
                >::type
            {};
        };

        template <>
        struct begin_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template begin<Sequence> {};
        };

        template <>
        struct begin_impl<boost_tuple_tag>;

        template <>
        struct begin_impl<boost_array_tag>;

        template <>
        struct begin_impl<mpl_sequence_tag>;

        template <>
        struct begin_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct begin
            : extension::begin_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence>
        >::type const
    begin(Sequence& seq)
    {
        return result_of::begin<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence const>
        >::type const
    begin(Sequence const& seq)
    {
        return result_of::begin<Sequence const>::call(seq);
    }
}}

#endif

/* begin.hpp
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
*/
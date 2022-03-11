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
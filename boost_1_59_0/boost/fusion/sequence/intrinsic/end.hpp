/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_04052005_1141)
#define FUSION_END_04052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end.hpp>

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
        struct end_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_end<Sequence>
                  , mpl::empty_base
                >::type
            {};
        };

        template <>
        struct end_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template end<Sequence> {};
        };

        template <>
        struct end_impl<boost_tuple_tag>;

        template <>
        struct end_impl<boost_array_tag>;

        template <>
        struct end_impl<mpl_sequence_tag>;

        template <>
        struct end_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct end
            : extension::end_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence>
        >::type const
    end(Sequence& seq)
    {
        return result_of::end<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence const>
        >::type const
    end(Sequence const& seq)
    {
        return result_of::end<Sequence const>::call(seq);
    }
}}

#endif

/* end.hpp
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
*/
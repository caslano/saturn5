/*=============================================================================
    Copyright (c) 2006 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEGMENTED_03202006_0015)
#define FUSION_IS_SEGMENTED_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion 
{
    // Special tags:
    struct sequence_facade_tag;
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::false_
            {};
        };

        template <>
        struct is_segmented_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_segmented {};
        };

        template <>
        struct is_segmented_impl<iterator_range_tag>;
    }

    namespace traits
    {
        template <typename Sequence>
        struct is_segmented
          : mpl::bool_<
                (bool)extension::is_segmented_impl<typename traits::tag_of<Sequence>::type>::
                    template apply<Sequence>::type::value
            >
        {
        };
    }
}}

#endif

/* is_segmented.hpp
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
*/
/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EMPTY_09162005_0335)
#define FUSION_EMPTY_09162005_0335

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct mpl_sequence_tag; // mpl sequence tag

    namespace extension
    {
        template <typename Tag>
        struct empty_impl
        {
            template <typename Sequence>
            struct apply 
                : mpl::bool_<(result_of::size<Sequence>::value == 0)>
            {};
        };

        template <>
        struct empty_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template empty<Sequence> {};
        };

        template <>
        struct empty_impl<mpl_sequence_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct empty 
            : extension::empty_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::empty<Sequence>::type
    empty(Sequence const&)
    {
        typedef typename result_of::empty<Sequence>::type result;
        return result();
    }
}}

#endif

/* empty.hpp
+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
*/
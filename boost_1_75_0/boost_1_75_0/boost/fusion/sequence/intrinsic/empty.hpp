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
P8wTseigP0FaYu/mSNYyAer9mORAUXnAF79ojz9ZGTSA5Gb2AI3FYvscFK/vB8GsDwMLmHMPVI2BUr+A3q2Hx8pHWluS4IQhvznW1qZ8gkMP1l6VTfvVGs65hs8sVrJdeSqRaHMJXl+UyJ3Jj/A6pMAp1ddJYcAmOxTrQZjUjW9Rzds+WFuibhyMytjndFuzsXO8idv7JLVvBT5D13ZUrzdcakJt8N3BtAxKIMvkzisBi28Qi1ozd3DKBerXYmeRe1SgEoaY9Xa8Z9a/OIg3MgYlU8kCuO4Pj6qtp69NNmGz1dama/kMXW01D+JXFTaULg9W4qzbAm+l6nhzXKvnLOXadUkIZny6/tAMD7vqD+HDrJEwXaso9kHX1/p2A5ZVOhlGXQ3NLA3NLQ5Ck9I3sRrC8yQ0rzymOXLBIs96aBDHM0vD8zHCzLptEOGZfy3i1sfArYeBW99r2+PWC57xNKNdQU1MmQGqseLlEGeR5UfPqndAtR8dhKT6pJmUbgqMVudywKLq0CA+ow3iZnxUw4spcpqHkWNajodniyjBmyy0i92FS7u/UHV3RdPk8ZgbemsBev1XbM2h0uYoWRRgrntMay8v2t4Uyu8YbY9iFk1t3d5w+EytDqhxcz6kFu+msRJ+tEXlcTM+x/UX6hMSKBTjNG0i18uOunGb5NjWghqA56Rb+KBZsrRIwVnkV65ux9qnIjjdpewzqCcC
*/
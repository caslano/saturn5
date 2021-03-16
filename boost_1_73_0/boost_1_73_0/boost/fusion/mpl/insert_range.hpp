/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_RANGE_10022005_1838)
#define FUSION_INSERT_RANGE_10022005_1838

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert_range.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_range_impl;

    template <>
    struct insert_range_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename Range>
        struct apply
        {
            typedef typename
                fusion::result_of::insert_range<Sequence, Pos, Range>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* insert_range.hpp
6n7xu8/JU/H1NkjaNz7KbhAPKfLGlTkK4i5WbLyRf1ROkUBTimwPsi+CYvvEyVT2DkGv98pMrm/lfZMS/P7GHqeV6u/n8SQlnm/seZSl0XcWHdyl4dykScSlU0rG3TxBGUOQ4xwMx6t6m5uytY69ZIPTelZ8dFPGdqbeY5j3wu2Z+rFEWcg/w6B8N8v1dvjofETc+muiTVj2rfJaynib35LxbRJtaZyM8yc9f5GbjH9oh4iV8U/DMu53xsn43BM=
*/
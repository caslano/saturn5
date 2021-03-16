/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_10022005_1835)
#define FUSION_ERASE_10022005_1835

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_impl;

    template <>
    struct erase_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename First, typename Last>
        struct apply
        {
            typedef typename
                fusion::result_of::erase<Sequence, First, Last>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase.hpp
nm5P5sMwjv5rKledKXy1JGjsQ/+1VuGW+nk4srVcS7LdDnvBsFvFX+7FBtnT6ZRzIt1sIVlEOPXBDp16N1m9y3+Febqr+x2d9w6KisvOHV2eh2GKfpu9PmwGSc7d7SQ7kpxlrw+bba8Lay03Jt0+0zZ/NSsCmwM2F+wRsMfAVoCtBDsOdgosxWFYU4dhIRVCZPLft1ScSJqeVr3RngmdU+3aKDUiomLQq0L2X3XJvs0tVXBl+YyOrmGVJUPpysI=
*/
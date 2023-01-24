/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_10022005_1620)
#define FUSION_BEGIN_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/adapted/mpl/detail/begin_impl.hpp>
#include <boost/fusion/iterator/mpl/fusion_iterator.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct begin_impl;

    template <>
    struct begin_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef fusion_iterator<typename fusion::result_of::begin<Sequence>::type> type;
        };
    };
}}

#endif

/* begin.hpp
c07qtVVgQJl9OniToo9S2kYm7S/r6bX6oLR9QoMizBtwoO6p2fZ8gsrP+OHGaff2D+xjkifm3L8oytOYlwEpcU5ujM24Jz8RA2+nil6m2UFBHFTRs6b/69Qp5RoOx66s/oRn8ZcmY9rY1bXYN2/En8Zuw7+lldOEKClUraMJs9QZCcs0W6Go5CWTzlKWb0+gTlMzvDeaqrzGSX12xedqmv0XtgMhO3NJOUtb4c+K5nhL0AI6dFf80KGpg5LIWrMIvsPHPfBB6XTKwkyjMJvA4Na29SpZgE5Z2RL0KX6qrzWcol8j4MGN4ske4aI0uBRZr8b50iaEmiLg5b7bDBGznBEQ0U0kh0xCGvHTetL2oXf/IK9jQRpDr0qZRTCvYALC4ptaADMLTeBwQGanmBndccIqPdlXRckk+9CMApEgXQDbVn1sJieVUhCC1pfTS4oy3QUVAwJXwbe0aIbsKMlE7IkmDIKgG6fhR8tyUqzCRbj20ACp+l76fQx5htJIxc62zKJ8jguyuM1Z7FZIL9MbaVdf7hZrZKnRSCc30i4a+fFH3Eg7NnIvTYOpOfQqwrsh/5itJuG1tU8DGiBs9vp/i5VRaviqlOrOBP+rPk7p1MexXfTxavRPxGCnUva0Kqf8T88zBPBikUAvT8w33erY43uYYPvVVzSYJ5jDmz4b1T+Iz2fgU58rcVjium77LPBAn/LzNFfl6gGm4AS/
*/
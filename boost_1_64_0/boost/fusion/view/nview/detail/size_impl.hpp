/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NVIEW_SIZE_IMPL_OCT_06_2009_0525PM)
#define FUSION_NVIEW_SIZE_IMPL_OCT_06_2009_0525PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<nview_tag>
        {
            template <typename Sequence>
            struct apply
                : result_of::distance<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>
            {};
        };
    }
}}

#endif



/* size_impl.hpp
d/5Cafw0Q17xnoLcPhWCiWjAHkuvkanYN6CItu1OJKoyYvDsvwIhtVJm0xd4qiw3plyUP1OsFNiJGPkM/Ga+CVFp9MOB/xUxD+CQibWdy/DbjK16Nsoj1DzMuB0dZYgKCrp1Jygc4wcqNcCVv7INeGBuYPODrJPTpENjerPtgl6njULnBBlOK90a/9qLUHKFXALvFescMEG00/fdfptlYV3id2dI3arVjbLspuQTGvoe9/PEHfguv0jjrFeaRhIKY9DRwgGUowelugyf5FTpj++rcnjP0UbKBUsF/fBndkRyyH/4L+/7N5tSK6FAA2QFddvWjXyvBuRZelZTZ5Sb8PHCz3YLFbUYGHvOLzaxfKgh2Ro+jtCgYp1VI3YLPwojGLT3nMvsCY5a5UIWkGhRaT4VZve0NoeTpFSF/gGqBuV6N+6pOEjmcysG5uiedRiPaAp1iCYZugYeu7Azgl3lazCabWNvm2cqxerJDvTi23bPZYfZ2HM2o4lOrEmm9kXfff4DOE4daOKVuwR15L4AJlPHAdQg8dRy9nludvoHJyTOh9K7P5OUpfqsOQ==
*/
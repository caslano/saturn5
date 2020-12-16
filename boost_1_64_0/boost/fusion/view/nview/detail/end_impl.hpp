/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM)
#define BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        // Unary Version
        template <>
        struct end_impl<nview_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::end<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif



/* end_impl.hpp
kqGIzaPckyX6PbyGA78s73CYCb0afrLOueIV1HkPufsZP/IaPjAE/J5BVjY8SbrwOg6M2nyGizJEYL5Gey0V/Q6IRHkNDxgCfp7TLRumkQzewIHSKVm1JvQq0fOhWEXPAyJRYsH/FhiEDBzZovfHJhxYcuH6KSaXV6rt/UEUSuz9wTCwvdXB2aL3xZs4cFfVmG9NLq9Q2/uCKJTY+4JhYDGo4mz4NMWUwVs4cPm5Y481uVws7rFvVlHPJeQeYPzI65LKEPBzm8OzIZP8hLdx4JZRGaQHl8MekoFDpQxk2gMbA9eDI7NFvUvDBq7PzqXowmVibXw4RcFZhdnP3hlq8Egs+90CCc8NWpwtan+/gwOr9i8qMqGXQr3K2t82mfIKX3McvEcIyuF6ksO7ODBywrJxFHmDrdQ/ePkBAN2lyyHsMn5k9otjKGL9hTXZMJfk8J6Gz4x0OuNeJGJOxUr21yaREk+vGAa2Vj6VDQUkg/dx4JPs5+eZXF4MxbRWlsWrsA9Eobu2Tq4ITAQs9vhCNvQgGXyAAzM7zLndhF4E05OsPqoq9lEmiRITahkG5je+lg3dKMdhi4ac+x95x+TyQuEv9FSypyYKPd6grJBbFAaeZ/5Gtog7fsjijhdAhco6SEShxKgjQ8DmAsrAqvu4FQey7thN2T7nw8I4sgcq50KNrFqADAHPkdySLc5vP8KBIaX3Un/x8+Cn9mQPVOSVE4kSo64MAasJ9lU2PEUy+BgHzphTcyWdSoEnjWLwyQruaVskyncRBAZhE3/IFr3zPjHijPOzSkwuF0AfnfwDlTbRL89bjMLAc51+yoYJJINPjf3DuxOpjse5MJT2D0nxKmXQKKtoQSyGqBoe2VBEcaXPcGCAPpXupp4DGe1pLiQpqAlnURhweSXVrmAYmAza5cDLtI/83MiLvbk6ZHI5H+I7UlwpTaEeBMJhyXogMIh1oW8O7KG58AUO/HDVzDqTy7NhBfmJm1X0FbQoDNZJ3i6YCFhOT1kObKDY2jYceGPl8j0m9CyoJz1YmKag3z6RKLPHNkMR6yedmANh0oUvDT9pa9wcE3omOPT/wV+WVuWJIeDnLtNyhL+8HQdu8nWeQlEU2JZAvmKiShnIulPDEPBcBV8OnEn7pq/weXWyr9GEngHjyF+ujVeQ42aRGHYFJAtBYBA2oSEHniIZfI3Pjy9fvsbk8nSAdmQX26mUgbTaDQwD2zvOyoFaksE3+NwY98HdJpdzYal15qDST5K+PJoImE2ckwMusgff4sA93tkPmtA5kEFzIahSBrMG95e8QJoYWE+dHKij9fE7HNiwawHVNToN1sVZfXcV7psMCiXdmmEoYvM8z8+BxX1NOewwfOY9551nQk+F9VYdDxU11sNer8f4Q1IeW9TreU2fHt3gIpoL3+PA09s91Hd9NiykWFIaPpOU8S8vK4GhiPUXD+wGp5AcfsCBiaU/vEKRNFhKcgDFcqiWFE3hKLgc4KBuoq7NjzjQ2d/zIBM6E6b/P/ogLUODoYjVB5RDJcnhJxzomn9D0IQ2wYX/jz4E5OuDiYLlbqEcrLPIn9lZZKPaPsQIMn5K5J1EMgxsrezZTZxN78SBPbt/oR4MEVEzuCxZQbzdolDewTTDwGIKp3aDu0kPdhl2YU6PpSaXYShPIp9JoQz6DRwkVQL0fttP+NTmfzcO7DzoGdo7hCCV+O+ZoiBHg+gbWNJPKv/4fv79j8iFB4j/XwyfOfPK+0wOZ8B1KcRssoKYUjgUxB+JVbMZAn4OX5ELjSSDX3Hgw00ru5Lmw8psqsOQrqAXi0mixArJDAE/c5qTC8/Q/vE3fG7zHkBnTgFY04H2De0V7J3CEZc=
*/
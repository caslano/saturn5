/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1215)
#define FUSION_CONVERT_09232005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/build_cons.hpp>
#include <boost/fusion/container/list/detail/convert_impl.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_list
        {
            typedef typename
                detail::build_cons<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type
                >
            build_cons;

            typedef typename build_cons::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Sequence& seq)
            {
                return build_cons::call(fusion::begin(seq), fusion::end(seq));
            }
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_list<Sequence>::type
    as_list(Sequence& seq)
    {
        return result_of::as_list<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_list<Sequence const>::type
    as_list(Sequence const& seq)
    {
        return result_of::as_list<Sequence const>::call(seq);
    }
}}

#endif

/* convert.hpp
7fbzGO3ZGJFiXc5ilhBrV2HPwGSmy1iOH2zncz7JP9KYJZON9TjWq02newlaCPNONiHe3MDmPMm62FbKw1Jh78ciYd/RJmEPiaZAKYv9igW/XyVxXJGwd4LvWUX+IfMHcFywrBDTj+Wo3YzTeN2ksJDOdU9l+ovnupMLuc7u3MTTKZuobQ9+gfMwhvnzGdazwjzkQInLtIWwbtVZSEf15fmL+gmy7s/ztE3k/Qp+xo7ncytofM33jUtsjx+VV+g2Okc3Q9zvLbyz0F+II0wvKDYT+a7COnuEML+3/LCy/ojjskji8yRZJ7BYG+vCYz/QNam2Kbye00xfSPyl5Lkq2N6ayZy2W/b+pGUj3+uy/gfqa3n15bRtjeNlzyZw3q4by9OjhXXnxcKet6qZPE/5zdt8LBAwzPfDYAyfK+R7ToqF9FeF3McIF7C07HuKHx5rI9vL6EE+0su8LZuwRrZG8JltfTidGySOmaJBPN1VsO0JU3h+ccxansrTCcIczuBUu7G15/cUY+NZ7IxxpT2vIvFU+0l2MjqzmsYsvYV1vd7C3mDN6/x+wHylLJHp53QcH5+m3E/H8yTfYx7i9Fcbebp2I7fJFzdQe3J1pFIW2+Gde64R/Pdn4xfeP1nbge+fDNlIyy5+mutIwGiOpShhnTqYpXOsCcI+NLu9+rG8nlt9eN+9+nM+D2f2PNbq9QyvZzmzvTiGNb6L51FR
*/
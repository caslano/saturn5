/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/plus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<single_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::plus<typename Iterator::position, Dist>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
ZtOnn5rTExXpjUyX5y2TbHt6Vuq/XToZrpw1it/2IOc7px3o0lMt6Qbw9k/59uQRFcrc3ZIepBaI1umTPm2DGhVVjTbpK2qp5Ne9HusXQRWIDEadtDDPW8i+9cnDuQV5De48OSwscB7PkKMulTFcpSFfzY9b/323/HgR1Mg76TO/IfKxs56XrCiezKAn2NM56OQl5PIt6X0N0u2r9sz2g13Y0im7KfYh6prSumP606mfib/KZHGIJacg1/y43628FnKiRHd1es46nYM67Wf+/sjvtvIpb+lvhiMe3OVPztrzId2KMZ0Xzg0Vizx/Sgxcy0IsyZLssm/zIV9xVFo7aaQ6/T9R5ilfrXs/pJ/jFPdP1GferP7b6O7s6U5Msr/tUV9tJdWQztQt3f863Ygq/Ru1mjyexq/f0r8UyR/a0n/Zj1H5uiq9Q+KZPenZOr3RPUmb+/ejrGmX9viW7lKp+7HLfxmSpE2Sb07voUqnilx6ld3fMVmdRV7HEmQ017v8OFq8f4P3VwR1feIL9qNNO87zrtJXrHEL8iB9sgq1fPjmcj8a+RWt9B/abb28vyl5L7NOE5n2VpFQnXyu0/6uaQUypXV6okm5gibtwqjz7DOE/ibuQztvmb4ag6wX9nRNN3QP5+smPeUkr/GWPr1MT7gn7Uc2t8j2t013p06/XabfrcP16Vo1qiHthmssc9KtZfq0PmnPKpOv1b3h
*/
/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONS_TIE_07182005_0854)
#define FUSION_CONS_TIE_07182005_0854

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace result_of
    {
        template <typename Car, typename Cdr = nil_>
        struct cons_tie
        {
            typedef cons<Car&, Cdr> type;
        };
    }

    // $$$ do we really want a cons_tie? $$$
    template <typename Car>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<Car&>
    cons_tie(Car& car)
    {
        return cons<Car&>(car);
    }

    // $$$ do we really want a cons_tie? $$$
    template <typename Car, typename Cdr>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<Car&, Cdr>
    cons_tie(Car& car, Cdr const& cdr)
    {
        return cons<Car&, Cdr>(car, cdr);
    }
}}

#endif


/* cons_tie.hpp
OsM7YCWoGWEiqFE51BDrcJf6lMWA9AHUJJk0qOEaMRG5Bqhpb0KogTZCdKWXpYSpNIQaOo99oYZesAQ1+gx9GeF78ln04sFAIuijzQBZDDWr/NwMcx+Px2HtvMuk8UHz+cPnfmhehNf6kohLMHbFqEshQE2k5RrTuBxntNc67HMz0vryNPtHLDKFRxYA2heto3v+mh2b/DU7DhnTDvmmVRvTqn3TlhvTlutpuprP25/xAWcbs2b7VlOj30iPfWbWaK4413rSeJ6k8qR1elIaTxLUY9KXMRCzqdly32YrjGkVvmk79Mp/+NTswzSoMIJGhS9oyKKYYM6Id4HOalr6KZ+RZGPzyXrztQtC9RMso4832PtP0EwjAmv7+JxkPkQorzWWD0ncIv8tNFZsCgCNq3hkgZEnYOzs/0uINDJW2D60bPp7YHl8Y1Cw3LYxKFi+u9EIlpma5bL/EWDesfHvA6bFFzB9ALGFLyDim8zTjnz86Mq6PhZFgZkLHOJpc0lCN8kcRAOL238+EMkN+DxzALnHThaAKG73b/Bnh2/pZ/w3FMZSdDiPvnQMf9Ydo5+/8/Bnij5OwSGM3aV+fZTCHfBb3X6U8n5CmT7gRVfRzzf5zzP/wZ+/UfAzBLvU+ccwmMvzPMFrKqSiUyi4m4LxPNMoHg7l4SAeDuSFFVa12pNHduPhNbzHbaiuVjxvBE/20mRcPEI/T9LPWj5V
*/
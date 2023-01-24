/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857)
#define BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_iterator.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<map_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef map_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
oj5ZTnj7GIcPl2P0/RSMLSftjdvKjXtgkn4P1J0Z3POtjtCkznzM7IjLOEmeuNtMr25lelVcJaZFoSTJ4Uw7StSAkOjxAYaQ6D8k15ifikKic/HJH2OWDpZyosXHSHDZozYMIRHMzAyHRcb9kE0imN2jdDnRJmKdcwutctZvHyylRWW1PrWSq/3tBlmtTw1wtZ9ZTdKiYZKdc4u52lw1drAUGJXV5qpXcbVz9Wpz1b5cbSlXmyulc2W1hV5pAnfJIKoyT68yTz1wI1U5UK8yT/3vEKryGq4yT3oRk1X6PcrQDBCFX6AvwYiyvMXi3JTeISCEKwaYFEjClTA0Uf3mmE03q5vBhq9IJ5yczJDqZYC3mSs6EFxvIlKhyUzIqh69XO5wUqUJF9DVd6HA67awhfFEL8eZOFisJg7vfz3oSEPjviZPB8bFedNkwoP7nkQEuJuC2ygYScFrkzF4aTKfcQY+kK8C28ivdHyAO1WW8l2OdNYGKME6QLwnQ7/G5sXpW6+hlUC7gUCPwWDEoRmjOEmoncYZIlh58aVAho6cIYLVHLFf1YMd1mnR68vXFyWUHAftP2f57zEWw9xY8TYyFPBtjEXXfgeHqE+w3zKARn013QHShuO8gdEdPbw7qsufijWceZBzgLJkPFUD0lHx1Dtx98Otmdzdu77Ob0OwZbjXADvxeoDJ38fdb5M/FeC4Aww29PBSGdpbaUjQ
*/
/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_KEY_10022005_1851)
#define FUSION_ERASE_KEY_10022005_1851

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct erase_key
          : erase<Sequence, typename find<Sequence, Key>::type>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::erase_key<Sequence const, Key>::type
    erase_key(Sequence const& seq)
    {
        return erase(seq, find<Key>(seq));
    }
}}

#endif


/* erase_key.hpp
IIga42Rx3bh8nvgisF0G+7RVRps18vZYCHl7m25ftZ8zMOAg5BXEYSDVFzHHVrXGRONVdVJZlZ/IuPFnxlEZiowUJ822dIlHUhyxEcR38O3OQf6BqmS3sirZC31ZlSxbkGHonDNX2ZWr5DvUmkxSJdsUSyTxQZ1aPrTQqrVvJGMFhtq5EK4c7R/+dho7D7h7FZJ77/GMEMBCBLSdlO8T+YF7wNXKHQL/KVZBBWKMqw0KUL2qv3MsKMf/DC0q+5E6vgw6FN2cB2t7Lfgp2aL+59ZkU44/x5wfXX+lP6kf+L3be2syNRe0X4HdnQi+du9KKxRwBX2PN2tzR69b5Q2KxUDCpzMJn8kkfDoSnN0WogzqvzD2eLNGwv+5QCfhX7EYP9i9QCPhQRSgkfDpTMIDHQudokAxXqSmIc92Nt0aIEENfUBrGKKl7f+Koxu4QjVhJc5xF6NoqB6nm6jrR0o06rqQ1+l80SMgrHtYThm+qr8oWiNB0oV7UPsihefHwfODwkj7cT+LukgSWO/toud9LvJcD61v2hcKO5rwi4AdhF+IfStiDMVI+CXvo6A+F/iCJl/PuZrYa6z4JuDXB3CDnzzBDIsJadJWWQzGndpeQ8N1sBXVv3TwlykxxFOFxhq6gnOPRxsH/+t8GOBGuCEYx+ZBcp+QAcpev1XbUFX1uTb3FpDGHDROaz0vxDZeiHr88Pn5RgOgyFLGOVAm
*/
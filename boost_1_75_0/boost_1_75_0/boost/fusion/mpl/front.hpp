/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_10022005_1618)
#define FUSION_FRONT_10022005_1618

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/front.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct front_impl;

    template <>
    struct front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<typename fusion::result_of::begin<Sequence>::type> {};
    };
}}

#endif

/* front.hpp
S9+evkyW1CGJWIzS3DFIIrqCOAT6CflNojmwpK1mQ5DSg/lykDT/EtOmmIojmkwsN8g4FydVHU1laN46jVVWXMDzLojeR4UgfEqPNosdo1R96iwuttnZTv5Zca5VExXAYQHYKN2KqwR1ci5FA/nVufQ2Cg10K+dRMi2/OTbXZWSPVLwXNUhkLZDV8c+TZ9ZyEh5uVpLOTguPO4sMWY82BMG1226UVehIqU9T2ciwXqo++TXP0QoxRzPUlx9Hgm3lK1Rm4NdifhaLOl9vRGE4z3gNLJY/wSWtoSWfzuMTxMUIXGTPpBRynaE5WCnmoP1xthlsJBG483GCZqL3ZIc4u088yZPisxaaPida+Od74vOdlg4jXjg+8IwnypFJxkRBrgSStAelzUWwiROH14mTE8vRoU76ljFUSllFhXNkkJUlxKreVhw0qoHkyQpjJwO5fD/rP+Lk0QpDHq2IyaMIdIXDTZddb6M86nKcTxRJz5Oi+Tss4sQ/JeI9JfCe7vp73LEXlRgvKom9COMSMIk6XfbAK3q7xDu6efAlv6WDhpDpjB3yafotlgonePQJoVvfcWAOu9kCcC/iVBWCwCo9usUcM6+qj37Ni6HcuFJ+plWL1fSYkJ+EwQcKxuochEce5XO3g+UxKdSfJqjG0AhGuipsOcrWLuUdWdQDm0Sj6MP6WB8Oo8aMaVmAEhveQuA5hyGfPbOc8sxqtoY9
*/
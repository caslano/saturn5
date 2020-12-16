// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/value_type_of.hpp
/// \brief value_type_of<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_VALUE_TYPE_OF_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_VALUE_TYPE_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::relation::support::value_type_of

\brief Metafunction to obtain the value type of one of the sides.

\code

template< class Tag, class Relation >
struct value_type_of
{
        typedef typename Relation::{side}_type type;
};

\endcode

See also member_at, get().
\ingroup relation_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Metafunction value_type_of
/*

    template< class Tag, class Relation >
    struct value_type_of
    {
        typedef -unspecified- type;
    };

*/

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    value_type_of,
    left_value_type,
    right_value_type
)

// Add support for info tags to value_type_of

template< class Tag, class SymmetricType >
struct value_type_of
<
    Tag, SymmetricType,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        ::boost::bimaps::relation::support::is_tag_of_member_at_info
        <
            Tag,
            SymmetricType
        >

    >::type
>
{
    typedef BOOST_DEDUCED_TYPENAME SymmetricType::info_type type;
};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SUPPORT_VALUE_TYPE_OF_HPP


/* value_type_of.hpp
nL5aDh1z+HZ3fzFP91STrc/xLbLvEVrxfFPBfq99o6g3aLe3id8O6nZMyztCz4/e5hKx/RnDfa5WGa88P1S/YdPue487op/VL8p9l/sj+4rtO6zcA9lX6q2XrGlmX8D76ju6Lv2vOFEW/CHc49b1O7RsNP7tof662nUnfyfueqeU+j3MaRH1/aFlRMN1MtlaRn4j7m87Ffwdzf1pWFZypWyEwx10lvKl9CXzBE+iSxp+e9i2ZtGd8gxynnCf63rf+93FPr23Wo8rauSh7LUBuyTcNnOhGaNtCC7Z965px95rzZCGZdM+G1aJv674S7XPhs2y78cmz0wyV5mx0WG1Hrwl/haZLnreqb7zns/eWjNE7EsHUZ9T2xJa5g9bd0n4efKe93wUP0PxUyt+6ray1q59ll7WXkT8huMrxu8K12/autxwfMUan87PYcvulb6yvLKJ61K75bn6rshnVEGD77HCqO8x/xrV0evW36fr/rvlpz28EK5127W7bdmNfE4Fr+2rYbqZXL0X08Q93MnnbwnyCBLQ3mnYziZXy/JUGzbJlCCPILHaviIbtqPJ1fozSdyjeA9Dt488jvjaOVtGnxJ/L5mR0tb5nkkl1QuXzq9YRoeDfWdruRW/9I5kmBb6DSH3TGRVrvd7dRPaJb0nvnVNm94O+ee0Sc+Mnp/nm+6331b//Dy8UTJ3UGWlMbaMN2GOHf88QPdlxp6fyGxr+vxEZtvJn59oVPvodH27B6G3NVgn1QSvkZrnT5fU66an64mAdKVmRafrZfwWRKZrRU15YLrUb7avrlXVVtv64h237Uwz8tOmW/eNsGWRczS4loNZAWu2bmv6HFD4bXzN1m2ndg6oo/CY03wb1tg2ss2fm+jDM2XuoNsWzdid9NsfP7e99z9u3/Tp7cG2rb/Kd/cnbK/o0evaP47MPZbbrsOTl7/OeAixkb27/Nmsol/ftifthj9fvavbqHf/fXMHNdd2efNAd3+X1xakVc6b8omftPxkVa8ziu5t/lxJzZ3r6Y/emm7ybVxo5zjyftf4fq/w/a71/V6icx+9jKg9q/bd8v0UYw6eq5zQOoLXwe6wDk6CN8CPwU/AeXA9vA5eDz8OPwU3qD89j/ZP0ica4zwbdF21jbAT/DwcAG+Gg+Bt8Gy4CY6Dm+FceKue/zY9T6rt35P+RDlPV+RDPc83dR2/b8Oeus5qvq6zOhm+AqfBH8CZ8BCcr+uYLoRvwGW6bulV8C14LXwHrtN1Xj8DD8Ob4G/hvfD38HV4BB7W9Vj/At+HKaTzD7At/ADmwb/BYfDv8Bz4c3gxfFvnXPoFXAt/Ca+Fx+Bn4V/hTfAfUOy8bf+Y9M1JfvRBxofHEJJvWXAC7AUnwv6wUPN7EhwLJ8NSOAUugCvhFfBC+Cl4EfwinAZ36PHdcDrcC2fCfXAOPAIvhX+CxfBD+DFdr+4S2ApeCk+Hl8F8OA+eC0vgKng5/CScA7fAhfAeWA7vhxXwAXgFfB4ugfWwEu6Dy+ArcCV8TeNtS/5cCdvBatgb1sD+cAU8B67UcnbIaP+E9ovUq85mv5az23Vd2zthb3g3HKjrfJ4Lt8ECXddzPLxP7cG/COfAR2AJfAyWwZ2wEj4Oq3T9yxq4F67R9S7r4PPwZvgVXQfzq/Ae+BJ8Cu6Gr+i6mgfhk/AofBG2dLx1aQvt9zf9BVpueiOjHM++uzsshKNgEbwQzoRF8GK9jtmwVO3nF8EFWn/KNP3lcDOsgHfDJTpH2TKYwLmqYAd4JcyF1bAHrIF94AqYD1dC+e6C0+FaeCm8FlbB62AtrNN6s07rzXr4OXg93Ag/BR+Gn4a74I1wL/wcfAHeBL8JN8L98BY=
*/
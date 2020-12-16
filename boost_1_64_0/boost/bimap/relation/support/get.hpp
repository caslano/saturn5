// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/get.hpp
/// \brief get<tag>(r) function

#ifndef BOOST_BIMAP_RELATION_SUPPORT_GET_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_GET_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/value_type_of.hpp>

#include <boost/bimap/relation/detail/access_builder.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>

#ifdef BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES


namespace boost {
namespace bimaps {
namespace relation {
namespace support {

/** \brief Gets a pair view of the relation.

\ingroup relation_group
                                                                        **/

template< class Tag, class SymmetricType >
BOOST_DEDUCED_TYPENAME result_of::get<Tag,SymmetricType>::type
    get( SymmetricType & );

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES



#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Since it is very error-prone to directly write the hole bunch
// of relation accesor. They are buil from litle macro blocks that
// are both more readable, leading to self docummenting code and a
// lot more easier to understand and mantain.
// It is very important to note that the three building blocks have
// to laid in the same namespace in order to work. There is also
// important to keep them in order.
// The forward declaration are not necesary but they help a lot to
// the reader, as they undercover what is the signature of the
// result code.
// In the end, it is not quicker to do it in this way because you
// write a lot. But this code has no complexity at all and almost
// every word writed is for documentation.

// Result of
// -------------------------------------------------------------------------
/*
    namespace result_of {

    template< class Tag, class Relation >
    struct get<Tag,Relation>;
    {
        typedef -unspecified- type;
    };

    } // namespace result_of

*/

BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER
(
    get,
    value_type_of
)



// Implementation
// -------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER
(
    get,
    SymmetricType,
    st,
    return st.get_left(),
    return st.get_right()
)

namespace detail {

template< class SymmetricType >
BOOST_DEDUCED_TYPENAME result_of::get<
    ::boost::bimaps::relation::member_at::info, SymmetricType >::type
get(::boost::bimaps::relation::member_at::info, SymmetricType & rel)
{
    return rel.info;
}

} // namespace detail

// Interface
//----------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER
(
    get
)


} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_GET_HPP


/* get.hpp
g4dh3zVc83iuESlGapE7kb3IG8hRJGMCx/DXFxYhVcgmZPzj6Nbg2jUh3dHBCcSJlKruaB/762HWBZyX3zlX4Q/Jxz0LFsLVsBJuQHYi+5GcoVwX13z4gpCOyUxEb4W/eqQzv9+BI2D61VwzUsrvOqTwavzBSujXR+1m3072HRtKmuAbuA/DjLXs4/cgWIhUIVmFXBtcy/n3wFG434BzYS2Sfg3H4U5kPL+34O8o9S/jrpYmHylCKpGNyMPIvrviOq74Ft/iW3yLb/EtvsW3+Bbf4lt8i2+nbvuX6P9XLloTmv3vxOf/e95n699Z9f83OCE92SqY7I7/f0H0A65KYNysYtfGvmLRmrBOuafq9VdbfYf672R1A98W91LnDMeRMMVqC+Cf/+874mee09lRWwAbT1cJs7m9YZPT2HW0yr/qHr86QicWjjMbfl/ClxJniumHjqAl+yq53iyu9im4GX4F3grnZtDHKGzKOHTWlJBzm14Ll5VZPUGijtMmkbKvkH3FPXSf6g7OVl3MCNWBP0gkeXAzHED4bV+TvCZACfGUrKgqm1+LskzzwNPFal6r/542T74m7uudWPdmivXf396bl8X9snnIJOg+x/SRPu08ynJyw/tl53h4ScJ9wlFdr8bbW/SgA3vKuP+lVZevWBReeyYvYu2ZMkof+a1zMdS+6Ibdi7/O5gnOmin7NR2EIh0Sb0+jYUUVQ3i9htUSfo9JIM2PmaSY19GV+++eulu7mCL3nHvY6Joug3RNl/BYe+5HhA66PEYZqPKXAdVr58GB4s/mkdUrHXOar98JGPMQMKal+fqgAL1PwFiXk6cPujXD3T/1wetGTftg6awP1n72r9kzry8IGoNx8vRH/y69HreYdlzbPW2HU5HT+E2yZJuvY0EWwVlwCSyGlXARXAqXwOXwc7AWboErdC6ElXAnXAP3wKvgc/AaXQujjv9H4HqY4Op1YQr8FOwNPwOHwBvhMLgBToBXwpmwGl4My+EqPa7XpW0EbV6M6+qqY1oGwsFG1+CAZ8EJqruZpLqar6tu5gAcDQ/CMfAQLICv+8a2jIN/hOPhX1Rnlsi5L4Rt4TS9julwIpwNp8A5cBm8ROeEuBTeCC+Dm+E8uDPRmLV3tzT3IfuRI0jW1pau7uOE9UT78v9/dEX/a3qih/+DdEVBeqJBW1v+X+mKCrje0q1xnVB8i2/x7dRtSciyU/39r1+HJ6sP4EF3DID2AdQ5RrbNyGnK1J7sfzqiD2BR9cKQveOfethvTPtteLv4vUq/UcNhc9XtmKxnXLdjv8nuz+S9NqOhHN+GL2wDSRr0m0u+o+y1pGp/xnSkLTIFOYbfgmcirmXZwlXGXotpcC0Lxe+Z1m729xlN6yPwz13QOcXI9iv91v8WdNx+lch0YId8VsmChdXSlRGdt5KXGmaQuC/G/aa4n5Dv/Z+JzaXE4PWhyPHTbf/Aq+J+wcm0/qswJK5YvIyyoN/yGqavuGfhPiTu55xM+/1OGD7D/d/29picn4M65+Fq+GMJ/4yjYzQ0vHzGyzmWOdxD8XO7TVeq64fPY/+8kg886/r5EeeSdZJl+56Em2jXDXa3juJvibORr4Nce07yUaxbK2pKylZU+deCXSv++5kE/mXruunX6rkSzGK+bWZ6fUw+290ceLv426Fux4zdG5qbPlv9a35on4U3//1RSfcdjpe+kIm+L4k2fafJOfL96dNrLHASzBBzgfm5pO/iTMNGBMabt3Kv+EsVm/B0CvDbNFAPuTbe6cMSM1NS0ru08GzCH84ViepPa6P9aX+XNN/IOS/CHYqvIDkUX2Ld3cTWrX1T4sqB8yVdI6PyzY37bOJIx88jhH8=
*/
// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/pair_by.hpp
/// \brief pair_by<member>(r) function

#ifndef BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/pair_type_by.hpp>
#include <boost/bimap/relation/detail/access_builder.hpp>

#ifdef BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

/** \brief Gets a pair view of the relation.

\ingroup relation_group
                                                                        **/

template< class Tag, class Relation >
BOOST_DEDUCED_TYPENAME result_of::pair_by<Tag,Relation>::type
    pair_by( Relation & rel );

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
    struct pair_by<Tag,Relation>;
    {
        typedef -unspecified- type;
    };

    } // namespace result_of
*/

BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER
(
    pair_by,
    pair_type_by
)



// Implementation
// -------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER
(
    pair_by,
    Relation,
    rel,
    return rel.get_left_pair(),
    return rel.get_right_pair()
)

// Interface
// --------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER
(
    pair_by
)

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP

/* pair_by.hpp
fNtdtZmMyuMRvjxuOPa6UlUJW5DWysOEL33A5lnUuGtAji0OqpMaNtO2TZ9twlzMbUy6pOdNN6zaIe8L/e419aKR4t5r3SPEvdO6h4v7Pus+W9xbrHuYuDdY99CYeeW3i01qFWCH/GAz7JAfPHl2yOF0HWgV21634MGm2+uK32B7XY6fWnvdsE11kQ5e6aDrGBn4rlv2QtdiB4poBQ0cn8I1aZje9jnwSXFvULdjSsWGs31QfdXwPe1z4RPi/j3u8Pzrixcu871ffu5Bb073bp30eE2tXcOIvLBz+W/ifDcjrTKpX3Arcgdym9Zp2rtG1wku1HWCZd2Y6HE0ks+ro9tRSQNpY59Nm7WX3uI03y46wH44wC46yG45yF66+XbFI8X++YsD3zrwQLt7ej36wSvnbb3kr3cE2T8H2SEH2V03f57rAHvpAHvyYHv1P3p2PvIuPcioLbT3W94F6mEH5Ab9PQkRG7Xwt4N+e9VH2KhBtYlcAfupjVO+ugepu1Rtnq7QeaUr1b1c3dOJdy0sgdfAlXA1/AK8Tm1i3jH63gOHaDpydcywURu0nnASHKC2Z0PgVHiB2kiWwOlqwzdTbfhmwTvgxfB+tZF8CH4MPqW2kXvhXPgztRX8q9oKdiIxC+BQWAYL4CL4MbgYzoPl8EqdD/gzsBJuh0vhz+Ey+CFcDt131iprG6bPfX0HqW9gG5alNngdYFe1Ve0Bc9QWrBMsUPcEmAs/pvsXqFvne9ZnLL/1PP75noeoDdowva/DNV/HwxFwJByjbsScC6eou0ht0eaoey4cAxeou1xtC5eruxaOg1er29pWPejZQg0yjdhWNcFfqSvqr4MTla92reduWo56qO1lL/h5tX0/qDbvv1Wb92NwIDQO54UvJnLerf+d9ldx26tTa3v132B39f9kc5X6cEvTFylAqpA7kT3IwYfjdlHxLb7Ft/gW3+JbfItv8e2/e/vX6P+Xs/zeGtcE4IT0/73pwz+SiS7wJsckGFked+q0cVNKxs+YdMGsklnTpk6Ycf5F4yaIncDVucbOU3Wfo4oApL3yNfcjfpv0AxNP0bSpk8Z9rGTC7POnypK7MsdG9Lz52jd7q4Q705s7V9zZ6nbMC+J2dB4yWesbad78hHY+8Qb6lIKE6LlsX8fvm0HXItNAyxqoUXPgaPoJ27y5bA81SNsFmrY3E6Lm/pW0HWk0bXa58KD0Eb558wA3TN9kTd/6xOj0/Qi/5p5G0+cpA4PTSBwnlsbw/c1Lik7jG/jNCE6jTsMVnLaME0zb6PD91bTV6hrwy5Af4zcvMG0yxa6tR0bS5ek9J0i4i0y+cWTus17EfydSztnSU2eIDtmbe7dp8/i1MSPb1Uq8xvwwKzJv39ZMHaftwAjkp6SrPiD9uly5rTsHo/NWw3p62NfEnY/m1mm4Lqu97h+Kn16mHWmz9kOyr6PViX0p56O1FaoT862RGllHj6YY2cZrHozUPMi7t7E8sHU0KB80vJcPZ4u7v+SDt36yjcbmxUi1u7J5IXGdnLzItnkRvVb/jPA8dy2i69tbxFHXWH6UhJ55OKdOm1gyc9a0GRNMcN5oXMmSDzfGsN+YIn6aV0cbXmcGvDHadsGW/b2p0df5c/xvDL5ObVcCr4uwTVt3fuMJXNvx1p3vF9b1atdcjk9v/T3q/7bQ9dn18w+wzzEls3DrdYT95DRZB00cpEXjoL3ZdW+4vfnfmi+qufrS5s4vVSH61VELX/vkXWU/fazwS2blx4sXX3Xq55dqbL4oLaDyDDoCTyOO90VXqO95cKyOv2+h7ahR3Y9R3U97dYvOSXVxZ8E+cDAcBYf45s95U+NN0nj98+BM13hnwEQ=
*/
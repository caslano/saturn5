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
m9R77zq9VQwfxeTGBJn7wy/NqILQLuQr53ygD2oJx0L2tAtpV1bKLJWaGYRAUNfxZ2mIkButKciKZFqRloYBEfotIk376mZtER77gc9+dseEm1J8VcqEH0hqv5Oft8gM73AGh0wo4YQrOOel/Iz9gW0O9oONweQSsjFoA19JYfDlfspw6nt6/sXPuu+pgmsP0PMqfg44QN978/snkF/pzBW35dS3IJUamLyfkpZwhc9iAWU5FSjg1GlagRQucD9/2sRDWcvPt/j5Cj+X8RAX8tPP6X2woencUFetgZp9lCGCG7iDC4ziZ/1+1pFA7O/RgsBlRTu9OTGsJ5n4knPGYdK9Wwa/LtUk1zp9R5X3BL4QiEKs/VVinxxQVh0Q+1PKp4dErhMi+VDA3qpHOFhk5PaucATMhCF6kIcSVWBnDyXhBqDzW55PQvxZIUpUpRblAjWoUlq/S1L6X4itcqt0RBvx0c9EyAXa7CHAfSZcYhPfkDBWs0m2Ziks2J0DqGl2B0hn6ndfhdaDEJBdmqoeEuJMDw79sIONVSeJ19RBuQLpHaEhdQJg82d0AoBDowbR4YoNIdPpDvKiHsBFVwbsM3sAoasXo6oSuW0CWo4E7DdegAemtsLyNJuzyul121J8gdRBj0c/daeoOdybO0CMBtDugID9++6Q19GJlDM+91Wic70FUgwH+j6xK6Jpd3gBmHWTjv8hUSCABsdJ
*/
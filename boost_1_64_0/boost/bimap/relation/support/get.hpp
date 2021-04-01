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
o84eVSV6+lp1iklNzwxTn9J1miBF+lTXIuLLuOlDl+njStY8cS5Ijq5+r7y6G1dq/DaXSv+AAoQgjqApSPiFiujc3YCvYpHYPgM+BwowrKWx9wBirbzbGiH2XoG+CkUiA05hmoe23NtqMZJ8x+oTluBUiPBkhOeLv2v7xuqLSlC2WQZ2MqLszyMF39hDvJuw8dTfEDK8WCP2+wbepQooCgYUsu4iFIVCC2s6JbRPULuH8tCPZuDRyokDylIg3709z/do/uF/9AlzR/qIwO3CRRDXC001R+5PfMPjq2Qo44BmOBvGXsaZ6hMDGUrbMgmvdHiRSMUYLDJbqkrx4eTlJxUY203/OGg1tcWTWilTzbu8CI1ZJS9t1/HS0Gj/A+2t98r26zAYeTI9zXwmdJcbzG9f8YVF8cyaGPEbTGoCieWOsyQrrCGfU0Nyji1Skhnza9GsToDxlvNzV5LeFYV/QNSCzTihWzGDOR1lOuZm3pApp2tCa8kCyMJ4cTkwe/QO1XE4RlnCsQNMk37VpSjQrLe3c9n2b++tOdvYrN0E0l2JDkohOWx+929WSg==
*/
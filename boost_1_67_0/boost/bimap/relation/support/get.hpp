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
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
*/
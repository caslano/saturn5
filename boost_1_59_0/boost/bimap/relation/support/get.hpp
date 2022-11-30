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
// of relation accesor. They are built from little macro blocks that
// are both more readable, leading to self docummenting code and a
// lot more easier to understand and maintain.
// It is very important to note that the three building blocks have
// to laid in the same namespace in order to work. There is also
// important to keep them in order.
// The forward declaration are not necessary but they help a lot to
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
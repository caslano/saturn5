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
4TkBrXmrRAz7md94qFetgg9xapRhqb+5JtViJ2XxAGVBlF6DfHTfc/v4DL9D84EvXtbd8Apuw88vj5yHYAO2Nksx4dFtpT6c6WV4w401nFb8Cks+/FpSeHY7+tmV84jnBpMcIpFHxRwdKCPsHph11I+mFEMtctvSKIWr3UkhI8pflgqzdP7BPqFkugREAXAM9xKGUOadTwVB5bZ72G5iQ2wLTc6kZpaVKzoRk44dii6olVuUiKTZrAx+6RyyBjiPyt4T88GzsIV7PNCPpYAuFVdMk7VKYimSDPFkEgwa2pH7sGeT0u56D8/3bMzC09H4vBeE9nl0ehoGsNd63nmTxtf5tdzbRFJtURsOXHnwfGimSt549afn9ScMmyseu3VJwEmDVcTL/Af4TsG/R3558UMTqNM/+nnNpj0Aqik/h9c9j9mU8lfZ5pKzylsHawSKXYajp5Q4z3LPucFhBw4ovcpnTKnvjzfZQ9tjX3Vcj6W0qFqhSt2EhOPN29brV60ODrll9apwWcHS26pXljSsCsGPq5a7XNNY1a36/dGatUFXbNGtVazSC3UJfVCN5qraeZUOO7c9otr6puJpvJy6FKeqt5EX51icrO+cIevdxb1FKqYZX2O+02s/HH3qPlij6aEurK46lPVVSGGa
*/
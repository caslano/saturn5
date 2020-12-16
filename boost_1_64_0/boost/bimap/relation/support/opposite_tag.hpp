// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/opposite_tag.hpp
/// \brief Metafunction to obtain the opposite tag in a relation.

#ifndef BOOST_BIMAP_RELATION_SUPPORT_OPPOSITE_TAG_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_OPPOSITE_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::relation::support::opposite_tag

\brief Metafunction to obtain the opposite tag in a relation.

\code

template< class Tag, class Relation >
struct opposite_tag
{
        typedef {OppositeTag} type;
};

\endcode

\ingroup relation_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Implementation of const pair reference type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    opossite_tag,
    right_tag,
    left_tag
)

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SUPPORT_OPPOSITE_TAG_HPP


/* opposite_tag.hpp
aTszHebDGZqemTpG4FI4F86G1WrbvlJt26/W45pO7WfFb4x0PqDpfBAOhw/Bc+GjGr7OaN8ifFLDt0Zqw+NvNPwWvc4vaPjb4Rh4h45xuEvTfTcsh1vhUrgN3qhjSj4L74d3we3wHnW/L/60/w2+p+loJ/kZ2uZpfpVofpVqfs3X81ZrfpVpfi3UMTGL4Fq4GF4HK+AN8Aq4XccY7ICV8CW4FO7T+A7p2Js3xO3ll/RjwT0x8muX5tfjmt9PwPPgbh2782Vtj5/SMUd74BXwabgcPqP59KyOPaqHW+Fzmt56W760PwlOjVG+ztd6MFbr13htrybqGItCTeeFsDecrPViCpyo+7V91D4d8iZG+7hWz3ONPndugCPgZ+A5cIOWk/Vwurpnw+v0fn0clut+bT+0v4WyHaP9SNf2qg1sBdvCjjAT9oY5sA/MggN0/3Ddr/WFvozg58xKbZ9WaTu6WtupNb5836bhx8XI97M1P4bDdnAEPBOOhP3haDgYngvPhqO03TgPjoaInKfA6Pc9GKTnSUaG6nkczYcEmA+TYH91D1T3+zDDfkPL97vE002O69s2/jJhd9gB9oRdYT84GJ4JR8J8eC6sgePhQHgZHAIvh0PhMj2+Fo6A6+FI+Fk4Cj4ER8MX4PnwJTgevgInwNfgBfAQnAR/DKfA38MLoeP29cPWcCHMg+VwJKyE4+AyeCFcDufAKlgGq+ESSPp0LTj9ToTZkg/Ba8YVNNFf6XH8FSaZiLk9P31vaH7PHTC8Htx+fh9F8ra3NIVIFXLn9pMzB+ipGi+0f3vL+Jihf+GYocPPJ8bHDf2HjBt6h7KfdF9L0wsZhZQidch9yH7kCJLxxZZmEFKMrEa2IDuRg8hRJOd+wiJzkTpkB7IfOYykf4n16JBZSBWyAXn4S/FxSPEtvsW3+Bbf4lt8i2/xLb7Ft/gW3+Lb/9L2Lxn/X1W97GSN//+Ub/z/AR3QtT0hNJ/bF+Av3LFK99JP6o2t5/QVy8SOyD+uvqSyosabK1HDnG7nkP+FuK9KaEOY28VuefkK/9ian4XOkaA2NRq+B+ewNirLyhbKae38lT8VP+eLu9yG6WbHR+dtFzvfhLamX4I7dn+jprmvnL9mYdX86vm1y6sl/HQbvp+M89+ifm/pEbZLr8HrQjvvfmuJe3xCppnQbpojumgN70j4bbhjjeU/LH5WJMQYyy82ZqI7ED81CVHj+NVWbqCcu19CprgjrzM878J9CTr+Pvn09KQWJmoMfqb62xf2l/rx6VHj9NVPEuXiBtdPwhVpEzBVTE1sn5LAsPwkht335FentD4Mz58qR3rj7siRzi7Tprp/2Z9EiCT2J4gUYOzYGSXQZM7XTm3j7syIlMt8+97NCvEz0fvs70i7QW+MS77kTf8Ecdu8ShcbzP0JoQp7I/EmrnsjrZBhc0npHTuFxxOs0vONaSf05t9UG2qdn5++w9D8rF1Mgh1vF74P+Uk6Pr5VaXpiuokaIx9236m2rMVBtqxqH1Znbay8OpfJ/k+zn3rFfuqV+t1oba+07uj+LbCv+PXqAPulzN4icdvyHmFXmtdC509LCNkG58Bf4T/jfm0fbNMQaAOrfgfY+zNa3H92YrULU6z/M23ZP1fcTkJQu1Buw/S18/+OEPfr6nZM9g4ZkxdYv6fbOMapG6tQcbeILmdqnzpMjv/NccvVQe55cUq4XG3/yOXq2S9FlquTWV9k/EYTxjEUR9mNRpezooByVhxQni4I22jqmPtypD3yMeQ3+D+wI4aN9fzKxcurK2rLl9bYQha0luy7En6C6WFaabkLx9nRBJQzPZ5tx8P8UtwX8jRIbnh/7BzhvxM/A0zs+3o=
*/
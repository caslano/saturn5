// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ITERATORS_BASE_HPP
#define BOOST_GEOMETRY_ITERATORS_BASE_HPP

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/if.hpp>

#ifndef DOXYGEN_NO_DETAIL
namespace boost { namespace geometry { namespace detail { namespace iterators
{

template
<
    typename DerivedClass,
    typename Iterator,
    typename TraversalFlag = boost::bidirectional_traversal_tag
>
struct iterator_base
    : public boost::iterator_adaptor
    <
        DerivedClass,
        Iterator,
        boost::use_default,
        typename boost::mpl::if_
        <
            boost::is_convertible
            <
                typename boost::iterator_traversal<Iterator>::type,
                boost::random_access_traversal_tag
            >,
            TraversalFlag,
            boost::use_default
        >::type
    >
{
    // Define operator cast to Iterator to be able to write things like Iterator it = myit++
    inline operator Iterator() const
    {
        return this->base();
    }

    /*inline bool operator==(Iterator const& other) const
    {
        return this->base() == other;
    }
    inline bool operator!=(Iterator const& other) const
    {
        return ! operator==(other);
    }*/
};

}}}} // namespace boost::geometry::detail::iterators
#endif


#endif // BOOST_GEOMETRY_ITERATORS_BASE_HPP

/* base.hpp
Pj3ooi49pCZO+oQ9U/3j0tH15emw0xu0X592hxE0RFN/LYE5vrqg3t/BAJdA9E67ZTAAjCl8vTLjkILWLfhwoENbOELDDIIFgQqTymLq5QjNeHEPnunjJ/Zy5cvqmeusVtjqVSjw60aM6W0a4texJ/ELFh59hc7q14OlRMGPBNOPn4AmW33LieixGOHXGffwqz331NsTfr0FahUYNDzY1BveERMxx69zi1iCZ8GvjrBWGbD+F1iJnJDKwYYmrFjbxnAKBMV9KBo6w7GPlTQwfF8/ggqc6AUU4alnFBX0odtBJaFnnsnRk4DA2gvB/wSfpTNx2Rd0ScgfJ+3j9qcDeEdzdicT8CQHDCZ1o1bFCHQmnRA3TJg0JAMdb4QncJtlo9Cxprg2Jp74MxROsMRbb2oDWQCi2YbFGDiieeAycyGGvRMBeUQVjGwiP2PbQad9+wGMmlV36iYnWNei4h6P+7dNkbnPH9CdKgGAQkrfaQ0En8EiSA9fVmHLAXXVv1Yyicc6O/GEcBYQcbMzAaEfkET4awQvhL92JDozcO9XWgQFf7SEfgxfOnJhg5cOBk9lg3jTXSbYjfAhlnVYN/TceUK01wPCiHSmUQHjtScDCIxhO5vBFhRxaCP8TpaF5sDaE9ysDHCbiDe3MtAA
*/
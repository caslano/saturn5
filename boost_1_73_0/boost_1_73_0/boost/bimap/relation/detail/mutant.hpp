// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/mutant.hpp
/// \brief Mutate functions to extract views of mutant classes.

#ifndef BOOST_BIMAP_RELATION_DETAIL_MUTANT_HPP
#define BOOST_BIMAP_RELATION_DETAIL_MUTANT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace bimaps {
namespace relation {

/// \brief Relation details, mutant idiom and symmetrical metafunctions builders.

namespace detail {

//@{
/// \brief Converts a mutant class to a view with zero overhead.
/**

This function is a safe wrapper around reinterpret_cast. It checks at
compile time that the desired view is supported by the mutant class.
See also mutant, can_mutate_in.
\ingroup mutant_group
                                                                            **/


template< class View, class Type >
BOOST_DEDUCED_TYPENAME enable_if< mpl::not_< is_const< Type > >,

View&

>::type mutate( Type & m )
{
    BOOST_MPL_ASSERT((
        ::boost::mpl::contains<BOOST_DEDUCED_TYPENAME Type::mutant_views,View>
    ));
    return *reinterpret_cast< View* >(boost::addressof(m));
}

template< class View, class Type >
BOOST_DEDUCED_TYPENAME enable_if< is_const< Type >,

const View&

>::type mutate( Type & m )
{
    BOOST_MPL_ASSERT((
        ::boost::mpl::contains<BOOST_DEDUCED_TYPENAME Type::mutant_views,View> 
    ));
    return *reinterpret_cast< const View* >(boost::addressof(m));
}

//@}

} // namespace detail
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_DETAIL_MUTANT_HPP


/* mutant.hpp
BJWvyRzrpeVvJblJL+xVwpokxR1DAcHpd7K9nB5fDE6PxzMMFbZms+j0R3u93XWMnlFiTo+T0fHZ0RRPcl8KW9ay3HBzZjYMNyKjP45D8NCuAjAOJeWdAPO+sZJpvAbk32nTF7o7peDzwCtd09vid05lLqS7LvgImGakHJs51X7FNhbbJjwPs2e7UiqnyBVJv1E/LKjJIjzYqZQCA+6lsZqMgp0DS/w4nnxoCguj6hszHpgohLF5ChJAjpcymr2DnxV25bBxlX+2fKSlBTZogaf1YH9piUd5Axl1Gw1dGItlaEvjUb+yrcTerkhzSiTYk25dtmLFbjrSRlWy0mhkwub2ImGaPTZi5T26EJo29ysvsJE8ErZOMFp8DhyvwO6CwvTOek/k35pjzHlim/Ta3iYapFySFVItKeF19TSj/MImhlY0l5R2nujd7qeNnF3YnI0Prf8AUEsDBAoAAAAIAC1nSlJVnwHcogUAAAgOAAArAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9wb3N0aXQyLWZvcm1hZGQuY1VUBQABtkgkYLVW/0/bOBT/vX/FW07HWpS1wE66DVp0vVIGWmkRdJrQmCI3cRsfrp2zHUpv2/9+7zlJKXAMTtrClzj2+/p539za/HFP
*/
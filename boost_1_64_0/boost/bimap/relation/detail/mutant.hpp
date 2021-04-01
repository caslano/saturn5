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
YCifM0BXAj6SxLFtzdb/dIknh8ztN+mytZkmQ0kGuk1Z8A4wuDEH7ZIZlW5zFcP+M0TPrBI1v5W7wrdwDvKGfjMtz791K7UJvA5w3lJ4BKQkUA2OTbcHDys3bWe5jJdgPeWvondEMwwBmzooi2Zff4l1hm0660o5Pj/NdeWujy0dPWRfsO7arZ5Su5IVYSrqZFRk7oVmL+f1oghfAjfX+0jCpmhSEMf6+m4qdYiq4gC4G8wE6V4xzGwqw449BTi2vn0J6I/bUoTRT4nJKRORaczZiof3+gNN2Kw1VtufS0F8EikRGjIaBxsYPGTF97iujoYaI8NvaRiKjZbE74yJvjuX243TYbG+IY47uJcxBpsjTLnIZJIcgIYfdCerySTak76b29fIG+IwwxW0f5UZaM8VwJu4QU8ik9tcTUiX07kX0wXYaP/bjWAWJdOYppfkE+naIC2nlSdweHUY9WBHTwBXG7RpbKJwoo0vC06x+ktYmrDG+6kc6KToVGAOIS7me//vuGp09BnVPjN+BXi1k65M1b4jdre2Jz/nM0UBrTSvEmOuwSNbdrywBg==
*/
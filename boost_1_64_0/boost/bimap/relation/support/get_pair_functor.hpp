// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/get_pair_functor.hpp
/// \brief get_pair_functor definition

#ifndef BOOST_BIMAP_RELATION_SUPPORT_GET_PAIR_FUNCTOR_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_GET_PAIR_FUNCTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/pair_by.hpp>

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

/// \brief A Functor that takes a relation as a parameter an return the desired view.
/**

This functor is included to help users of the relation class when using
stl algorithms.

See also member_at, pair_by().
\ingroup relation_group

                                                                                  **/

template< class Tag, class Relation >
struct get_pair_functor
{
    BOOST_DEDUCED_TYPENAME result_of::pair_by<Tag,Relation>::type
    operator()( Relation & r ) const
    {
        return pair_by<Tag>(r);
    }

    BOOST_DEDUCED_TYPENAME result_of::pair_by<Tag,const Relation>::type
    operator()( const Relation & r ) const
    {
        return pair_by<Tag>(r);
    }
};


/// \brief A Functor that takes a relation as a parameter an return the above view.
/**

\ingroup relation_group
                                                                                  **/

template< class Relation >
struct get_above_view_functor
{
    BOOST_DEDUCED_TYPENAME Relation::above_view &
    operator()( Relation & r ) const
    {
        return r.get_view();
    }

    const BOOST_DEDUCED_TYPENAME Relation::above_view &
    operator()( const Relation & r ) const
    {
        return r.get_view();
    }
};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SUPPORT_GET_PAIR_FUNCTOR_HPP


/* get_pair_functor.hpp
Mop7D2Kpds0XGf45VrRWeyIzL81BoVm4y/3HD1b6+08rHXn4CW2HWj+KOroqcTiq1Al3NFrB0v1Nn2kscjEQhcPeEc0Gz4KUh5mNdXEK9QQjlUvl84ehDGF6ADfP57uiHtWGot7aUtmz6kCe7ii3+jRHRAuIrRIS4cyfUwEJas9hR6Yb0ntKy36Gkv2yIaM9AWtWcIYGVZ2glx8ZrvF5Ye3oihRzDcc/Zxlju4O2xSlO5YFRFcr4eelfXHekJZgU0ZvG0k2aEABKnPCSorAjg1GSsr4/4+IWCoQD+hZkOwmbVTNMoFM3t54F0Wz2N/EoViixOLy8sb7RYxT3OT1AWKPjpQwGug4nZqzCeeVei6qBq6d7EY2a9KrlE29ovaM+H5GMWJmBtwVyBQg7icOXp0JEMp5LYbMg5gI0CgyB46p/L85lJ0gcBHSv1JgVw7Ui91FL3TY+F5ung1oRBFIZhJ4nM2bh+KQS4pKOr+6sEpvabmnYZWZspaSwSlv70hbiFKukmOww8i7Gp+p6BGIRTf30ddgWC8Kuoq3lNwZ0NNN1xwSGJY5quyfHMw==
*/
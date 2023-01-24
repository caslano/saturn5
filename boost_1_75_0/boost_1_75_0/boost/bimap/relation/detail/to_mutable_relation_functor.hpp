// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/to_mutable_relation_functor.hpp
/// \brief functors to convert types to mutable relations

#ifndef BOOST_BIMAP_RELATION_DETAIL_TO_MUTABLE_RELATION_FUNCTOR_HPP
#define BOOST_BIMAP_RELATION_DETAIL_TO_MUTABLE_RELATION_FUNCTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/pair_type_by.hpp>
#include <boost/bimap/relation/detail/mutant.hpp>
#include <boost/bimap/relation/mutant_relation.hpp>

namespace boost {
namespace bimaps {
namespace relation {
namespace detail {

/// \brief Functor used in map views

template< class Tag, class Relation >
struct pair_to_relation_functor
{
    const Relation
        operator()(const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                            pair_type_by<Tag,Relation>::type & p) const
    {
        return Relation(p);
    }
};

template< class Tag, class TA, class TB, class Info >
struct pair_to_relation_functor<
    Tag,::boost::bimaps::relation::mutant_relation<TA,TB,Info,true> >
{
    typedef ::boost::bimaps::relation::mutant_relation<TA,TB,Info,true> Relation;

    Relation &
        operator()( BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
            pair_type_by<Tag,Relation>::type & p ) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(p);
    }

    const Relation &
        operator()( const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
            pair_type_by<Tag,Relation>::type & p) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(p);
    }
};


/// \brief Used in set views

template< class Relation >
struct get_mutable_relation_functor
{
    const Relation
    operator()( const BOOST_DEDUCED_TYPENAME Relation::above_view & r ) const
    {
        return Relation(r);
    }
};

template< class TA, class TB, class Info >
struct get_mutable_relation_functor< ::boost::bimaps::relation::mutant_relation<TA,TB,Info,true> >
{
    typedef ::boost::bimaps::relation::mutant_relation<TA,TB,Info,true> Relation;

    Relation &
    operator()( BOOST_DEDUCED_TYPENAME Relation::above_view & r ) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(r);
    }

    const Relation &
    operator()( const BOOST_DEDUCED_TYPENAME Relation::above_view & r ) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(r);
    }
};

} // namespace detail
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_DETAIL_TO_MUTABLE_RELATION_FUNCTOR_HPP


/* to_mutable_relation_functor.hpp
C9gfhDSOO9m5FclpmYSr6pUVWIN6eN5J5AWQS6aDnHq84a58vx6ifd8LJkfgSmEXoL6L3AKrZH6tAkU1AQWhIVtLk6mujxvMxcQaKoMwG70gf55RrWadjnfFLG3k/LAivyOGaNF5QqgCBzG/qfPqESjH8o5WKI+1GrdcAkmePFZ+2AouIFuM6to2fI2E7FR4d9w1oondseFv2h3XtMSipbrdEdNS7o5SsSqd9+t2x5kW6u4o05mtlGm6vS9bmBpvjM9T1I1x+75wNiNc+odukQMx+mvAYpEn96FFThdlfq1BxBCn3K8vspOKuON4VpKxRG6cDEUudkVGH21XXNEiaFfMiTHsCnOfpnZFxTp1V6DJp7Yt3BPVbVGq3xamCMO2uHhi8LYoVbM+j5b/lhPJ/8W2WJKiFirjCbg2DrdFmdR/taJ1ZXFAYAzJq9iAeMTLQyVGJaPx/o9H5Apx+j4D7mjoKeCOekUADiyIjUBtXEegs8ej0TxGOq7w2z0/MeZe8DsIbXTgoCHFpvA4YPClfFLwWXgTGBzuH/AAeCfOO2jA4KUSg5fqMHipxOClhMEL4RaDf2PsXvZhBKE+JQYfE04jQzDxdYKRdQse2Yc/8sg2HD7fyFw+z940cG9Eg0sLpcGdwXOcszDl2uCOWYIHt+JnHNzecwwut5Q0RiIx1XcKRF+wzAdWotrMKtEvNcHHb22SPqHHbT19mmQ9
*/
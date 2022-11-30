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
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
*/
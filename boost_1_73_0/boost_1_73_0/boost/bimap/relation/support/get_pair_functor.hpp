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
hEnPIEsBQq9bG/Tmh7cMo+d4WgnCmSJdSiMWWGlTsYzDy7nWL+kEGPIy03jYRGoiCWmwOOa588cVnEzPRj40wpMnATTv18Dk3dHub6/ftNaOCivUoszuYnw53RwdHljGFkIxsypNLvlLKSksSYak1l+p1r7y/Uql56Uy7lKd9AMCJwCuYrfKeT/IauS6JPUqYY4FGDoB1A94CQOpdOKFCDzgQ4X88ijsQ0+ovMB8vSlaCjwy/cBylZTvVvyD77/u3Ff2gvcsOH7ragskQ0+1hdeVhTsKtphhxQRww2RReV1HUG6VOj65wxKPbqPxk1CxLPBoe9YlQnfSwztLBpGnta1F6hJlq6B1oRw2BKGa9MDMIsZ+kDIDbXy++fyl1fi3AXD0cTKCNukcVG+eTVgeBw1coI0oE0ijtj+fPpx/HI0Otnc8odtz7LHJ1jbGV+DY8VIW2w2KpJxh7fvnbTnmRIwUVrjsw5sV889fUCIY3uY4ufaDTSALqWdMRkIJ16RQo/ej8R+DUTQYjVprKVT1wpzZVSnaIkdi3qTlFlDWOMlwihjOHC/7OuWGmNNOlec6v9KG1/U+vO67isfroVCVbwlDbanCZGMKq5rgapIPH9UWjhExoul1QthQ84EYrVIBrEWJ+MLtdeLgBwH6
*/
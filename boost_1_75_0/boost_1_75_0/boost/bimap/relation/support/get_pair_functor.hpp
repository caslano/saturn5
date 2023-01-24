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
j0dPW1PXSto/YUW7lMNzyVAbvS6GB+wLRHoxooXvLiC47yRhvJMG4z1kWg8trTcz0f90AyKf25uWP6x7uI4fhHxXcQ92d8NhXwvo4uyzdKOn3KR3WfdkIt/qQYSxgnfyNd/R1r+Sn/2/CzMZfZNqqvV4JDSW6atU1TpcQi4aFTvK5ftRqffDFv4dbViRPtovhtBJaA7Y8ByTyRyU6MgQ5U3SS8JSL+Cfu1iuHy0yrO9wItykXCBQn4sC1WSi0WxKWRZIToITG63c1odozmVh4Gij/wSH9+EwNI1LKXuUM01UruBMHUSmzdOwGTxn2FEXMSHVKzanM8S3J2DfAvsGnOhV0PW0dMzJV7OlxlEQ7dFO70a8O+Xyvo8qygpyEDP7VCjeQoNJR2UjHc6Jr3ASZwqJyoMRA5ROSB3UL6l1a1P2xYJ2Xi5+KJP+DAM6erH4DWcOqax+89ITytXAU/V8YzncD+nv2r5Ifz9qA3V0t+hsRebwpXsz8Ml+ulUnoM3hOwNuqp6vUHOA+CUb0Nn/E4eV28XgDuZheHXASQhYUKQWiYlWgTKkGwPl0a4AlKjvzCIWjjwLJQTEvMGxi3hE4L05y1A8sygg3zHshwcs1Df8ZcHnzGKrKdVHpVJ9J7Dle4H2CbHXx/6KgIe7SfQmyRk9uXVfOKUkF5NH8EsichjJMU5/60qlx08gMu2lMxfw2FzbCvpRkRqbHIYd
*/
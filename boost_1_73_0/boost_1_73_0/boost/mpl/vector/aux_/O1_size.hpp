
#ifndef BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct O1_size_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : Vector::size
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct O1_size_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
        : mpl::long_<N>
    {
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
auq66WJI67CoY2XdB9W+zKK2FCSlmdmfn6xkDQz2SdLpueeFO+bQulpYzAiTaq398YzDTpvGZqS8zZek6FAY4PjLkZsZL+YkSTr9U6pEb5zUyhJGjx2M7knICTmBFZoXNImVDRJmcNMNHtAIJzJyY3SfQo+XVve4a9HghHCdwlo846XSh8qEPOlmGM8kmRCAQW+NBStV7b87/8Hono7RA33QLTqJyh106/DwEBvcZET2YuMb/j6BKdHjPivspGvhn3wQ5/d8fvEm9lC6xwKrdd8L1WQkHulSSk/n1YqXy/R05FlWXzj98PGcfrrNy0V5dz37djGNIdlCHG29cGqxjgy63/H/xRh91fDXQ4gQ7ysauR5gTA5i7dCAaxHGOUIrLDwhKohsq11E2EvAeoqN0U7XustIfnY2hSJf5lfeGn+YjIW3sKg+l3cQPQZ/ke/H+jFYjALgHaxmi1nBwacKhfcQlgGmcFVdP3z/EYrnI011z8fBHAUZfXVBj9v2B1BLAwQKAAAACAAtZ0pStdgHczwBAADvAQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDg5NlVUBQABtkgkYH2R0WvCMBDG3/NXHBXp9lDCkMHm0kLpFAt2itaxN8naqw1rG0miTvbP
*/
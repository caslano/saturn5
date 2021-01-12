
#ifndef BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/vector/aux_/O1_size.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct size_impl< aux::vector_tag >
    : O1_size_impl< aux::vector_tag >
{
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct size_impl< aux::vector_tag<N> >
    : O1_size_impl< aux::vector_tag<N> >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

/* size.hpp
MbfYTWWfRPyI4/hUxT9Q3kMZ4oCMe2JEgnsL8hGHx4ZHxk6IrORlI8OQ7aSsnMr4JHFsUuJu8/LpyoMn8KzUIRp3u8fcxkTi6fAyngEot9PLXT2KrMvLnN15kXV7mbdNTtkGyKgl4OTC7fFyXLlN8W1GWE/nl9O3If6L1ngj7G/+BQ7tDuFmE7U/NSF+lBeAtfOsNOuKHmGJ34+4umBT7P4WS6vN2xz8MrAvp/lyKyOXHd3b
*/
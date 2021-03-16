
#ifndef BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct value_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : second<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
7poWUxsKh3gbwxl0Og4iFGiFOt21e302/p8nQ0+YEB+Vi2WIO+wLZSjL0gbKyZY2ZOhYZssQH5oJGbrPUg+mpAr+h0jdDedXJrqANJ62+8ej43U1ybhxKXVcI0enW2m6/pzRWSW8o7NE6DWW6snSeME5Z6mjmq9kumnerHR6m+OYT5q4SB3H2kPCDPqujvHzuLzeUSSu7byvXNlkuTc4BttHjuwDoXbicSzHO/q1zcQ/BZkQ6tCeou5lzxHSxcw=
*/
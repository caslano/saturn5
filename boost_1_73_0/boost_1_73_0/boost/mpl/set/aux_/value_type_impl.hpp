
#ifndef BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct value_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
IHMaS5gN5l6SPl/LTOdEw3vvNE9P9r9zJ1binLcpLbN7msrYzubHT7wVQYGWhRZo5WDfI79xwmBehPPWL6jnHeMm0syV4/k9OdWy/QyJ+YtkOhPDo7lz9I45clprP1uquCljfIa18qOAjbZm1mIs07czrYylLX5nhotpBdbW3Ha5ERl5I5kI98ohfwx1LBIIZQEeQqmMXWwPzzhfUH6+y2sepj0UmMzDUU7pVCylI4Y4ulr4nFWrPkOJtp/Gouo=
*/
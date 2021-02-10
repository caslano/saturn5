
#ifndef BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

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

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,0> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

/* pop_back.hpp
L606xx72ktzB97vvO44Z1CbjGgPCRFNI+33g8SBVrgMSJ+GcRBVyBSl+GjIepdGEeF4lN6Lx5NYI2WjC6JVg9DSE9EgPlqj2qDwtciRM4bY6toJz0SmiSmBjzoqsa6xEd1xARM23Fri0wBpe4ykVHIQp4U8ScMNVOvHzXV0fXbgpuKhEs7m1ID2RwDJZ17zJA+K2w4eU9iezZRrPh/126ny2SOnD4z19SsJ4Gr88j978Oxe8HbjOzsYYaswchebL/dfaZv7xseV5rW7hV1SiOELODQdeGFRgSoT2BlByDe+IDTi6lMYhbN9pA0sNwPchWi2mo7V91kk4Hc8WSZgShkpJlcncLjewXr9aRi88o9cbfwNQSwMECgAAAAgALWdKUkNOlqBeAgAANAUAABwACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5VVQFAAG2SCRgtVRdT9swFH23lP9wV4S0oQWnjAENaTXEx0AbtCoZe5vkJjetRWpHjttSaT9+13FLGRNIeyCKEl37+J6Tc4+SWKxtJmrssUSqQtPrHpcLbfK6xy7TdNA84KI/vB70b1NfFbJEmFWlFjlL+AafcN9iC27RzNGEtcyRJQarckm7ubDCN+Xt3Qj2ogj636Be1Fmpa2RnwmIM
*/
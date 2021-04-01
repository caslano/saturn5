
#ifndef BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
nnVbxFXwKX6EBjxOeC0esFlsxpAgUZuu9WrttlU9XojZhamB32l/cPRaMScu21s/s7BBrfWn/0XPoxXunuKDsN0OXzMNMeq+QXAypxSyHS7+YppLeWQfjLwo0AirtnQherdNT7vO4utEuYDh2TUfs0/gt0PVz7xUuz+rRn4/iKq7CowJDX3JeACJXoV36gx8DckF2tgZ9770JN7r3NF5JpMsD1UF5FGLgefEpNcO8N3BBGmVORiHLlD/zO0N7Nf0Ir0dEBXrpJBGWpKfFMGSIbIen1q1b2G6wTnm5cDSdj5H71LHNBikgte0kqaPeGG2OC1Eoah72sfkuc54cfW+OsMcoSR++R8wVIaE8rwRWU9g/nxQ0Bti7QYNazptwh/aA5CwZpzaN3/82U55DdEghm0nyl2uUQndrNzmPaaI3Nklhev6SAU/xeeo55kTCrQ53nefbCDgtmcdJiOLYferEpKP5RIetuMicox/SgSkUGZDDNX4Qv1+8gXFT9lb+FIAFHw1RtoilQjS6UpHwoN6mSXC9WHWNuQC6j2Oc/t4YH9/cK0xP+CBX5KuHg==
*/
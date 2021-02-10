
#ifndef BOOST_MPL_FRONT_HPP_INCLUDED
#define BOOST_MPL_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct front
    : front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, front)

}}

#endif // BOOST_MPL_FRONT_HPP_INCLUDED

/* front.hpp
4fVRcMGYOhNba1suP8uwUTU37plhoOsNgsG8NKhtB5Zg/pqukjTO4t9jH0FxRUHmrcxzbOBtDzkWqq8sO45Goaa6Vk0+BjH8JIrX2VMSTA59S+I0k/63+1vP83xwV+BGcBVRZwP495L1FTv+teLl+RoMXRaHaaAxZDTlnOlzwScZtoYsaap4+osMLnnnyTniv5GOeOWuuI8bTgpA96aSk1+LdP0UvzjiUWtseftaXjvC4cBLCIszFS8vP+MfUEsDBAoAAAAIAC1nSlLRHZirzwAAAGYBAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTU2NFVUBQABtkgkYE1Qy27DMAy7+yuE9jwEA9adhFz2CQN2dxMGMepYga00yN9PeXTZyaRI0YRYUbTxBbXjkDqx54FlltyW2g1T1OBm/8A0Oq5Ogavd6670jfxEfiuhheOMMS6rfADTv2JA0kNvNmKGDl6nDIv6Sz9HXLbM2iVJtlS9KKtIrF0M9/fb54cJO+fkB7yC6I5OMmiUGGkO2lMSgi8L9T61EcXWdj83Mgw2W+v+h0dFq/6DHLqFWq+efKfIpD1oPZiFFfsJiS6lF704fm7eNeBE52l/AVBLAwQKAAAACAAtZ0pSRGpVuRwBAADUAQAA
*/

#ifndef BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED

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
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct pop_back_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, pop_back_impl)

}}

#endif // BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED

/* pop_back_impl.hpp
2VepZC1RKagZNYM0dase9LWGXzPC0Ahts2/rdqOmk8ZtVPpNwrB/Yhj1q2HYS2HozUbdrpOartdMXK83/dCwSGD5VtPXcVAProches+sXzhq2UTU+U/Y/wFQSwMECgAAAAgALWdKUgGxvzLRBAAABCEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDMxVVQFAAG2SCRg5Zprb6JKGIC/k/gfprtpspda5LZtPdQE73a9VVG358sGYQSOyFgY69pff96Bejn2uLVZTTUlDTIw816fGd4hVSkOqWmEOMOprj8g8DPEsykJrDDDlXW9GZ1QqaDHF3W9WkPGhDqcyi87qnw89iNq4+ABB8nQtTCnBnjszTIcp54kk6joBiFFAb6fgEbkGOFS1hmaBsS30dgIQyYRJZMg0zKoIaRSsRm8cC4gOSWgOsbWcmSCixWmUc01AxKSAU1WKm1eOU8luBzxKfZpUp+NcRpR/IvyDh15fyHTMYIQ02s3JMnLS+UqKSw7V7FvUyeNxIsE1+v1khpogfuuaVAQwhQnuASnO26I4M8nFMFzcMvwwHwbn0AsFoY/+SCkhHUnmP0uKAxG2HJB8v78kKRNfiDda9X0bl3vaFpO06JTRctHVyVbK2j33zpCXesZ
*/
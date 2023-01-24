
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
Wh7jqCbLcqnL7aQQvRRRvopZesblSN4sv7kkB+KnELPJYysP9hdSecPKlq+y81asnNvMeBKyuYgNKFvtoF67pVo2RVUUTXHDzbWIDnlB/yNSW1oCFGKa830YTDBe9XvYXBxiiBuVFsBnGfUJ5AEZBj7O3qDEpRPX+picWiuNAnsLXMnd33GLNv6VoaOaJcXkxagM/3XyY0Gg2YNczPX0GTjEdYdbsreiCzCdIY8yYNDvLmXjORYe2wM22EIfw5PuUB1FUj/lUluF1Jb06qniZIcuyp+5MrKzSU3trCrjg382EreZ09a2R/l8rHKPZbcvW4/U0C+l+mqBXSRHBaQiumV0ipooQ61ChMfvZXTGcVzo0Bcvr5QqyHDkhyEfWIs26N9oVsIxIsHXB/k8Jnc8ASxa2Sb7mAoWlUnmLJpGqDQXGGM6od5UDUTFzKVTzBiQaLB/y9WjHVO0+Do7Z6j4mWiv8WEWkfJcwI/5VD6Zy0oNVNhrv25SpXbd5iRMtwS+yd4fvrlmO0gOFdPSj7yr+XWiyfx0C/IOuQR8nSEJil7a7cXukK8NorjZH6Bv+D3cMAG0e22obWbjZyHL53jQa20B/2hR0WeJN2E5tqm4Td0TlRmtv/JqNbFPyeVIhbJcI47OQ2QFZZPNPfUO5Xf+VIbkA5OqcGG+qe4G9PAabWEPGpMQ/0xfE+Ntoy+i9qmTvFXrNau6qmzilA9Z
*/
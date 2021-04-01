
#ifndef BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
        : is_not_void_< 
              typename at_impl<aux::map_tag>
                ::apply<Map,Key>::type
            >
#else
        : bool_< ( x_order_impl<Map,Key>::value > 1 ) >
#endif
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
GxYoet7k1gu13q+09Tg3drLCAfj/QbcbMKY7JYttRO3mmCvR0hFSOx5qBwNzh/RKMNTLQr5jSVUgdS6GBBv+kS7FWND9ngTW5svEc4hlWjcyYHH4gTjRxjEvf+IWgZHMgrTPDHZFEhnezeuu+OY8BdoC1TpzCrRbVpT2Fs0VrOzgvcIlmwfJ2W8iqxJSNZusS5+Yod9kRnYuZooZMPIWTUwER7dm+a8tRU65JP3EeQANF14IEsCouz22APUFiiQLPkqGwEHecQpnwNbsZGGri0dA65bJYgmy3cKs2FEpScXmyhboq7KP0JfKMl5GJ+kA2QbmBEKb6p2soM3JykIg9HLZ5T6Bz1ZIwbobCLacDCMA1MY18TxDbVN+7e9j/62GWZirViiKHMXcfkru6jExPNUxp5q+oDuPJ4dgMf7/Tj29negIHyS3qceU0FJU0VwTFUVk7G1EAtBSm50F9j5uQC2ijyLhT5aVo8zMZPHKkW6wcZ1UK1cLPDfDcXk1NJ0Xde1ov6xvBABe9tgSz+u3mby9q3tkurCXr3P3dn+Q5+DsiW/pD8PI3HTPbA==
*/
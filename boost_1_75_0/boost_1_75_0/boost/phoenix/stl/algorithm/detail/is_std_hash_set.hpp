// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_hash_set.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_HASH_SET_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_HASH_SET_EN_16_12_2004

#include <boost/phoenix/config.hpp>
#include <boost/mpl/bool.hpp>

#ifdef BOOST_PHOENIX_HAS_HASH
#include BOOST_PHOENIX_HASH_SET_HEADER
#endif

namespace boost
{
    template<class T>
    struct is_std_hash_set
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_hash_multiset
        : boost::mpl::false_
    {};

#ifdef BOOST_PHOENIX_HAS_HASH

    template<class Kty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_set< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_set<Kty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

    template<class Kty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_multiset< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_multiset<Kty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

#endif

}

#endif

/* is_std_hash_set.hpp
drGWJ6+c894fb+bcez/3zp17vnPO98z3zvfMyx7/n09NrKXVal0SrAmt9CffpOJ4BipT1aZvzgqlaJAb3pz6PInM9zsVmYgjaBb4nq661yxNZvwScis4fwM1v6cNI++VrxoEl0/nsJrztrD7UPN/nhSvQrpXmdW22x99+MyMNLLzbgXAX7ogJPW0LSmz8sP9yA9MHXo15TFDIgkAgbnwnJD11Ad1LN6I/ODt8apmn6KWo8blmbJUS0KYhqm0OiHdSFdDai5OQCyLH6Q4oSyvsQbBO7KiI3rm6VVZk6c9jdlMr33YQh06IAGggU2RiJN9+Puj9SyZOqZZg7P9tSBh0hvHzg7p3/lrf2Jqbm1rCSAVNuK1Jd3WaX+T/fgVl7lmNfuPtcz8HgG4ZujaL9zecMNSo1rWxZempcZZh0nWuhb+vf1rAKDaSsd8bbo+bX18fZ5vCYBaRV6RQ52+JLwbpiX0E676+9f31/xBcuv/MrtQIEpmaPp77GSnQ1d9/BNeciyHR9L7C+RPnERRFuX4Uu6WPcRha6oDIbzzJtuzDXC5Gs16Czp+tgqwC87rV/Ea3P0cQHKYyUyCNqL8ELZbA1klwHz2kwyCrM+g/tzsrxAk5jtOyKmIqyXyWFtmOqVCrAYpnQYBvMe5/g1kma43g3ER35m2m8HQeLggXkMALBWLQYP1o0wTA39MAjCNgdRxrJxTYwz84HeHpdIB
*/